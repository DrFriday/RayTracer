#ifndef _RAY_H_
#define _RAY_H_

#include "../util/point3.h"
#include "../util/vec3x1.h"

class Ray {
public:

	Point3 origin;
	Vec3x1 direction;

	Ray() = default;
	Ray(const Point3& origin, const Vec3x1& dir);
	Ray(const Ray& ray);

	Ray& operator= (const Ray& rhs);

};

#endif