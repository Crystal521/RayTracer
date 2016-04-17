#ifndef _BRDF_H_
#define _BRDF_H_

#include <math.h>

#include "RGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"

class Sampler;
class BRDF
{
public:
	BRDF();
	BRDF(const BRDF &object);
	//BRDF(Sampler* pSampler);
	virtual ~BRDF();


	virtual BRDF* Clone() const = 0;
	//·µ»ØBRDF
	virtual RGBColor F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const;
	//
	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wo, Vector3D &wi) const ;

	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wo, Vector3D &wi, float &pdf) const;

	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D &wo) const ;

protected:
	BRDF& operator = (const BRDF& rhs);
};

#endif//_BRDF_H_