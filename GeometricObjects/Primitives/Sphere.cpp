#include "Sphere.h"
#include <math.h>
const double Sphere::kEpsilon = 0.001;
Sphere::Sphere()
	:GeometricObject(),
	center(0,0,0),
	radius(1.0f),
	rr(1.0f)
{}

Sphere::Sphere(const Sphere & sphere)
	:GeometricObject(sphere),
	center(sphere.center),
	radius(sphere.radius),
	rr(sphere.rr)
{}

Sphere::Sphere(const Point3D c, double r)
	:GeometricObject(),
	center(c),
	radius(r),
	rr(r*r)
{}

Sphere::~Sphere()
{}

bool Sphere::Hit(const Ray & ray, double & tmin, ShadeRec & s) const
{
	//求光线（直线）与球表面相交时参数t的大小
	//r = o + t*d 直线的参数方程
	//0 = (point - center)*(point - center) - radius*radius 球体方程
	//两者相交通过二元一次方程求解
	double t;
	Vector3D temp = ray.o - center;//优化
	double a = ray.d*ray.d;
	double b = 2 * temp*ray.d;
	double c = temp*temp - radius*radius;
	double disc = b*b - 4.0 * a*c;

	if (disc < 0)
		return false;
	
	double e = sqrt(disc);
	double demon = 2 * a;//分母
	t = (-b - e) / demon;
	if (t > kEpsilon)
	{
		tmin = t;
		s.isHit = true;
		s.localHitPoint = ray.o + t * ray.d;
		s.normal = (temp + t * ray.d) / radius;

		return true;
	}

	t = (-b + e) / demon;
	if (t > kEpsilon)
	{
		tmin = t;
		s.isHit = true;
		s.localHitPoint = ray.o + t * ray.d;
		s.normal = (temp + t * ray.d) / radius;

		return true;
	}
	return false;
}

Sphere * Sphere::Clone() const
{
	return new Sphere(*this);
}

Sphere & Sphere::operator=(const Sphere & rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);
	center = rhs.center;
	radius = rhs.radius;

	return (*this);
}

bool Sphere::ShadowHit(const Ray& ray, float &tmin) const
{

	//求光线（直线）与球表面相交时参数t的大小
	//r = o + t*d 直线的参数方程
	//0 = (point - center)*(point - center) - radius*radius 球体方程
	//两者相交通过二元一次方程求解
	float t;
	Vector3D temp = ray.o - center;//优化
	double a = ray.d*ray.d;
	double b = 2 * temp*ray.d;
	double c = temp*temp - radius*radius;
	double disc = b*b - 4.0 * a*c;

	if (disc < 0)
		return false;

	double e = sqrt(disc);
	double demon = 2 * a;//分母
	t = (-b - e) / demon;
	if (t > kEpsilon)
	{
		tmin = t;
		return true;
	}

	t = (-b + e) / demon;
	if (t > kEpsilon)
	{
		tmin = t;
		return true;
	}
	return false;

	////碰撞点指向球心的向量
	//Vector3D oc = ray.o - center;
	//double ll = oc * oc;
	////向量oc在阴影光线的方向上的投影长度
	//double d = oc * ray.d;
	////表明球心在碰撞点之后且光源在球体之外
	//if (d < 0 && ll > rr)
	//	return false;
	////半弦长的平方
	//double hh = rr - (ll - d*d);
	////半弦长为表明光线与球无交点
	//if (hh<0)
	//	return false;
	////光源在球体之外时，取距离较小的点为第一交点
	//if (ll > rr)
	//{
	//	tmin = d - sqrt(hh);
	//	return true;
	//}
	//else //光源在球体之内或之上时，取距离较大的点为第一交点
	//	tmin = d + sqrt(hh);
	//return true;
}
