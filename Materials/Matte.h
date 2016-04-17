#ifndef _MATTE_H_
#define _MATTE_H_

#include "ShadeRec.h"
#include "Material.h"
#include "Lambertian.h"
class Matte:public Material
{
public:
	Matte();
	Matte(const Matte& matte);
	virtual ~Matte();

	virtual Matte* Clone() const override;
	virtual RGBColor Shade(ShadeRec& sr);

	Matte& operator=(const Matte& rhs);

	void SetKa(const float a);//设置环境光的系数
	void SetKd(const float d);//设置漫反光的系数

	void SetCd(const RGBColor c);
	void SetCd(const float r, const float g, const float b);
	void SetCd(const float c);
private:
	Lambertian*		ambientBRDF;
	Lambertian*		diffuseBRDF;
};


inline void Matte::SetKa(const float a)
{
	ambientBRDF->SetKd(a);
}
inline void Matte::SetKd(const float d)
{
	diffuseBRDF->SetKd(d);
}

inline void Matte::SetCd(const RGBColor c)
{
	ambientBRDF->SetCd(c);
	diffuseBRDF->SetCd(c);
}
inline void Matte::SetCd(const float r, const float g, const float b)
{
	ambientBRDF->SetCd(r,g,b);
	diffuseBRDF->SetCd(r, g, b);
}
inline void Matte::SetCd(const float c)
{
	ambientBRDF->SetCd(c);
	diffuseBRDF->SetCd(c);
}
#endif//_MATTE_H_