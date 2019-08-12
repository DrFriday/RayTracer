#ifndef __WORLD__
#define __WORLD__

#include <wx/wx.h>

#include "ViewPlane.h"
#include "../Utilities/RGBColor.h"
#include "../GeometricObjects/Sphere.h"
#include "../Tracers/Tracer.h"
#include "../UserInterface/RenderThread.h"

class World 
{
public:
	ViewPlane vp;
	RGBColor background_color;
	Sphere sphere;
	Tracer* tracer_prt;

	World();
	
	void build();

	void render_scene() const;

	void open_window(const int hres, const int vres) const;

	void display_pixel(const int row, const int column, const RGBColor& color) const;

	void setPaintArea(RenderThread* paintArea);

	void OnRenderStart(wxCommandEvent event) const;

	std::shared_ptr<wxEvtHandler> getEventHandler() const;

private:
	RenderThread* paintArea;
	std::shared_ptr<wxEvtHandler> _eventHandler;
};


#endif
