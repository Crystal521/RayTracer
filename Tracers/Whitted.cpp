#include "Whitted.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

Whitted::Whitted()
	:Tracer()
{
}

Whitted::Whitted(World* pWorld)
	: Tracer(pWorld)
{
}


Whitted::~Whitted()
{
}


RGBColor Whitted::TraceRay(const Ray& ray, const int depth) const
{
	//结束递归的条件
	if (depth > pWorld->vp.maxDepth)
		return black;
	
	ShadeRec sr(pWorld->HitObjects(ray));
	if (sr.isHit)
	{
		sr.depth = depth;
		sr.ray = ray;
		return sr.pMaterial->Shade(sr);
	}
	else
		return pWorld->backgroundColor;
}

RGBColor Whitted::TraceRay(const Ray& ray, float& tmin, const int depth) const
{
	//结束递归的条件
	if (depth > pWorld->vp.maxDepth)
		return black;

	ShadeRec sr(pWorld->HitObjects(ray));
	if (sr.isHit)
	{
		sr.depth = depth;
		sr.ray = ray;
		tmin = sr.t;
		return sr.pMaterial->Shade(sr);
	}
	else
	{
		tmin = kHugeValue;
		return pWorld->backgroundColor;
	}
		
}