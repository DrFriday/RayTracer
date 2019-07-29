#ifndef __SPHERE__
#define __SPHERE__

#include "GeometricObject.h"
#include "../Utilities/Point3D.h"

class Sphere : GeometricObject {

public:
	bool hit(const Ray& ray, double& min, ShadeRec& sr) const;
private:
	Point3D center;
	double radius;
};

#endif // __SPHERE__