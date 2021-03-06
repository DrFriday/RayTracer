#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

class GeometricObject
{
public:
	virtual bool hit(const Ray& ray, double& min, ShadeRec& sr) const = 0;
	RGBColor get_color() const;
	void set_color(const RGBColor);
protected:
	RGBColor color;
};


#endif