#include "Sphere.h"
#include "../Utilities/Constants.h"

bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double t;
	Vector3D temp = ray.o - center;
	double a = ray.d * ray.d;
	double b = 2.0 * temp * ray.d;
	double c = temp * temp - radius * radius;
    double discriminant = b * b - 4.0 * a * c;

	// Complex roots
    if (discriminant < 0.0)
	{
		return false;
	}
	// discriminant = 0.0, one real root, no plus and minus
	// discriminant > 0.0, two real roots, has plus and minus
	else
	{
        double e = sqrt(discriminant);
		double denom = 2.0 * a;
		t = (-b - e) / denom; // smaller root

		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}

		t = (-b + e) / denom; // larger root

		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}
	}

	return false;
}


void Sphere::set_center(const double newCenter)
{
	center = newCenter;
}

void Sphere::set_center(const Point3D newCenter)
{
	center = newCenter;
}

void Sphere::set_radius(const double newRadius)
{
	radius = newRadius;
}
