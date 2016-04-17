#include "PointLight.h"
#include "ShadeRec.h"
#include <math.h>
#include "World.h"

PointLight::PointLight()
	:Light(),
	ls(1.0f),
	a0(0.0f),
	a1(1.0f),
	a2(0.0f),
	location(0.0f, 1.0f, 0.0f),
	color(1.0f)//Ĭ�ϰ׹�
{
}

PointLight::PointLight(const PointLight& pl)
	:Light(pl),
	ls(pl.ls),
	a0(pl.a0),
	a1(pl.a1),
	a2(pl.a2),
	location(pl.location),
	color(pl.color)
{
}
PointLight::~PointLight()
{
}

Light* PointLight::Clone() const
{
	return new PointLight(*this);
}

PointLight& PointLight::operator=(const PointLight& rhs)
{
	if (this == &rhs)
		return *this;

	Light::operator=(rhs);
	ls = rhs.ls;
	color = rhs.color;
	location = rhs.location;

	return *this;
}

Vector3D PointLight::GetDirection(ShadeRec& s)
{
	return (location-s.hitPoint).hat();
}

RGBColor PointLight::L(ShadeRec& s)
{
	//������ù���ǿ��L=Io/��a0 + a1*d + a2* d^2���Ĺ�ʽ
	//������Ը��õĿ��Ƶ��Դ��Ч��
	double d = (location - s.hitPoint).length();
	double temp = a0 + a1*d + a2*pow(d, 2);
	return ls*color / temp;
}

bool PointLight::IsInShadow(const Ray& ray, ShadeRec& sr)const
{
	float t;
	int num = sr.w.objects.size();
	float d = location.distance(ray.o);

	for (int i = 0; i < num; i++)
	{
		if (sr.w.objects[i]->ShadowHit(ray, t) && t < d)
			return true;
	}
	return false;
}
