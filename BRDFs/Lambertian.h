#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include "BRDF.h"

class Lambertian:public BRDF
{
public:
	Lambertian();
	Lambertian(const Lambertian& obj);
	~Lambertian();

	virtual Lambertian* Clone() const;
	virtual RGBColor F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const override;
	/*virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wi, const Vector3D &wo) const;
	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D & wi, const Vector3D &wo, float &pdf) const;*/
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D &wo) const override;

	Lambertian& operator=(const Lambertian& rhs);

	void SetKd(const float k);
	void SetCd(const RGBColor& c);
	void SetCd(const float r, const float g, const float b);
	void SetCd(const float c);
private:
	float kd;
	RGBColor cd;
};


inline void Lambertian::SetKd(const float k)
{
	kd = k;
}

inline void Lambertian::SetCd(const RGBColor & c)
{
	cd = c;
}

inline void Lambertian::SetCd(const float r, const float g, const float b)
{
	cd.r = r; cd.g = g; cd.b = b;
}

inline void Lambertian::SetCd(const float c)
{
	cd.r = c; cd.g = c; cd.b = c;
}

#endif //_LAMBERTIAN_H_



