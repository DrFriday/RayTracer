#ifndef __RENDER_THREAD__
#define __RENDER_THREAD__

#include <wx/wx.h>
#include <vector>

#include "RenderPixel.h"
#include "../Events/Events.h"

#include "../World/World.h"

class RenderCanvas;

class RenderThread : public wxThread
{
public:
	RenderThread(World* world, RenderCanvas* canvas);
	virtual void *Entry();
	virtual void OnExit();
	virtual void setPixel(int x, int y, int red, int green, int blue);

private:
	void NotifyCanvas();

	World* _world;
	RenderCanvas* _canvas;

	std::vector<RenderPixel*> pixels;
	wxStopWatch* timer;
	long lastUpdateTime;
};

#endif // __RENDER_THREAD__