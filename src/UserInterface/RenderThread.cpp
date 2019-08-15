#include <wx/wx.h>
#include <wx/dcbuffer.h>

#include "RenderThread.h"
#include "RenderPixel.h"

RenderThread::RenderThread(World* world, wxEvtHandler* eventHandler)
	: wxThread()
	, _world(world)
	, _parentEventHandler(eventHandler)
	, pixels()
	, timer(nullptr)
{}

void RenderThread::NotifyCanvas()
{
	lastUpdateTime = timer->Time();

	//copy rendered pixels into a new vector and reset
	std::vector<RenderPixel*> *pixelsUpdate = new std::vector<RenderPixel*>(pixels);
	pixels.clear();

	wxCommandEvent event(wxEVT_RENDER, ID_RENDER_NEWPIXEL);
	event.SetClientData(pixelsUpdate);
	_parentEventHandler->AddPendingEvent(event);
}

void RenderThread::OnExit()
{
	NotifyCanvas();

	wxCommandEvent event(wxEVT_RENDER, ID_RENDER_COMPLETED);

	_parentEventHandler->AddPendingEvent(event);
}

void RenderThread::setPixel(int x, int y, int red, int green, int blue)
{
	pixels.push_back(new RenderPixel(x, y, red, green, blue));

	if (timer->Time() - lastUpdateTime > 40)
		NotifyCanvas();

	TestDestroy();
}

void *RenderThread::Entry()
{
	lastUpdateTime = 0;
	timer = new wxStopWatch();

	wxCommandEvent event(wxEVT_RENDER, RENDER_START);

	_world->render_scene();
	//world->render_scene(); //for bare bones ray tracer only
	//world->camera_ptr->render_scene(*world);

	return NULL;
}