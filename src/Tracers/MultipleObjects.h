#pragma once

#include "Tracer.h"

#include "../World/World.h"

class MultipleObjects : public Tracer
{
public:
	MultipleObjects(World* world);
	RGBColor trace_ray(const Ray& ray) const override;
};