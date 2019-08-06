#ifndef __RENDER_THREAD__
#define __RENDER_THREAD__

#include <wx/wx.h>
#include <vector>

#include "RenderCanvas.h"

DECLARE_EVENT_TYPE(wxEVT_RENDER, -1)
#define ID_RENDER_COMPLETED 100
#define ID_RENDER_NEWPIXEL  101
#define ID_RENDER_UPDATE    102

class RenderThread : public wxThread
{
public:
	RenderThread(RenderCanvas* c, World* w) : wxThread(), world(w), canvas(c) {}
	virtual void *Entry();
	virtual void OnExit();
	virtual void setPixel(int x, int y, int red, int green, int blue);

private:
	void NotifyCanvas();

	World* world;
	RenderCanvas* canvas;

	std::vector<RenderPixel*> pixels;
	wxStopWatch* timer;
	long lastUpdateTime;
};

#endif // __RENDER_THREAD__