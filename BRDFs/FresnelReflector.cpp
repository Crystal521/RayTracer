#include "FresnelReflector.h"
#include "Constants.h"
FresnelReflector::FresnelReflector()
	:BRDF(), etaIn(1.5f), etaOut(1.0f)
{
}

FresnelReflector::~FresnelReflector()
{
}

FresnelReflector::FresnelReflector(const FresnelReflector& pt)
	:BRDF(), etaIn(pt.etaIn), etaOut(pt.etaOut)
{
}

FresnelReflector& FresnelReflector::operator = (const FresnelReflector& rhs)
{
	if (this == &rhs)
		return *this;

	BRDF::operator=(rhs);
	etaIn = rhs.etaIn;
	etaOut = rhs.etaOut;
	return *this;
}

FresnelReflector* FresnelReflector::Clone() const
{
	return new FresnelReflector(*this);
}

RGBColor FresnelReflector::F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const
{
	return black;
}

//计算折射光线的方向并将其返回至参数wt，注意此函数仅能用于非全内反射条件下
RGBColor FresnelReflector::SamplerF(const ShadeRec& sr, const Vector3D & Wo, Vector3D &Wr) const
{
	float NdotWo = sr.normal * Wo;
	Wr = -Wo + 2.0 * sr.normal * NdotWo;
	return Fresnel(sr) * white / fabs(sr.normal * Wr);
}


RGBColor FresnelReflector::Rho(const ShadeRec& sr, const Vector3D &wo) const
{
	return black;
}


//计算折射系数Kr
float FresnelReflector::Fresnel(const ShadeRec& sr) const
{
	Normal normal(sr.normal);
	float NdotD = -sr.ray.d * normal;
	float eta;

	if (NdotD < 0)
	{//光线与介质内表面碰撞
		normal = -normal;
		eta = etaOut / etaIn;
	}
	else
		eta = etaIn / etaOut;

	float cosThetaI = -sr.ray.d * normal;
	float temp = 1.0 - (1.0 - cosThetaI*cosThetaI) / (eta*eta);
	float cosThetaT = sqrt(temp);
	float rParallel = (eta*cosThetaI - cosThetaI) / (eta*cosThetaI + cosThetaT);
	float rPerpendicular = (cosThetaI - eta*cosThetaT) / (cosThetaI + eta*cosThetaT);
	float kr = 0.5*(rParallel*rParallel + rPerpendicular*rPerpendicular);

	return kr;
}