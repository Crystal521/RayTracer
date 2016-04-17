#ifndef _TRANSPARENT_H_
#define _TRANSPARENT_H_
#include "Phong.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"
class Transparent:public Phong
{
public:
	Transparent();
	Transparent(const Transparent& ph);
	~Transparent();

	virtual Transparent* Clone() const;
	virtual RGBColor Shade(ShadeRec& sr);


	void  SetKr(const float& kr);
	void  SetIor(const float& ior);
	void  SetKt(const float& kt);
private:
	PerfectSpecular* reflectiveBRDF;
	PerfectTransmitter* specularBTDF;
};


inline void  Transparent::SetKr(const float& kr)
{
	reflectiveBRDF->SetKr(kr);
}
inline void  Transparent::SetIor(const float& ior)
{
	specularBTDF->SetIor(ior);
}
inline void  Transparent::SetKt(const float& kt)
{
	specularBTDF->SetKt(kt);
}
#endif //_TRANSPARENT_H_