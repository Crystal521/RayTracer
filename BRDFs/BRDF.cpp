#include "BRDF.h"
#include "Constants.h"

BRDF::BRDF()
{
}

BRDF::BRDF(const BRDF & object)
{
}

BRDF::~BRDF()
{
}


RGBColor BRDF::F(const ShadeRec & sr, const Vector3D & wo, const Vector3D & wi) const
{
	return black;
}

RGBColor BRDF::SamplerF(const ShadeRec & sr, const Vector3D & wo, Vector3D & wi) const
{
	return black;
}

RGBColor BRDF::SamplerF(const ShadeRec & sr, const Vector3D & wo, Vector3D & wi, float & pdf) const
{
	return black;
}

RGBColor BRDF::Rho(const ShadeRec & sr, const Vector3D & wo) const
{
	return black;
}

BRDF & BRDF::operator=(const BRDF & rhs)
{
	if (this == &rhs)
		return *this;

	return *this;
}
