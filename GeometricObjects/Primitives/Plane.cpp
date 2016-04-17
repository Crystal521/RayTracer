#include "Plane.h"

const double Plane::kEpsilon = 0.001;
Plane::Plane()
	:GeometricObject(), point(0), normal(0, 1, 0)
{}

Plane::Plane(const Point3D p, const Normal & n)
	: GeometricObject(), point(p), normal(n)
{
	normal.normalize();
}

Plane::Plane(const Plane& plane)
	: GeometricObject(plane),
	point(plane.point),
	normal(plane.normal)
{}


Plane* Plane::Clone() const 
{
	return (new Plane(*this));
}


// ---------------------------------------------------------------- assignment operator

Plane& Plane::operator= (const Plane& rhs) 
{

	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);
	point = rhs.point;
	normal = rhs.normal;

	return (*this);
}



Plane::~Plane()
{}

bool Plane::Hit(const Ray & ray, double& tmin, ShadeRec & s) const
{
	//����ߣ�ֱ�ߣ���ƽ���ཻʱ����t�Ĵ�С
	//r = o + t*d ֱ�ߵĲ�������
	//p = (point - a)*n ƽ��ĵ㷨ʽ����
	double t = (point - ray.o)*normal / (ray.d *normal);

	if (t > kEpsilon)
	{
		tmin = t;
		/*s.isHit = true;*/
		s.localHitPoint = ray.o + t*ray.d;
		s.normal = normal;
		return true;
	}

	return false;
}

bool Plane::ShadowHit(const Ray& ray, float &tmin) const
{
	//����ߣ�ֱ�ߣ���ƽ���ཻʱ����t�Ĵ�С
	//r = o + t*d ֱ�ߵĲ�������
	//p = (point - a)*n ƽ��ĵ㷨ʽ����
	double t = (point - ray.o)*normal / (ray.d *normal);

	if (t > kEpsilon)
	{
		tmin = t;
		return true;
	}

	return false;
}
