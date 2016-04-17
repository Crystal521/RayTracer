#include "Ambient.h"

Ambient::Ambient()
	:Light(),
	ls(1.0f),
	color(1.0)//Ä¬ÈÏ°×¹â
{
}

Ambient::Ambient(const Ambient& ambient)
	:Light(ambient),
	ls(ambient.ls),
	color(ambient.color)
{
}
Ambient::~Ambient()
{
}

Light* Ambient::Clone() const 
{
	return new Ambient(*this);
}

Ambient& Ambient::operator=(const Ambient& rhs)
{
	if (this == &rhs)
		return *this;

	Light::operator=(rhs);
	ls = rhs.ls;
	color = rhs.color;

	return *this;
}

Vector3D Ambient::GetDirection(ShadeRec& s)
{
	return (Vector3D(0.0f));
}

RGBColor Ambient::L(ShadeRec& s)
{
	return ls*color;
}

bool Ambient::IsInShadow(const Ray& ray, ShadeRec& sr)const
{
	return false;
}