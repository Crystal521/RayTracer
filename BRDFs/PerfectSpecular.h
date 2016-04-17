#ifndef _PERFECT_SPECULAR_H_
#define _PERFECT_SPECULAR_H_

#include "BRDF.h"

class Sampler;
class PerfectSpecular : public BRDF
{
public:
	PerfectSpecular();
	PerfectSpecular(const PerfectSpecular &object);
	//PerfectSpecular(Sampler* pSampler);
	~PerfectSpecular();


	virtual PerfectSpecular* Clone() const;
	//返回PerfectSpecular
	virtual RGBColor F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const override;
	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const override;
	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const override;
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D &wo) const override;

	void SetKr(const float k);
	void SetCr(const RGBColor& c);
	void SetCr(const float r, const float g, const float b);
	void SetCr(const float c);
	//void SetNormal(const Normal& n);

	PerfectSpecular& operator = (const PerfectSpecular& rhs);

private:
	
	float kr;		 //镜面反射系数
	RGBColor cr;	 //镜面反射颜色
};


inline void PerfectSpecular::SetKr(const float k)
{
	kr = k;
}

inline void PerfectSpecular::SetCr(const RGBColor & c)
{
	cr = c;
}

inline void PerfectSpecular::SetCr(const float r, const float g, const float b)
{
	cr.r = r; cr.g = g; cr.b = b;
}

inline void PerfectSpecular::SetCr(const float c)
{
	cr.r = c; cr.g = c; cr.b = c;
}

#endif//_PERFECT_SPECULAR_H_