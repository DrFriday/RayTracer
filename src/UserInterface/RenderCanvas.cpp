#include <wx/dcbuffer.h>
#include <vector>

#include "RenderCanvas.h"
#include "RenderPixel.h"

#include "main.xpm"
#include "bg.xpm"



RenderCanvas::RenderCanvas(wxWindow *parent)
	: wxScrolledWindow(parent), m_image(NULL), w(NULL), thread(NULL),
	timer(NULL), updateTimer(this, ID_RENDER_UPDATE)
{
	SetOwnBackgroundColour(wxColour(143, 144, 150));
}

RenderCanvas::~RenderCanvas(void)
{
	if (m_image != NULL)
		delete m_image;

	if (thread != NULL)
		thread->Delete();

	if (w != NULL)
		delete w;

	if (timer != NULL)
		delete timer;
}

void RenderCanvas::SetImage(wxImage& image)
{
	if (m_image != NULL)
		delete m_image;

	m_image = new wxBitmap(image);

	SetScrollbars(10, 10, (int)(m_image->GetWidth() / 10.0f),
		(int)(m_image->GetHeight() / 10.0f), 0, 0, true);

	Refresh();
}

wxImage RenderCanvas::GetImage(void)
{
	if (m_image != NULL)
		return m_image->ConvertToImage();

	return wxImage();
}

void RenderCanvas::OnDraw(wxDC& dc)
{
	if (m_image != NULL && m_image->IsOk())
		wxBufferedDC bdc(&dc, *m_image);
}

void RenderCanvas::OnRenderCompleted(wxCommandEvent& event)
{
	thread = NULL;

	if (w != NULL)
	{
		delete w;
		w = NULL;
	}

	if (timer != NULL)
	{
		long interval = timer->Time();

		wxTimeSpan timeElapsed(0, 0, 0, interval);
		wxString timeString = timeElapsed.Format(wxT("Elapsed Time: %H:%M:%S"));
		wxGetApp().SetStatusText(timeString, 1);

		delete timer;
		timer = NULL;
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
	if (thread != NULL)
		thread->Pause();

	updateTimer.Stop();

	if (timer != NULL)
		timer->Pause();
}

void RenderCanvas::renderResume(void)
{
	if (thread != NULL)
		thread->Resume();

	updateTimer.Start();

	if (timer != NULL)
		timer->Resume();
}

void RenderCanvas::OnTimerUpdate(wxTimerEvent& event)
{
	if (timer == NULL)
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

	thread = new RenderThread(this, w);
	thread->Create();
	w->setPaintArea(thread);
	thread->SetPriority(20);
	thread->Run();
}
