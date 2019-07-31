#ifndef __SINGLE_SPHERE__
#define __SINGLE_SPHERE__

#include "Tracer.h"

#include "../World/World.h"

class SingleSphere : Tracer
{
private:
	World world;
public:
	SingleSphere(World& w);
};

#endif // __SINGLE_SPHERE__