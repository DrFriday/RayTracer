#include <wx/dcbuffer.h>
#include <vector>

#include "RenderCanvas.h"
#include "RenderPixel.h"
#include "RenderThread.h"
#include "wxraytracer.h"
#include "../Events/Events.h"

#include "main.xpm"
#include "bg.xpm"


BEGIN_EVENT_TABLE(RenderCanvas, wxScrolledWindow)
	EVT_COMMAND(ID_RENDER_NEWPIXEL, wxEVT_RENDER,
		RenderCanvas::OnNewPixel)
	EVT_COMMAND(ID_RENDER_COMPLETED, wxEVT_RENDER,
		RenderCanvas::OnRenderCompleted)
	EVT_TIMER(ID_RENDER_UPDATE, RenderCanvas::OnTimerUpdate)
END_EVENT_TABLE()

RenderCanvas::RenderCanvas(wxWindow *parent)
	: wxScrolledWindow(parent),
	m_image(nullptr),
	w(nullptr),
	thread(nullptr),
	timer(nullptr),
	updateTimer(this, ID_RENDER_UPDATE)
{
	SetOwnBackgroundColour(wxColour(143, 144, 150));
}

RenderCanvas::~RenderCanvas(void)
{
	if (m_image != nullptr)
		delete m_image;

	if (thread != nullptr)
		thread->Delete();

	if (w != nullptr)
		delete w;

	if (timer != nullptr)
		delete timer;
}

void RenderCanvas::SetImage(wxImage& image)
{
	if (m_image != nullptr)
		delete m_image;

	m_image = new wxBitmap(image);

	SetScrollbars(10, 10, (int)(m_image->GetWidth() / 10.0f),
		(int)(m_image->GetHeight() / 10.0f), 0, 0, true);

	Refresh();
}

wxImage RenderCanvas::GetImage(void)
{
	if (m_image != nullptr)
		return m_image->ConvertToImage();

	return wxImage();
}

void RenderCanvas::OnDraw(wxDC& dc)
{
	if (m_image != nullptr && m_image->IsOk())
		wxBufferedDC bdc(&dc, *m_image);
}

void RenderCanvas::OnRenderCompleted(wxCommandEvent& event)
{
	// Uncomment if not propagating up
	//this->GetParent()->GetEventHandler()->AddPendingEvent(event);
	thread = nullptr;

	if (w != nullptr)
	{
		delete w;
		w = nullptr;
	}

	if (timer != nullptr)
	{
		long interval = timer->Time();

		wxTimeSpan timeElapsed(0, 0, 0, interval);
		wxString timeString = timeElapsed.Format(wxT("Elapsed Time: %H:%M:%S"));
		wxGetApp().SetStatusText(timeString, 1);

		delete timer;
		timer = nullptr;
	}
}

void RenderCanvas::OnNewPixel(wxCommandEvent& event)
{
	//set up double buffered device context
	wxClientDC cdc(this);
	DoPrepareDC(cdc);
	wxBufferedDC bufferedDC(&cdc, *m_image);

	//iterate over all pixels in the event
	std::vector<RenderPixel*> *pixelsUpdate =
		(std::vector<RenderPixel*> *)event.GetClientData();

	for (std::vector<RenderPixel*>::iterator itr = pixelsUpdate->begin();
		itr != pixelsUpdate->end(); itr++)
	{
		RenderPixel* pixel = *itr;

		wxPen pen(wxColour(pixel->red, pixel->green, pixel->blue));
		bufferedDC.SetPen(pen);
		bufferedDC.DrawPoint(pixel->x, pixel->y);

		pixelsRendered++;
		delete pixel;
	}

	pixelsUpdate->clear();
	delete pixelsUpdate;
}

void RenderCanvas::renderPause(void)
{
	if (thread != nullptr)
		thread->Pause();

	updateTimer.Stop();

	if (timer != nullptr)
		timer->Pause();
}

void RenderCanvas::renderResume(void)
{
	if (thread != nullptr)
		thread->Resume();

	updateTimer.Start();

	if (timer != nullptr)
		timer->Resume();
}

void RenderCanvas::OnTimerUpdate(wxTimerEvent& event)
{
	if (timer == nullptr)
		return;

	//percent
	float completed = (float)pixelsRendered / (float)pixelsToRender;

	wxString progressString = wxString::Format(wxT("Rendering...%d%%"),
		(int)(completed * 100));
	wxGetApp().SetStatusText(progressString, 0);

	//time elapsed
	long interval = timer->Time();

	wxTimeSpan timeElapsed(0, 0, 0, interval);

	//time remaining
	float remaining = 1.0f - completed;
	long msecRemain = (long)
		(((double)interval / (completed * 100)) * 100 * remaining);

	wxTimeSpan timeRemaining(0, 0, 0, msecRemain);

	wxString timeRemainString = timeRemaining.Format(wxT(" / ETA: %H:%M:%S"));
	wxString timeString = timeElapsed.Format(wxT("Elapsed Time: %H:%M:%S"));

	//only display ETA if something has been completed
	if (msecRemain >= 0)
		wxGetApp().SetStatusText(timeString + timeRemainString, 1);
	else
		wxGetApp().SetStatusText(timeString, 1);
}

void RenderCanvas::renderStart(void)
{
	w = new World();

	wxGetApp().SetStatusText(wxT("Building world..."));

	w->build();

	wxGetApp().SetStatusText(wxT("Rendering..."));

	pixelsRendered = 0;
	pixelsToRender = w->vp.hres * w->vp.vres;

	//set the background
	wxBitmap bitmap(w->vp.hres, w->vp.vres, -1);
	wxMemoryDC dc;
	dc.SelectObject(bitmap);
	dc.SetBackground(*wxGREY_BRUSH);
	dc.Clear();

	wxBitmap tile(bg_xpm);

	for (int x = 0; x < w->vp.hres; x += 16)
	{
		for (int y = 0; y < w->vp.vres; y += 16)
			dc.DrawBitmap(tile, x, y, FALSE);
	}

	dc.SelectObject(wxNullBitmap);

	wxImage temp = bitmap.ConvertToImage();
	SetImage(temp);

	updateTimer.Start(250);

	//start timer
	timer = new wxStopWatch();

	thread = new RenderThread(w, this->GetEventHandler());
	thread->Create();
	w->setPaintArea(thread);
	thread->SetPriority(20);
	thread->Run();
}
