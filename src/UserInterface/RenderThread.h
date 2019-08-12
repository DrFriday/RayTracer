#ifndef __RENDER_THREAD__
#define __RENDER_THREAD__

#include <wx/wx.h>
#include <vector>

#include "RenderPixel.h"
#include "../Events/Events.h"

class RenderThread : public wxThread
{
public:
	RenderThread(std::shared_ptr<wxEvtHandler> worldHandler, wxEvtHandler* eventHandler);
	virtual void *Entry();
	virtual void OnExit();
	virtual void setPixel(int x, int y, int red, int green, int blue);

private:
	void NotifyCanvas();

	std::shared_ptr<wxEvtHandler> _worldEventHandler;
	wxEvtHandler* _parentEventHandler;

	std::vector<RenderPixel*> pixels;
	wxStopWatch* timer;
	long lastUpdateTime;
};

#endif // __RENDER_THREAD__