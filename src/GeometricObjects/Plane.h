#ifndef _PLANE_H_
#define _PLANE_H_

#include "GeometricObject.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

class Plane : public GeometricObject
{
public:
	Plane();
	Plane(const Point3D, const Normal);

	virtual bool
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
private:
	Point3D point;
	Normal normal;
	static const double kEpsilon;
};


#endif // _PLANE_H_