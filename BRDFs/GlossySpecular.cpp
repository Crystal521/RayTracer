#include "GlossySpecular.h"
#include "Constants.h"
#include "World.h"

GlossySpecular::GlossySpecular()
	:BRDF(), ks(0), cs(1), exp(1)
{
}

GlossySpecular::GlossySpecular(const GlossySpecular & obj)
	: BRDF(obj), ks(obj.ks), cs(obj.cs), exp(obj.exp)
{
}

GlossySpecular::~GlossySpecular()
{
}

GlossySpecular * GlossySpecular::Clone() const
{
	return (new GlossySpecular(*this));
}

RGBColor GlossySpecular::Rho(const ShadeRec & sr, const Vector3D & wo) const
{
	return sr.w.backgroundColor;
}

GlossySpecular & GlossySpecular::operator=(const GlossySpecular & rhs)
{
	if (this == &rhs)
		return *this;

	BRDF::operator= (rhs);
	ks = rhs.ks;
	exp = rhs.exp;
	cs = rhs.cs;

	return *this;
}

//使用Phong着色模型，用于直接光照
RGBColor GlossySpecular::F(const ShadeRec & sr, const Vector3D & wo, const Vector3D & wi) const
{
	RGBColor L;
	//反射光线方向，通过光线碰撞点的法线与入射方向求得
	double NdotWi = sr.normal*wi;
	Vector3D r(-wi + 2.0 * (sr.normal*(NdotWi)));

	double RdotWo = r*wo;
	if (RdotWo>0)
		L = ks*cs*pow(RdotWo, exp);
	return L;
}

//用于间接光照，带有采样器
RGBColor GlossySpecular::SamplerF(
	const ShadeRec& sr, const Vector3D &wo, 
	Vector3D & wi, 
	float &pdf) const
{
	//float NdotWo = sr.normal * wo;
	////反射光线方向，通过光线碰撞点的法线与入射方向求得
	//Vector3D r = -wo + 2.0 * sr.normal * NdotWo;

	//Vector3D w = r;
	//Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
	//u.normalize();
	//Vector3D v = u ^ w;

	//Point3D sp = pSampler->SampleHemisphere();
	//wi = sp.x * u + sp.y * v + sp.z * w;			// reflected ray direction

	//if (sr.normal * wi < 0.0) 						// reflected ray is below tangent plane
	//	wi = -sp.x * u - sp.y * v + sp.z * w;

	//float phong_lobe = pow(r * wi, exp);
	//pdf = phong_lobe * (sr.normal * wi);

	return ks * cs;//(ks * cs * phong_lobe);
}


