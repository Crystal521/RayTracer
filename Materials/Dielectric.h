
#ifndef _DIELECTRIC_H_
#define _DIELECTRIC_H_
#include "Phong.h"
#include "FresnelTransmitter.h"
#include "FresnelReflector.h"

class Dielectric :public Phong
{
public:
	Dielectric();
	Dielectric(const Dielectric& ph);
	~Dielectric();

	virtual Dielectric* Clone() const;
	virtual RGBColor Shade(ShadeRec& sr);


	void  SetCfIn(const float c);
	void  SetCfOut(const float c);
	void  SetCfIn(const float r, const float g, const float b);
	void  SetCfOut(const float r, const float g, const float b);
	void  SetCfIn(const RGBColor c);
	void  SetCfOut(const RGBColor c);

	void  SetEtaIn(const float& eta);
	void  SetEtaOut(const float& eta);
private:
	RGBColor cfIn;
	RGBColor cfOut;

	FresnelReflector* fresnelBRDF;
	FresnelTransmitter* fresnelBTDF;
};

inline void Dielectric::SetCfIn(const float c)
{
	cfIn.r = c; cfIn.g = c; cfIn.b = c;
}
inline void Dielectric::SetCfOut(const float c)
{
	cfOut.r = c; cfOut.g = c; cfOut.b = c;
}
inline void Dielectric::SetCfIn(const float r, const float g, const float b)
{
	cfIn.r = r; cfIn.g = g; cfIn.b = b;
}
inline void Dielectric::SetCfOut(const float r, const float g, const float b)
{
	cfOut.r = r; cfOut.g = g; cfOut.b = b;
}
inline void Dielectric::SetCfIn(const RGBColor c)
{
	cfIn = c;
}
inline void Dielectric::SetCfOut(const RGBColor c)
{
	cfOut = c;
}

inline void Dielectric::SetEtaIn(const float& eta)
{
	fresnelBTDF->SetEtaIn(eta);
	fresnelBRDF->SetEtaIn(eta);
}
inline void Dielectric::SetEtaOut(const float& eta)
{
	fresnelBTDF->SetEtaOut(eta);
	fresnelBRDF->SetEtaOut(eta);
}
#endif //_DIELECTRIC_H_
