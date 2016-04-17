#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "GeometricObject.h"


class Sphere : public GeometricObject
{
public:
	Sphere();
	Sphere(const Sphere& sphere);
	Sphere(const Point3D center, double radius);

	virtual ~Sphere();
	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec& s)const override;
	virtual bool ShadowHit(const Ray& ray, float &tmin) const override;
	virtual Sphere * Clone() const override;

	Sphere & operator=(const Sphere &rhs);
	void SetCenter(const Point3D & c);
	void SetCenter(const double x, const double y, const double z);
	void SetRadius(double r);
private:
	//圆心
	Point3D center;
	//半径
	double radius;
	//radius*radius，用于优化
	double rr;
	//用于阴影的计算和次光线
	static const double kEpsilon;
};



inline void Sphere::SetCenter(const Point3D & c)
{
	center = c;
}

inline void Sphere::SetCenter(const double x, const double y, const double z)
{
	center.x = x;
	center.y = y;
	center.z = z;
}

inline void Sphere::SetRadius(double r)
{
	radius = r;
	rr = r*r;
}

#endif //_SPHERE_H_

