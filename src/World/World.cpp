#include "World.h"

#include <wx/wx.h>

#include "../Utilities/Constants.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Ray.h"
#include "../Tracers/SingleSphere.h"
#include "../Tracers/MultipleObjects.h"

#include "../UserInterface/RenderThread.h"

#include "../Events/Events.h"
#include <iostream>

World::World()
	: vp()
	, background_color(black)
	, sphere()
	, tracer_prt(nullptr)
{}

void 
World::build() 
{
	// building ...
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	background_color = black;

	//tracer_prt = new SingleSphere(this);
	tracer_prt = new MultipleObjects(this);

	auto sphere = new Sphere();
	sphere->set_center(0.0);
	sphere->set_radius(20.0);
	sphere->set_color(white);

	add_object(sphere);


	auto sphere2 = new Sphere();
	sphere2->set_center(Point3D(20, 0, 50));
	sphere2->set_radius(20.0);
	sphere2->set_color(red);

	add_object(sphere2);


	//sphere.set_center(0.0);
	//sphere.set_radius(85.0);
}

void 
World::render_scene() const 
{
	RGBColor pixel_color;
	Ray ray;
	double zw = 100;
	double x, y;

	open_window(vp.hres, vp.vres);
	ray.d = Vector3D(0, 0, -1);

	for (int row = 0; row < vp.vres; row++)
	{
		for (int col = 0; col < vp.hres; col++)
		{
			x = vp.s * (col - 0.5 * (vp.hres - 1.0));
			y = vp.s * (row - 0.5 * (vp.vres - 1.0));
			ray.o = Point3D(x, y, zw);

			pixel_color = tracer_prt->trace_ray(ray);
			if (vp.gamma != 1.0)
				pixel_color = pixel_color.powc(vp.inv_gamma);

			display_pixel(row, col, pixel_color);
		}
	}
}

void 
World::open_window(const int hres, const int vres) const 
{
	// opening ...
}

void 
World::display_pixel(const int row, const int column, const RGBColor& color) const
{
	int x = column;
	int y = vp.vres - row - 1;

	/*if (vp.gamma != 1.0)
		color = color.powc(vp.inv_gamma);*/

	paintArea->setPixel(x, y, 
		(int)(color.r * 255),
		(int)(color.g * 255),
		(int)(color.b * 255));
}

void
World::setPaintArea(RenderThread* newPaintArea)
{
	paintArea = newPaintArea;
}

void
World::add_object(GeometricObject* object_ptr)
{
	objects.push_back(object_ptr);
}

ShadeRec
World::hit_bare_bones_objects(const Ray& ray) const
{
	ShadeRec sr(*this);
	double t;
	double tmin = kHugeValue;

	for (auto object : objects)
	{
		if (object->hit(ray, t, sr) && t < tmin)
		{
			sr.hit_an_object = true;
			sr.color = object->get_color(); 
			tmin = t;
		}
	}

	return sr;
}