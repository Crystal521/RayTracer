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
	//环境光的反射辐射度L = Ka*Cd*ls*Cl
	//其中Ka是环境光系数，Cd是环境光颜色，ls光源系数，Cl光源颜色
	RGBColor L =  ambientBRDF->Rho(sr, Wo)*sr.w.pAmbient->L(sr);
	int num = sr.w.lights.size();

	for (int j = 0; j < num; j++)
	{
		Vector3D Wi = sr.w.lights[j]->GetDirection(sr);
		float NdotWi = sr.normal*Wi;

		//Phong光照模型的着色公式L = (Kd*Cd/Pi + Ks*Cd*pow((R*Wo), Exp)）*L*NdotWi
		//其中Kd是漫反射系数，Cd是漫反射颜色
		//其中Ks是高光系数，Cd是高光颜色，R是反射方向，Wo碰撞点到视平面像素点
		//L是不同光源下的光强
		//NdotWi是法线与入射光线的点积
		if (NdotWi > 0.0f)
		{
			//检测阴影，并计算着色
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