#include "PerfectTransmitter.h"
#include "Constants.h"
PerfectTransmitter::PerfectTransmitter()
	:BTDF(), kt(0.0f), ior(1.0f)
{
}

PerfectTransmitter::~PerfectTransmitter()
{
}

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& pt)
	:BTDF(pt), kt(pt.kt), ior(pt.ior)
{
}

PerfectTransmitter& PerfectTransmitter::operator = (const PerfectTransmitter& rhs)
{
	if (this == &rhs)
		return *this;
	
	BTDF::operator=(rhs);
	kt = rhs.kt;
	ior = rhs.ior;
	return *this;
}

PerfectTransmitter* PerfectTransmitter::Clone() const
{
	return new PerfectTransmitter(*this);
}

RGBColor PerfectTransmitter::F(const ShadeRec& sr, const Vector3D & wo, const Vector3D &wi) const
{
	return black;
}

//计算折射光线的方向并将其返回至参数wt，注意此函数仅能用于非全内反射条件下
RGBColor PerfectTransmitter::SamplerF(const ShadeRec& sr, const Vector3D & Wo, Vector3D &Wt) const
{
	Normal n(sr.normal);
	float cosThetaI = n *Wo;
	float eta = ior;

	if (cosThetaI < 0)//判断光线是否与透明对象的内部表面相交
	{
		eta = 1 / ior;//若是则取ior值的倒数
		n = -n;		  //若是则逆转法线方向
		cosThetaI = -cosThetaI;//若是则改变cosThetaI的符号
	}

	//计算折射光线方向t，以及其与法线的cos值
	float temp = 1.0 - (1.0 - cosThetaI*cosThetaI) / (eta*eta);
	float cosThetaT = sqrt(temp);
	Wt =  -Wo / eta - (cosThetaT - cosThetaI / eta)*n;
	//本类不涉及颜色计算，默认乘上白色显示RGB颜色
	return kt / (eta*eta)*white / fabs(sr.normal*Wt);
}


RGBColor PerfectTransmitter::Rho(const ShadeRec& sr, const Vector3D &wo) const
{
	return black;
}

//判断是否发生全内反射
bool PerfectTransmitter::Tir(const ShadeRec& sr) const
{
	Vector3D Wo(-sr.ray.d);
	float cosThetaI = sr.normal*Wo;
	float eta = ior;

	if (cosThetaI < 0)//判断光线是否与透明对象的内部表面相交
		eta = 1 / ior;//若是则取ior值的倒数

	//满足条件则为发射全内反射
	return 1.0 - (1.0 - cosThetaI*cosThetaI) / (eta*eta) < 0;
}