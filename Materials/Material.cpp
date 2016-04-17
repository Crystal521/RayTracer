#include "Material.h"
#include "Constants.h"

Material::Material()
{
}

Material::Material(const Material& material)
{}

Material::~Material()
{
}

RGBColor Material::Shade(ShadeRec& sr)
{
	return black;
}

Material& Material::operator=(const Material& rhs)
{
	if (this == &rhs)
		return *this;

	return *this;
}