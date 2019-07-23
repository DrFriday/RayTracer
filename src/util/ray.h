#ifndef _RAY_H_
#define _RAY_H_

#include "point3D.h"
#include "vector3D.h"

class Ray {
public:

	Point3D origin;
	Vector3D direction;

	Ray() = default;
	Ray(const Point3D& origin, const Vector3D& dir);
	Ray(const Ray& ray);

	Ray& operator= (const Ray& rhs);

};

#endif