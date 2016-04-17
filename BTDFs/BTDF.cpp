#include "BTDF.h"
#include "Constants.h"
BTDF::BTDF()
{}

BTDF::~BTDF()
{}

BTDF::BTDF(const BTDF &object)
{}

BTDF& BTDF::operator = (const BTDF& rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

RGBColor BTDF::F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const
{
	return black;
}

RGBColor BTDF::SamplerF(const ShadeRec& sr, const Vector3D & wo, Vector3D &wt) const
{
	return black;
}


RGBColor BTDF::Rho(const ShadeRec& sr, const Vector3D &wo) const
{
	return black;
}