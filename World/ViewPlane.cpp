#include "ViewPlane.h"


ViewPlane::ViewPlane()
	: hres(400),
	vres(400),
	pixelSize(1.0),
	numSamples(1),
	gamma(1.0),
	invGamma(1.0),
	showOutOfGamut(false)
{
}

ViewPlane::ViewPlane(const ViewPlane & vp)
	: hres(vp.hres),
	vres(vp.vres),
	pixelSize(vp.pixelSize),
	numSamples(vp.numSamples),
	gamma(vp.gamma),
	invGamma(vp.invGamma),
	showOutOfGamut(vp.showOutOfGamut)
{
}

ViewPlane & ViewPlane::operator=(const ViewPlane & rhs)
{
	if (this == &rhs)
		return (*this);

	hres = rhs.hres;
	vres = rhs.vres;
	pixelSize = rhs.pixelSize;
	numSamples = rhs.numSamples;
	gamma = rhs.gamma;
	invGamma = rhs.invGamma;
	showOutOfGamut = rhs.showOutOfGamut;

	return *this;
}

ViewPlane::~ViewPlane()
{
}
