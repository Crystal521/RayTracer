#ifndef _REFLECTIVE_H_
#define _REFLECTIVE_H_

#include "Phong.h"
#include "PerfectSpecular.h"

class Reflective:public Phong
{
public:
	Reflective();
	Reflective(const Reflective &object);
	~Reflective();

	Reflective& operator=(const Reflective& rhs);
	virtual Reflective* Clone() const override;
	virtual RGBColor Shade(ShadeRec& sr);

	void SetKr(const float a);//设置镜面发射光的系数

	void SetCr(const RGBColor c);
	void SetCr(const float r, const float g, const float b);
	void SetCr(const float c);
private:

	PerfectSpecular* reflectiveBRDF;
};


inline void Reflective::SetKr(const float a)
{
	reflectiveBRDF->SetKr(a);
}

inline void Reflective::SetCr(const RGBColor c)
{
	reflectiveBRDF->SetCr(c);
}
inline void Reflective::SetCr(const float r, const float g, const float b)
{
	reflectiveBRDF->SetCr(r, g, b);
}
inline void Reflective::SetCr(const float c)
{
	reflectiveBRDF->SetCr(c);
}

#endif//_REFLECTIVE_H_