#include "Phong.h"
#include "Constants.h"
#include "World.h"

Phong::Phong()
	:Material(),
	ambientBRDF(new Lambertian),
	diffuseBRDF(new Lambertian),
	specularBRDF(new GlossySpecular)
{
}

Phong::Phong(const Phong& phong)
	:Material(phong)
{

	if (phong.ambientBRDF)
		ambientBRDF = phong.ambientBRDF->Clone();
	else
		ambientBRDF = NULL;

	if (phong.diffuseBRDF)
		diffuseBRDF = phong.diffuseBRDF->Clone();
	else
		diffuseBRDF = NULL;

	if (phong.specularBRDF)
		specularBRDF = phong.specularBRDF->Clone();
	else
		specularBRDF = NULL;
}

Phong::~Phong()
{
	if (ambientBRDF)
	{
		delete ambientBRDF;
		ambientBRDF = NULL;
	}
	if (diffuseBRDF)
	{
		delete diffuseBRDF;
		diffuseBRDF = NULL;
	}
	if (specularBRDF)
	{
		delete specularBRDF;
		specularBRDF = NULL;
	}
}

Phong* Phong::Clone() const
{
	return new Phong(*this);
}

RGBColor Phong::Shade(ShadeRec& sr)
{
	Vector3D Wo(-sr.ray.d);
	//������ķ�������L = Ka*Cd*ls*Cl
	//����Ka�ǻ�����ϵ����Cd�ǻ�������ɫ��ls��Դϵ����Cl��Դ��ɫ
	RGBColor L =  ambientBRDF->Rho(sr, Wo)*sr.w.pAmbient->L(sr);
	int num = sr.w.lights.size();

	for (int j = 0; j < num; j++)
	{
		Vector3D Wi = sr.w.lights[j]->GetDirection(sr);
		float NdotWi = sr.normal*Wi;

		//Phong����ģ�͵���ɫ��ʽL = (Kd*Cd/Pi + Ks*Cd*pow((R*Wo), Exp)��*L*NdotWi
		//����Kd��������ϵ����Cd����������ɫ
		//����Ks�Ǹ߹�ϵ����Cd�Ǹ߹���ɫ��R�Ƿ��䷽��Wo��ײ�㵽��ƽ�����ص�
		//L�ǲ�ͬ��Դ�µĹ�ǿ
		//NdotWi�Ƿ�����������ߵĵ��
		if (NdotWi > 0.0f)
		{
			//�����Ӱ����������ɫ
			bool inShadow = false;
			if (sr.w.lights[j]->CastShadow())
			{
				Ray shadowRay(sr.hitPoint, Wi);
				inShadow = sr.w.lights[j]->IsInShadow(shadowRay, sr);
			}
			if (!inShadow)
			{
				L +=
					(diffuseBRDF->F(sr, Wo, Wi) + specularBRDF->F(sr, Wo, Wi))
					* sr.w.lights[j]->L(sr)*NdotWi;
			}
		}
			
	}
	return L;
}

Phong& Phong::operator=(const Phong& rhs)
{
	if (this == &rhs)
		return *this;

	Material::operator=(rhs);


	if (ambientBRDF)
	{
		delete ambientBRDF;
		ambientBRDF = NULL;
	}
	if (rhs.ambientBRDF)
		ambientBRDF = rhs.ambientBRDF->Clone();

	if (diffuseBRDF)
	{
		delete diffuseBRDF;
		diffuseBRDF = NULL;
	}
	if (rhs.diffuseBRDF)
		diffuseBRDF = rhs.diffuseBRDF->Clone();

	if (specularBRDF)
	{
		delete specularBRDF;
		specularBRDF = NULL;
	}
	if (rhs.specularBRDF)
		specularBRDF = rhs.specularBRDF->Clone();

	return *this;
}