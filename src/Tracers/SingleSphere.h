#ifndef __SINGLE_SPHERE__
#define __SINGLE_SPHERE__

#include "Tracer.h"

#include "../World/World.h"

class SingleSphere : public Tracer
{
public:
	SingleSphere(World* world);
	RGBColor trace_ray(const Ray& ray) const override;
};

#endif // __SINGLE_SPHERE__