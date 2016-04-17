#ifndef _PERFECT_TRANSMITTER_H_
#define _PERFECT_TRANSMITTER_H_
#include"BTDF.h"
class PerfectTransmitter:public BTDF
{
public:
	PerfectTransmitter();
	PerfectTransmitter(const PerfectTransmitter& pt);
	~PerfectTransmitter();
	PerfectTransmitter& operator = (const PerfectTransmitter& rhs);

	virtual PerfectTransmitter* Clone() const;
	//返回BTDF
	virtual RGBColor F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const override;

	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wo, Vector3D &wt) const override;
	//virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wi, const Vector3D &wo, float &pdf) const override;

	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D &wo) const override;

	//判断是否发生全内反射
	bool Tir(const ShadeRec& sr) const;

	void SetIor(const float& Ior);
	void SetKt(const float& Kt);
private:
	float ior;
	float kt;
};

inline void PerfectTransmitter::SetIor(const float& Ior)
{
	ior = Ior;
}
inline void PerfectTransmitter::SetKt(const float& Kt)
{
	kt = Kt;
	
}

#endif//_PERFECT_TRANSMITTER_H_