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

//使用Phong着色模型，用于直接光照
RGBColor PerfectSpecular::F(const ShadeRec & sr, const Vector3D & wi, const Vector3D & wo) const
{
	return sr.w.backgroundColor;
}



//被不断重新计算的wi为镜面反射的方向
//wi被 Reflective::shade and Transparent::shade调用（隐式递归）
//使用fabs是...
RGBColor PerfectSpecular::SamplerF(
	const ShadeRec& sr, const Vector3D &wo, 
	Vector3D & wi) const
{
	float NdotWo = sr.normal * wo;
	//反射光线方向，通过光线碰撞点的法线与入射方向求得
	wi = -wo + 2.0 * sr.normal * NdotWo;
	//wi.normalize();
	//使用fabs
	return kr * cr / fabs((sr.normal * wi));
}


//本函数用于path tracing
//pdf是...
RGBColor PerfectSpecular::SamplerF(
	const ShadeRec& sr, const Vector3D &wo, 
	Vector3D & wi,
	 float &pdf) const
{
	float NdotWo = sr.normal * wo;
	//反射光线方向，通过光线碰撞点的法线与入射方向求得
	wi = -wo + 2.0 * sr.normal * NdotWo;
	pdf = fabs((sr.normal * wi));
	return kr * cr / pdf;
}

