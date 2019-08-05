#ifndef __TRACER__
#define __TRACER__

#include <memory>

#include "../Utilities/Ray.h"

class World;

class Tracer 
{
public:
	Tracer();
	Tracer(World* world);
	virtual RGBColor trace_ray(const Ray& ray) const;
protected:
	World* world_ptr;
};

#endif // __TRACER__