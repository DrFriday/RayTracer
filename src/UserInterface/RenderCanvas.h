#ifndef __RENDER_CANVAS__
#define __RENDER_CANVAS__

#include <wx/wx.h>


#include "RenderCanvas.h"
#include "../World/World.h"
#include "RenderThread.h"

class RenderCanvas : public wxScrolledWindow
{
public:
	RenderCanvas(wxWindow *parent);
	virtual ~RenderCanvas(void);

	void SetImage(wxImage& image);
	wxImage GetImage(void);

	virtual void OnDraw(wxDC& dc);
	void renderStart(void);
	void renderPause(void);
	void renderResume(void);
	void OnRenderCompleted(wxCommandEvent& event);
	void OnTimerUpdate(wxTimerEvent& event);
	void OnNewPixel(wxCommandEvent& event);

protected:
	wxBitmap *m_image;
	World* w;

private:
	RenderThread* thread;
	wxStopWatch* timer;
	long pixelsRendered;
	long pixelsToRender;
	wxTimer updateTimer;

	DECLARE_EVENT_TABLE()
};

#endif // __RENDER_CANVAS