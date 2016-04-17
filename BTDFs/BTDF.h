#ifndef _BTDF_H_
#define _BTDF_H_

#include <math.h>

#include "RGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"

class Sampler;
class BTDF
{
public:
	BTDF();
	BTDF(const BTDF &object);
	//BTDF(Sampler* pSampler);
	virtual ~BTDF();


	virtual BTDF* Clone() const = 0;
	//·µ»ØBTDF
	virtual RGBColor F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const;
	
	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wo, Vector3D &wt) const;
	//virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wi, const Vector3D &wo, float &pdf) const = 0;

	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D &wo) const;
protected:
	BTDF& operator = (const BTDF& rhs);
};

#endif//_BTDF_H_