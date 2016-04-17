#include "Lambertian.h"
#include "Constants.h"


Lambertian::Lambertian()
	:BRDF()
{
}

Lambertian::Lambertian(const Lambertian & obj)
	: BRDF(obj), kd(obj.kd), cd(obj.cd)
{
}

Lambertian::~Lambertian()
{
}

Lambertian * Lambertian::Clone() const
{
	return (new Lambertian(*this));
}

RGBColor Lambertian::F(const ShadeRec & sr, const Vector3D & wo, const Vector3D & wi) const
{
	return kd*cd*invPI;
}

RGBColor Lambertian::Rho(const ShadeRec & sr, const Vector3D & wo) const
{
	return kd*cd;
}

Lambertian & Lambertian::operator=(const Lambertian & rhs)
{
	if (this == &rhs)
		return *this;
	
	BRDF::operator= (rhs);
	kd = rhs.kd;
	cd = rhs.cd;

	return *this;
}

