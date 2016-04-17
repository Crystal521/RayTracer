#ifndef _RAY_H_
#define _RAY_H_
#include "Point3D.h"
#include "Vector3D.h"

class Ray
{
public:
	Ray();
	Ray(const Point3D &origin, const Vector3D &direction);
	Ray(const Ray & ray);
	~Ray();

	Point3D o;
	Vector3D d;

	Ray & operator = (const Ray & rhs);
private:

};


#endif
