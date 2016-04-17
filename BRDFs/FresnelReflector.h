#ifndef _FRESNEL_REFLECTOR_H_
#define _FRESNEL_REFLECTOR_H_

#include"BRDF.h"
class FresnelReflector :public BRDF
{
public:
	FresnelReflector();
	FresnelReflector(const FresnelReflector& pt);
	~FresnelReflector();
	FresnelReflector& operator = (const FresnelReflector& rhs);

	virtual FresnelReflector* Clone() const;
	//返回BRDF
	virtual RGBColor F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const override;
	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wo, Vector3D &wr) const override;
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D &wo) const override;

	
	
	void SetEtaIn(const float& in);
	void SetEtaOut(const float& out);
private:
	float etaIn;
	float etaOut;

	//计算折射系数KR
	float Fresnel(const ShadeRec& sr) const;
};

inline void FresnelReflector::SetEtaIn(const float& in)
{
	etaIn = in;
}
inline void FresnelReflector::SetEtaOut(const float& out)
{
	etaOut = out;
}

#endif//_FRESNEL_REFLECTOR_H_
