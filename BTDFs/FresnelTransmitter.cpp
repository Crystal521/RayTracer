#include "FresnelTransmitter.h"
#include "Constants.h"
FresnelTransmitter::FresnelTransmitter()
	:BTDF(), etaIn(1.5f), etaOut(1.0f)
{
}

FresnelTransmitter::~FresnelTransmitter()
{
}

FresnelTransmitter::FresnelTransmitter(const FresnelTransmitter& pt)
	:BTDF(), etaIn(pt.etaIn), etaOut(pt.etaOut)
{
}

FresnelTransmitter& FresnelTransmitter::operator = (const FresnelTransmitter& rhs)
{
	if (this == &rhs)
		return *this;

	BTDF::operator=(rhs);
	etaIn = rhs.etaIn;
	etaOut = rhs.etaOut;
	return *this;
}

FresnelTransmitter* FresnelTransmitter::Clone() const
{
	return new FresnelTransmitter(*this);
}

RGBColor FresnelTransmitter::F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const
{
	return black;
}

//计算折射光线的方向并将其返回至参数wt，注意此函数仅能用于非全内反射条件下
RGBColor FresnelTransmitter::SamplerF(const ShadeRec& sr, const Vector3D & Wo, Vector3D &Wt) const
{
	Normal n(sr.normal);
	float cosThetaI = n *Wo;
	float eta = etaIn/etaOut;

	if (cosThetaI < 0)//判断光线是否与透明对象的内部表面相交
	{
		eta = 1 / eta;//若是则取ior值的倒数
		n = -n;		  //若是则逆转法线方向
		cosThetaI = -cosThetaI;//若是则改变cosThetaI的符号
	}

	//计算折射光线方向t，以及其与法线的cos值
	float temp = 1.0 - (1.0 - cosThetaI*cosThetaI) / (eta*eta);
	float cosThetaT = sqrt(temp);
	Wt = -Wo / eta - (cosThetaT - cosThetaI / eta)*n;
	//本类不涉及颜色计算，默认乘上白色显示RGB颜色
	return Fresnel(sr) / (eta*eta)*white / fabs(sr.normal*Wt);
}


RGBColor FresnelTransmitter::Rho(const ShadeRec& sr, const Vector3D &wo) const
{
	return black;
}

//判断是否发生全内反射
bool FresnelTransmitter::Tir(const ShadeRec& sr) const
{
	Vector3D Wo(-sr.ray.d);
	float cosThetaI = sr.normal*Wo;
	float eta = etaIn / etaOut;

	if (cosThetaI < 0)//判断光线是否与透明对象的内部表面相交
		eta = 1 / eta;//若是则取ior值的倒数

	//满足条件则为发射全内反射
	return 1.0 - (1.0 - cosThetaI*cosThetaI) / (eta*eta) < 0;
}

//计算折射系数Kt
float FresnelTransmitter::Fresnel(const ShadeRec& sr) const
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

	return 1 - kr;
}