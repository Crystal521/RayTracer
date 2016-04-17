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
	//����ߣ�ֱ�ߣ���������ཻʱ����t�Ĵ�С
	//r = o + t*d ֱ�ߵĲ�������
	//0 = (point - center)*(point - center) - radius*radius ���巽��
	//�����ཻͨ����Ԫһ�η������
	double t;
	Vector3D temp = ray.o - center;//�Ż�
	double a = ray.d*ray.d;
	double b = 2 * temp*ray.d;
	double c = temp*temp - radius*radius;
	double disc = b*b - 4.0 * a*c;

	if (disc < 0)
		return false;
	
	double e = sqrt(disc);
	double demon = 2 * a;//��ĸ
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

	//����ߣ�ֱ�ߣ���������ཻʱ����t�Ĵ�С
	//r = o + t*d ֱ�ߵĲ�������
	//0 = (point - center)*(point - center) - radius*radius ���巽��
	//�����ཻͨ����Ԫһ�η������
	float t;
	Vector3D temp = ray.o - center;//�Ż�
	double a = ray.d*ray.d;
	double b = 2 * temp*ray.d;
	double c = temp*temp - radius*radius;
	double disc = b*b - 4.0 * a*c;

	if (disc < 0)
		return false;

	double e = sqrt(disc);
	double demon = 2 * a;//��ĸ
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

	////��ײ��ָ�����ĵ�����
	//Vector3D oc = ray.o - center;
	//double ll = oc * oc;
	////����oc����Ӱ���ߵķ����ϵ�ͶӰ����
	//double d = oc * ray.d;
	////������������ײ��֮���ҹ�Դ������֮��
	//if (d < 0 && ll > rr)
	//	return false;
	////���ҳ���ƽ��
	//double hh = rr - (ll - d*d);
	////���ҳ�Ϊ�������������޽���
	//if (hh<0)
	//	return false;
	////��Դ������֮��ʱ��ȡ�����С�ĵ�Ϊ��һ����
	//if (ll > rr)
	//{
	//	tmin = d - sqrt(hh);
	//	return true;
	//}
	//else //��Դ������֮�ڻ�֮��ʱ��ȡ����ϴ�ĵ�Ϊ��һ����
	//	tmin = d + sqrt(hh);
	//return true;
}
