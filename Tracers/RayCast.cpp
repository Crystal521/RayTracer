#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

RayCast::RayCast(void)
	: Tracer()
{}

RayCast::RayCast(World* pWorld)
	: Tracer(pWorld)
{}

RayCast::~RayCast() {}

RGBColor RayCast::TraceRay(const Ray& ray) const 
{
	ShadeRec sr(pWorld->HitObjects(ray));

	if (sr.isHit) 
	{
		sr.ray = ray;			// ���ڼ���߹���ɫ
		return sr.pMaterial->Shade(sr);
	}
	else
		return pWorld->backgroundColor;
}

RGBColor RayCast::TraceRay(const Ray& ray, const int depth) const 
{
	ShadeRec sr(pWorld->HitObjects(ray));

	if (sr.isHit)
	{
		sr.ray = ray;			// ���ڼ���߹���ɫ
		return sr.pMaterial->Shade(sr);
	}
	else
		return pWorld->backgroundColor;
}

