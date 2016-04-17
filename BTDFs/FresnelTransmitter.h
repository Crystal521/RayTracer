
#ifndef _FRESNEL_TRANSMITTER_H_
#define _FRESNEL_TRANSMITTER_H_

#include"BTDF.h"
class FresnelTransmitter :public BTDF
{
public:
	FresnelTransmitter();
	FresnelTransmitter(const FresnelTransmitter& pt);
	~FresnelTransmitter();
	FresnelTransmitter& operator = (const FresnelTransmitter& rhs);

	virtual FresnelTransmitter* Clone() const;
	//返回BTDF
	virtual RGBColor F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const override;
	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wo, Vector3D &wt) const override;
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D &wo) const override;
	
	
	//判断是否发生全内反射
	bool Tir(const ShadeRec& sr) const;

	void SetEtaIn(const float& in);
	void SetEtaOut(const float& out);
private:
	float etaIn;
	float etaOut;

	//计算折射系数Kt
	float Fresnel(const ShadeRec& sr) const;
};

inline void FresnelTransmitter::SetEtaIn(const float& in)
{
	etaIn = in;
}
inline void FresnelTransmitter::SetEtaOut(const float& out)
{
	etaOut = out;
}

#endif//_PERFECT_TRANSMITTER_H_
