#include "Ray.h"

Ray::Ray()
	:o(0), d(0, 0, 1.0f)
{}

Ray::Ray(const Point3D &origin, const Vector3D &direction)
	: o(origin), d(direction)
{}

Ray::Ray(const Ray & ray)
	: o(ray.o), d(ray.d)
{}

Ray::~Ray()
{}

Ray & Ray::operator=(const Ray & rhs)
{
	if (this == &rhs)
		return (*this);

	o = rhs.o;
	d = rhs.d;

	return (*this);
}
