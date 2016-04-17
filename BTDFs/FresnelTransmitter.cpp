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

//����������ߵķ��򲢽��䷵��������wt��ע��˺����������ڷ�ȫ�ڷ���������
RGBColor FresnelTransmitter::SamplerF(const ShadeRec& sr, const Vector3D & Wo, Vector3D &Wt) const
{
	Normal n(sr.normal);
	float cosThetaI = n *Wo;
	float eta = etaIn/etaOut;

	if (cosThetaI < 0)//�жϹ����Ƿ���͸��������ڲ������ཻ
	{
		eta = 1 / eta;//������ȡiorֵ�ĵ���
		n = -n;		  //��������ת���߷���
		cosThetaI = -cosThetaI;//������ı�cosThetaI�ķ���
	}

	//����������߷���t���Լ����뷨�ߵ�cosֵ
	float temp = 1.0 - (1.0 - cosThetaI*cosThetaI) / (eta*eta);
	float cosThetaT = sqrt(temp);
	Wt = -Wo / eta - (cosThetaT - cosThetaI / eta)*n;
	//���಻�漰��ɫ���㣬Ĭ�ϳ��ϰ�ɫ��ʾRGB��ɫ
	return Fresnel(sr) / (eta*eta)*white / fabs(sr.normal*Wt);
}


RGBColor FresnelTransmitter::Rho(const ShadeRec& sr, const Vector3D &wo) const
{
	return black;
}

//�ж��Ƿ���ȫ�ڷ���
bool FresnelTransmitter::Tir(const ShadeRec& sr) const
{
	Vector3D Wo(-sr.ray.d);
	float cosThetaI = sr.normal*Wo;
	float eta = etaIn / etaOut;

	if (cosThetaI < 0)//�жϹ����Ƿ���͸��������ڲ������ཻ
		eta = 1 / eta;//������ȡiorֵ�ĵ���

	//����������Ϊ����ȫ�ڷ���
	return 1.0 - (1.0 - cosThetaI*cosThetaI) / (eta*eta) < 0;
}

//��������ϵ��Kt
float FresnelTransmitter::Fresnel(const ShadeRec& sr) const
{
	Normal normal(sr.normal);
	float NdotD = -sr.ray.d * normal;
	float eta;

	if (NdotD < 0)
	{//����������ڱ�����ײ
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