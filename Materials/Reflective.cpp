#include "Reflective.h"
#include "Constants.h"
#include "World.h"

Reflective::Reflective()
	:Phong(),
	reflectiveBRDF(new PerfectSpecular)
{
}

Reflective::~Reflective()
{
	if (reflectiveBRDF) 
	{
		delete reflectiveBRDF;
		reflectiveBRDF = NULL;
	}
}

Reflective::Reflective(const Reflective &object)
	:Phong(object)
{
	if (object.reflectiveBRDF)
		reflectiveBRDF = object.reflectiveBRDF;
	else
		reflectiveBRDF = NULL;
}


Reflective& Reflective::operator=(const Reflective& rhs)
{
	if (this == &rhs)
		return *this;

	Phong::operator=(rhs);
	if (reflectiveBRDF)
	{
		delete reflectiveBRDF;
		reflectiveBRDF = NULL;
	}
		
	
	if (rhs.reflectiveBRDF)
		reflectiveBRDF = rhs.reflectiveBRDF->Clone();

	return *this;
}

Reflective* Reflective::Clone() const
{
	return new Reflective(*this);
}

RGBColor Reflective::Shade(ShadeRec& sr)
{
	//直接光照
	RGBColor L(Phong::Shade(sr));  
	
	//计算间接光照
	Vector3D Wo(-sr.ray.d.hat());
	Vector3D Wi;
	//使用Fresnel方程计算着色
	RGBColor fr = reflectiveBRDF->SamplerF(sr, Wo, Wi);
	
	Ray reflectiveRay(sr.hitPoint, Wi);
	
	L += fr * sr.w.pTracer->TraceRay(reflectiveRay, sr.depth + 1)*(sr.normal*Wi);
	return L;
}