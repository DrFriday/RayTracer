#ifndef __SPHERE__
#define __SPHERE__

#include "GeometricObject.h"
#include "../Utilities/Point3D.h"

class Sphere : public GeometricObject 
{

public:
	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	void set_center(const double newCenter);
	void set_center(const Point3D newCenter);

	void set_radius(const double newRadius);


private:
	Point3D center;
	double radius;
};

#endif // __SPHERE__