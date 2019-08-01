#ifndef __TRACER__
#define __TRACER__

#include <memory>

class World;

class Tracer 
{
public:
	Tracer();
	Tracer(World* world);
protected:
	World* world;
};

#endif // __TRACER__