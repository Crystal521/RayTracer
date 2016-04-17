#ifndef _PHONG_H_
#define _PHONG_H_

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong:public Material
{
public:
	Phong();
	Phong(const Phong& Phong);
	virtual ~Phong();

	virtual Phong* Clone() const;
	virtual RGBColor Shade(ShadeRec& sr);

	Phong& operator=(const Phong& rhs);

	void SetKa(const float a);//���û������ϵ��
	void SetKd(const float d);//�����������ϵ��
	void SetKs(const float s);//���ø߹��ϵ��
	void SetExp(const float e);//��������ֲ�ϵ��

	void SetCd(const RGBColor c);
	void SetCd(const float r, const float g, const float b);
	void SetCd(const float c);
private:
	Lambertian*		ambientBRDF;
	Lambertian*		diffuseBRDF;
	GlossySpecular* specularBRDF;
};


inline void Phong::SetKa(const float a)
{
	ambientBRDF->SetKd(a);
}
inline void Phong::SetKd(const float d)
{
	diffuseBRDF->SetKd(d);
}
inline void Phong::SetKs(const float s)
{
	specularBRDF->SetKs(s);
}

inline void Phong::SetExp(const float e)
{
	specularBRDF->SetExp(e);
}

inline void Phong::SetCd(const RGBColor c)
{
	ambientBRDF->SetCd(c);
	diffuseBRDF->SetCd(c);
	specularBRDF->SetCs(c);
}
inline void Phong::SetCd(const float r, const float g, const float b)
{
	ambientBRDF->SetCd(r, g, b);
	diffuseBRDF->SetCd(r, g, b);
	specularBRDF->SetCs(r, g, b);
}
inline void Phong::SetCd(const float c)
{
	ambientBRDF->SetCd(c);
	diffuseBRDF->SetCd(c);
	specularBRDF->SetCs(c);
}
#endif//_PHONG_H_