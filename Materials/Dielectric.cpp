
#include "Dielectric.h"
#include "World.h"
#include <math.h>
Dielectric::Dielectric()
	:Phong(),
	fresnelBRDF(new FresnelReflector),
	fresnelBTDF(new FresnelTransmitter),
	cfIn(1.0f), cfOut(1.0f)
{
}

Dielectric::~Dielectric()
{
	if (fresnelBRDF)
	{
		delete fresnelBRDF;
		fresnelBRDF = nullptr;
	}
	if (fresnelBTDF)
	{
		delete fresnelBTDF;
		fresnelBTDF = nullptr;
	}
}


Dielectric::Dielectric(const Dielectric& ph)
	:Phong(ph)
{
	if (ph.fresnelBRDF)
		fresnelBRDF = ph.fresnelBRDF;
	else
		fresnelBRDF = nullptr;

	if (ph.fresnelBTDF)
		fresnelBTDF = ph.fresnelBTDF;
	else
		fresnelBTDF = nullptr;

	cfIn = ph.cfIn;
	cfOut = ph.cfOut;
}


Dielectric* Dielectric::Clone() const
{
	return new Dielectric(*this);
}

RGBColor Dielectric::Shade(ShadeRec& sr)
{
	RGBColor L(Phong::Shade(sr));

	Vector3D Wo(-sr.ray.d);
	Vector3D Wi;
	RGBColor fr = fresnelBRDF->SamplerF(sr, Wo, Wi);
	Ray reflectedRay(sr.hitPoint, Wi);
	float t;
	RGBColor Lr, Lt;
	float NdotWi = sr.normal*Wi;

	if (fresnelBTDF->Tir(sr))
	{//全内反射
		if (NdotWi < 0)
		{   //反射光线在介质内部
			Lr = sr.w.pTracer->TraceRay(reflectedRay, t, sr.depth + 1);
			L += cfIn.powc(t)*Lr;
		}
		else
		{
			//反射光线在介质内部
			Lr = sr.w.pTracer->TraceRay(reflectedRay, t, sr.depth + 1);
			L += cfOut.powc(t)*Lr;
		}
	}
	else
	{
		Vector3D Wt;
		RGBColor ft = fresnelBTDF->SamplerF(sr, Wo, Wt);//计算Wt
		Ray transmittedRay(sr.hitPoint, Wt);
		float NdotWt = sr.normal*Wt;

		if (NdotWi < 0)
		{   //反射光线在介质内部
			Lr = fr * sr.w.pTracer->TraceRay(reflectedRay, t, sr.depth + 1)*fabs(NdotWi);
			L += cfIn.powc(t)*Lr;
			//折射光线在介质外部
			Lt = ft * sr.w.pTracer->TraceRay(transmittedRay, t, sr.depth + 1)*fabs(NdotWt);
			L += cfOut.powc(t)*Lt;
		}
		else
		{
			//反射光线在介质外部
			Lr = fr * sr.w.pTracer->TraceRay(reflectedRay, t, sr.depth + 1)*fabs(NdotWi);
			L += cfOut.powc(t)*Lr;
			//折射光线在介质内部
			Lt = ft * sr.w.pTracer->TraceRay(transmittedRay, t, sr.depth + 1)*fabs(NdotWt);
			L += cfIn.powc(t)*Lt;
		}

	}

	return L;
}
