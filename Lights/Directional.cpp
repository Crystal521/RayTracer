
#include "World.h"
#include "Directional.h"

Directional::Directional()
	:Light(),
	ls(1.0f),
	dir(0.0f,1.0f,0.0f),
	color(1.0f)//Ä¬ÈÏ°×¹â
{
}

Directional::Directional(const Directional& directional)
	:Light(directional),
	ls(directional.ls),
	dir(directional.dir),
	color(directional.color)
{
}
Directional::~Directional()
{
}

Light* Directional::Clone() const
{
	return new Directional(*this);
}

Directional& Directional::operator=(const Directional& rhs)
{
	if (this == &rhs)
		return *this;

	Light::operator=(rhs);
	ls = rhs.ls;
	color = rhs.color;
	dir = rhs.dir;

	return *this;
}

Vector3D Directional::GetDirection(ShadeRec& s)
{
	return dir;
}

RGBColor Directional::L(ShadeRec& s)
{
	return ls*color;
}

bool Directional::IsInShadow(const Ray& ray, ShadeRec& sr)const
{
	float t;
	int num = sr.w.objects.size();

	for (int i = 0; i < num; i++)
	{
		if (sr.w.objects[i]->ShadowHit(ray, t))
			return true;
	}
	return false;
}