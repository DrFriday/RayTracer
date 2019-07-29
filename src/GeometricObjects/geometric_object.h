#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "../util/rgb_color.h"
#include "../util/ray.h"
#include "../util/shade_rec.h"

class World;


class GeometricObject {
public:
	virtual bool hit(Ray& ray, double& min, ShadeRec& sr);
protected:
	RGBColor color;
};


#endif