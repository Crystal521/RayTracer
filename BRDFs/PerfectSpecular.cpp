#include "PerfectSpecular.h"
#include "Constants.h"
#include "World.h"

PerfectSpecular::PerfectSpecular()
	:BRDF(), kr(0), cr(1)
{
}

PerfectSpecular::PerfectSpecular(const PerfectSpecular & obj)
	: BRDF(obj), kr(obj.kr), cr(obj.cr)
{
}

PerfectSpecular::~PerfectSpecular()
{
}

PerfectSpecular * PerfectSpecular::Clone() const
{
	return (new PerfectSpecular(*this));
}

RGBColor PerfectSpecular::Rho(const ShadeRec & sr, const Vector3D & wo) const
{
	return sr.w.backgroundColor;;
}

PerfectSpecular & PerfectSpecular::operator=(const PerfectSpecular & rhs)
{
	if (this == &rhs)
		return *this;

	BRDF::operator= (rhs);
	kr = rhs.kr;
	cr = rhs.cr;

	return *this;
}

//ʹ��Phong��ɫģ�ͣ�����ֱ�ӹ���
RGBColor PerfectSpecular::F(const ShadeRec & sr, const Vector3D & wi, const Vector3D & wo) const
{
	return sr.w.backgroundColor;
}



//���������¼����wiΪ���淴��ķ���
//wi�� Reflective::shade and Transparent::shade���ã���ʽ�ݹ飩
//ʹ��fabs��...
RGBColor PerfectSpecular::SamplerF(
	const ShadeRec& sr, const Vector3D &wo, 
	Vector3D & wi) const
{
	float NdotWo = sr.normal * wo;
	//������߷���ͨ��������ײ��ķ��������䷽�����
	wi = -wo + 2.0 * sr.normal * NdotWo;
	//wi.normalize();
	//ʹ��fabs
	return kr * cr / fabs((sr.normal * wi));
}


//����������path tracing
//pdf��...
RGBColor PerfectSpecular::SamplerF(
	const ShadeRec& sr, const Vector3D &wo, 
	Vector3D & wi,
	 float &pdf) const
{
	float NdotWo = sr.normal * wo;
	//������߷���ͨ��������ײ��ķ��������䷽�����
	wi = -wo + 2.0 * sr.normal * NdotWo;
	pdf = fabs((sr.normal * wi));
	return kr * cr / pdf;
}

