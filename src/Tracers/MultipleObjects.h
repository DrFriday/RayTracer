#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.h"

#include "../World/World.h"

class MultipleObjects : public Tracer
{
public:
	MultipleObjects(World* world);
	RGBColor trace_ray(const Ray& ray) const;
};

#endif // __MULTIPLE_OBJECTS__