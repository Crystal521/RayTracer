#include "Tracer.h"



Tracer::Tracer()
	:pWorld(NULL)
{
}

Tracer::Tracer(World* pWorld)
	:pWorld(pWorld)
{

}
Tracer::~Tracer()
{
	if (pWorld)
		pWorld = NULL;
}


RGBColor Tracer::TraceRay(const Ray& ray) const
{
	return black;
}

RGBColor Tracer::TraceRay(const Ray& ray, const int depth) const
{
	return black;
}

RGBColor Tracer::TraceRay(const Ray& ray, float& tmin, const int depth) const
{
	return black;
}