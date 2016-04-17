#include "BBox.h"
#include <math.h>
#include "Maths.h"
#include "Constants.h"

BBox::BBox()
	: x0(-1), y0(-1), z0(-1),
	x1(1), y1(1), z1(1)
{
}

BBox::~BBox()
{}

BBox::BBox(const Point3D& a, const Point3D& b)
	:x0(a.x), y0(a.y), z0(a.z),
	x1(b.x), y1(b.y), z1(b.z)
{
}

BBox::BBox(const BBox& box)
	: x0(box.x0), y0(box.y0), z0(box.z0),
	x1(box.x1), y1(box.y1), z1(box.z1)
{
}

BBox::BBox(const double xmin, const double xmax,
	const double ymin, const double ymax,
	const double zmin, const double zmax)
	: x0(xmin), y0(ymin), z0(zmin),
	x1(xmax), y1(ymax), z1(zmax)
{
}

bool BBox::Hit(const Ray& ray) const
{

	double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
	double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;
	double txmin, tymin, tzmin;
	double txmax, tymax, tzmax;

	//x0,y0,z0Ϊ��Χ�����С����
	//x1,y1,z1Ϊ��Χ�����󶥵�
	if (fabs(dx) < 0.000001f)
	{
		//�����߷���ʸ����x�����Ϊ0��ԭ�㲻�ں�����
		if (ox < x1 || ox > x0)
			return false;
	}
	else
	{
		if (dx >= 0)
		{
			txmin = (x0 - ox) / dx;
			txmax = (x1 - ox) / dx;
		}
		else
		{
			txmin = (x1 - ox) / dx;
			txmax = (x0 - ox) / dx;
		}

	}


	if (fabs(dy) < 0.000001f)
	{
		//�����߷���ʸ����x�����Ϊ0��ԭ�㲻�ں�����
		if (oy < y1 || oy > y0)
			return false;
	}
	else
	{
		if (dy >= 0)
		{
			tymin = (y0 - oy) / dy;
			tymax = (y1 - oy) / dy;
		}
		else
		{
			tymin = (y1 - oy) / dy;
			tymax = (y0 - oy) / dy;
		}

	}


	if (fabs(dz) < 0.000001f)
	{
		//�����߷���ʸ����x�����Ϊ0��ԭ�㲻�ں�����
		if (oz < z1 || oz > z0)
			return false;
	}
	else
	{
		if (dz >= 0)
		{
			tzmin = (z0 - oz) / dz;
			tzmax = (z1 - oz) / dz;
		}
		else
		{
			tzmin = (z1 - oz) / dz;
			tzmax = (z0 - oz) / dz;
		}

	}

	double t0, t1;

	//���߽���ƽ�洦�������ƽ�棩�����tֵ 
	t0 = max(tzmin, max(txmin, tymin));

	//�����뿪ƽ�洦����Զ���ƽ�棩����Сtֵ
	t1 = min(tzmax, min(txmax, tymax));

	return t0 < t1;
}

BBox& BBox::operator = (const BBox& rhs)
{
	if (this == &rhs)
		return *this;

	x0 = rhs.x0;
	x1 = rhs.x1;
	y0 = rhs.y0;
	y1 = rhs.y1;
	z0 = rhs.z0;
	z1 = rhs.z1;

	return *this;
}

//�����жϹ�������Ƿ��ں�����
bool BBox::Inside(const Point3D& p) const
{
	return (p.x > x0 && p.x < x1) && (p.y > y0 && p.y < y1) && (p.z > z0 && p.z < z1);
}