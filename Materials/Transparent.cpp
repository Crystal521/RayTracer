#include "Transparent.h"
#include "World.h"
#include <math.h>
Transparent::Transparent()
	:Phong(), 
	reflectiveBRDF(new PerfectSpecular),
	specularBTDF(new PerfectTransmitter)
{
}

Transparent::~Transparent()
{
	if (reflectiveBRDF)
	{
		delete reflectiveBRDF;
		reflectiveBRDF = nullptr;
	}
	if (specularBTDF)
	{
		delete specularBTDF;
		specularBTDF = nullptr;
	}
}


Transparent::Transparent(const Transparent& ph)
	:Phong(ph)
{
	if (ph.reflectiveBRDF)
		reflectiveBRDF = ph.reflectiveBRDF;
	else
		reflectiveBRDF = nullptr;

	if (ph.specularBTDF)
		specularBTDF = ph.specularBTDF;
	else
		specularBTDF = nullptr;
}


Transparent* Transparent::Clone() const
{
	return new Transparent(*this);
}

RGBColor Transparent::Shade(ShadeRec& sr)
{
	RGBColor L(Phong::Shade(sr));

	Vector3D Wo(-sr.ray.d);
	Vector3D Wi;
	RGBColor fr = reflectiveBRDF->SamplerF(sr, Wo, Wi);
	Ray reflectedRay(sr.hitPoint, Wi);

	if (specularBTDF->Tir(sr))
		L += sr.w.pTracer->TraceRay(reflectedRay,sr.depth+1);
	else
	{
		Vector3D Wt;
		RGBColor ft = specularBTDF->SamplerF(sr, Wo, Wt);//¼ÆËãWt
		Ray transmittedRay(sr.hitPoint, Wt);

		L += fr*sr.w.pTracer->TraceRay(reflectedRay, sr.depth + 1)*fabs(sr.normal*Wi);
		L += ft*sr.w.pTracer->TraceRay(transmittedRay, sr.depth + 1)*fabs(sr.normal*Wt);		
	}

	return L;
}