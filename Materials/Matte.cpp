#include "Matte.h"
#include "Constants.h"
#include "World.h"
Matte::Matte()
	:Material(),
	ambientBRDF(new Lambertian),
	diffuseBRDF(new Lambertian)
{
}

Matte::Matte(const Matte& matte)
	:Material(matte)
{
	if (matte.ambientBRDF)
		ambientBRDF = matte.ambientBRDF->Clone();
	else
		ambientBRDF = NULL;

	if (matte.diffuseBRDF)
		diffuseBRDF = matte.diffuseBRDF->Clone();
	else
		diffuseBRDF = NULL;
}

Matte::~Matte()
{
	if (ambientBRDF)
	{
		delete ambientBRDF;
		ambientBRDF = NULL;
	}

	if (ambientBRDF)
	{
		delete diffuseBRDF;
		diffuseBRDF = NULL;
	}
}

RGBColor Matte::Shade(ShadeRec& sr)
{
	Vector3D Wo(-sr.ray.d.hat());
	//������ķ�������L = Kd*Cd*ls*Cl
	//����Kd�ǻ�����ϵ����Cd�ǻ�������ɫ��ls��Դϵ����Cl��Դ��ɫ
	RGBColor L = ambientBRDF->Rho(sr, Wo)*sr.w.pAmbient->L(sr);
	int num = sr.w.lights.size();

	for (int j = 0; j < num; j++)
	{
		Vector3D Wi = sr.w.lights[j]->GetDirection(sr).hat();
		float NdotWi = sr.normal*Wi;
		
		//������ķ�������L = Kd*Cd/Pi*L*NdotWi
		//����Kd��������ϵ����Cd����������ɫ��L�ǲ�ͬ��Դ�µĹ�ǿ
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
				L += diffuseBRDF->F(sr, Wo, Wi)*sr.w.lights[j]->L(sr)*NdotWi;
			}
		}
	}
	return L;
}

Matte* Matte::Clone() const
{
	return new Matte(*this);
}

Matte& Matte::operator=(const Matte& rhs)
{
	if (this == &rhs)
		return *this;

	Material::operator=(rhs);
	if (ambientBRDF)
		delete ambientBRDF;
	if (rhs.ambientBRDF)
		ambientBRDF = rhs.ambientBRDF->Clone();

	if (diffuseBRDF)
		delete diffuseBRDF;
	if (rhs.diffuseBRDF)
		diffuseBRDF = rhs.diffuseBRDF->Clone();

	return *this;
}