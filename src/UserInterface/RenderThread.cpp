#include <wx/wx.h>
#include <wx/dcbuffer.h>

#include "RenderThread.h"
#include "RenderPixel.h"

DEFINE_EVENT_TYPE(wxEVT_RENDER)

BEGIN_EVENT_TABLE(RenderCanvas, wxScrolledWindow)
EVT_COMMAND(ID_RENDER_NEWPIXEL, wxEVT_RENDER,
	RenderCanvas::OnNewPixel)
	EVT_COMMAND(ID_RENDER_COMPLETED, wxEVT_RENDER,
		RenderCanvas::OnRenderCompleted)
	EVT_TIMER(ID_RENDER_UPDATE, RenderCanvas::OnTimerUpdate)
	END_EVENT_TABLE()

	void RenderThread::setPixel(int x, int y, int red, int green, int blue)
{

	pixels.push_back(new RenderPixel(x, y, red, green, blue));

	if (timer->Time() - lastUpdateTime > 40)
		NotifyCanvas();

	TestDestroy();
}

void RenderThread::NotifyCanvas()
{
	lastUpdateTime = timer->Time();

	//copy rendered pixels into a new vector and reset
	std::vector<RenderPixel*> *pixelsUpdate = new std::vector<RenderPixel*>(pixels);
	pixels.clear();

	wxCommandEvent event(wxEVT_RENDER, ID_RENDER_NEWPIXEL);
	event.SetClientData(pixelsUpdate);
	canvas->GetEventHandler()->AddPendingEvent(event);
}

void RenderThread::OnExit()
{
	NotifyCanvas();

	wxCommandEvent event(wxEVT_RENDER, ID_RENDER_COMPLETED);

	canvas->GetEventHandler()->AddPendingEvent(event);

	canvas->GetParent()->GetEventHandler()->AddPendingEvent(event);
}

void *RenderThread::Entry()
{
	lastUpdateTime = 0;
	timer = new wxStopWatch();

	world->render_scene(); //for bare bones ray tracer only
	//world->camera_ptr->render_scene(*world);

	return NULL;
}