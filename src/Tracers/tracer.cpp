#include "Tracer.h"
#include "../Utilities/Constants.h"

Tracer::Tracer()
	: world_ptr(nullptr)
{}

Tracer::Tracer(World* world)
	: world_ptr(world)
{}

RGBColor 
Tracer::trace_ray(const Ray& ray) const
{
	return black;
}