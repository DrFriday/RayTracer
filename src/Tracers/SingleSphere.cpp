#include "SingleSphere.h"

#include "../Utilities/Constants.h"

SingleSphere::SingleSphere(World* world)
	: Tracer(world)
{}

RGBColor
SingleSphere::trace_ray(const Ray& ray) const
{
	ShadeRec sr(*world_ptr);
	double t;

	if (world_ptr->sphere.hit(ray, t, sr))
	{
		return red;
	}
	else
	{
		return black;
	}
}