#include "ray.h"

Ray::Ray(const Point3D& origin, const Vector3D& dir)
	: origin(origin)
	, direction(dir)
{};

Ray::Ray(const Ray& ray)
	: origin(ray.origin)
	, direction(ray.direction)
{};

Ray&
Ray::operator= (const Ray& rhs)
{
	origin = rhs.origin;
	direction = rhs.direction;

	return *this;
}