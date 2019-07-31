#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

class World;


class GeometricObject
{
public:
	virtual bool hit(const Ray& ray, double& min, ShadeRec& sr) const = 0;
protected:
	RGBColor color;
};


#endif