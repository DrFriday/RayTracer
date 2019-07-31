#include "World.h"

#include "../Utilities/Constants.h"

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"

#include "../Utilities/Ray.h"

World::World()
	: vp()
	, background_color(black)
	, sphere()
	, tracer_prt(nullptr)
{}

void World::build() 
{
	// building ...
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	background_color = black;

}

void World::render_scene() const 
{
	// rendering ...
}

void World::open_window(const int hres, const int vres) const 
{
	// opening ...
}

void 
World::display_pixel(const int row, const int column, const RGBColor& color) const
{
	// displaying ...
}