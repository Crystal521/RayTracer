#include "Triangle.h"
#include "Maths.h"
#include "Constants.h"

Triangle::Triangle()
	:GeometricObject(),
	v0(0, 0, 0), v1(1,0,0),
	v2(0, 0, 1), normal(0, 1, 0)
{
}

Triangle::Triangle(Point3D v0, Point3D v1, Point3D v2)
	:GeometricObject(),
	v0(v0), v1(v1),
	v2(v2)
{
	ComputeNormal();
}

Triangle::Triangle(const Triangle& rhs)
	:GeometricObject(rhs),
	v0(rhs.v0), v1(rhs.v1),
	v2(rhs.v2), normal(rhs.normal)
{
}

Triangle::~Triangle(){}

void  Triangle::ComputeNormal()
{
	normal = (v2 - v0) ^ (v1 - v0);
	normal.normalize();
}

bool Triangle::Hit(const Ray& ray, double& tmin, ShadeRec &sr) const
{
	//求解光线与三角形相交,三角形上的任意一点p可通过方程p=a+beta*(b-a)+gamma*(c-a)求得
	//beta与gamma以及t为未知，o+t*d = a+beta*(b-a)+gamma*(c-a)
	//beta*(ax-bx)+gamma(ax-cx)+t*dx = ax-ox
	//beta*(ay-by)+gamma(ay-cy)+t*dy = ay-oy
	//beta*(az-bz)+gamma(az-cz)+t*dz = az-oz
	//可以变成矩阵形式再通过克莱姆法则求解上述beta与gamma以及t
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
	double q = g*i - e*k, s = e*j - f*i;

	double invDenom = 1.0 / (a*m + b*q + c*s);

	double e1 = d*m - b*n - c*p;
	double beta = e1*invDenom;

	if (beta < 0 || beta>1)
		return false;

	double r = e*l - h*i;
	double e2 = a*n + d*q + c*r;
	double gamma = e2*invDenom;

	if (gamma < 0 || gamma>1)
		return false;
	if (gamma + beta > 1)
		return false;

	double e3 = a*p - b*r + d*s;
	double t = e3*invDenom;

	if (t < kEpsilon)
		return false;

	tmin = t;
	sr.normal = normal;
	sr.hitPoint = ray.o + t*ray.d;
	return true;
}

Triangle* Triangle::Clone() const
{
	return new Triangle(*this);
}

bool Triangle::ShadowHit(const Ray& ray, float &tmin) const
{
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
	double q = g*i - e*k, s = e*j - f*i;

	double invDenom = 1.0 / (a*m + b*q + c*s);

	double e1 = d*m - b*n - c*p;
	double beta = e1*invDenom;

	if (beta < 0 || beta>1)
		return false;

	double r = e*l - h*i;
	double e2 = a*n + d*q + c*r;
	double gamma = e2*invDenom;

	if (gamma < 0 || gamma>1)
		return false;
	if (gamma + beta > 1)
		return false;

	double e3 = a*p - b*r + d*s;
	double t = e3*invDenom;

	if (t < kEpsilon)
		return false;

	tmin = t;
	return true;
}


BBox Triangle::GetBoundingBox()
{
	double delta = 0.000001;
	return BBox(
		min(v0.x, min(v1.x, v2.x)) - delta, max(v0.x, max(v1.x, v2.x)) + delta,
		min(v0.y, min(v1.y, v2.y)) - delta, max(v0.y, max(v1.y, v2.y)) + delta,
		min(v0.z, min(v1.z, v2.z)) - delta, max(v0.z, max(v1.z, v2.z)) + delta);
}

Triangle& Triangle::operator=(const Triangle& rhs)
{
	if(this == &rhs)
		return *this;

	GeometricObject::operator=(rhs);
	v0 = rhs.v0;
	v1 = rhs.v1;
	v2 = rhs.v2;
	normal = rhs.normal;

	return *this;
}