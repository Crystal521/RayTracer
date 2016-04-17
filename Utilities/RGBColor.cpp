#include "RGBColor.h"
#include <math.h> 

RGBColor::RGBColor()
	:r(0),g(0),b(0)
{}

RGBColor::RGBColor(float c)
	: r(c), g(c), b(c)
{}

RGBColor::RGBColor(float _r, float _g, float _b)
	:r(_r),g(_g),b(_b)
{}

RGBColor::RGBColor(const RGBColor & color)
	:r(color.r),g(color.g),b(color.b)
{}

RGBColor::~RGBColor()
{}

RGBColor & RGBColor::operator=(const RGBColor & rhs)
{
	if (this == &rhs)
		return (*this);

	r = rhs.r;
	g = rhs.g;
	b = rhs.b;

	return (*this);
}

RGBColor RGBColor::powc(float p) const
{
	return RGBColor(pow(r, p), pow(g, p), pow(b, p));
}