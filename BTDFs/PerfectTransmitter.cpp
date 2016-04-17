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

//����������ߵķ��򲢽��䷵��������wt��ע��˺����������ڷ�ȫ�ڷ���������
RGBColor PerfectTransmitter::SamplerF(const ShadeRec& sr, const Vector3D & Wo, Vector3D &Wt) const
{
	Normal n(sr.normal);
	float cosThetaI = n *Wo;
	float eta = ior;

	if (cosThetaI < 0)//�жϹ����Ƿ���͸��������ڲ������ཻ
	{
		eta = 1 / ior;//������ȡiorֵ�ĵ���
		n = -n;		  //��������ת���߷���
		cosThetaI = -cosThetaI;//������ı�cosThetaI�ķ���
	}

	//����������߷���t���Լ����뷨�ߵ�cosֵ
	float temp = 1.0 - (1.0 - cosThetaI*cosThetaI) / (eta*eta);
	float cosThetaT = sqrt(temp);
	Wt =  -Wo / eta - (cosThetaT - cosThetaI / eta)*n;
	//���಻�漰��ɫ���㣬Ĭ�ϳ��ϰ�ɫ��ʾRGB��ɫ
	return kt / (eta*eta)*white / fabs(sr.normal*Wt);
}


RGBColor PerfectTransmitter::Rho(const ShadeRec& sr, const Vector3D &wo) const
{
	return black;
}

//�ж��Ƿ���ȫ�ڷ���
bool PerfectTransmitter::Tir(const ShadeRec& sr) const
{
	Vector3D Wo(-sr.ray.d);
	float cosThetaI = sr.normal*Wo;
	float eta = ior;

	if (cosThetaI < 0)//�жϹ����Ƿ���͸��������ڲ������ཻ
		eta = 1 / ior;//������ȡiorֵ�ĵ���

	//����������Ϊ����ȫ�ڷ���
	return 1.0 - (1.0 - cosThetaI*cosThetaI) / (eta*eta) < 0;
}