#include "MultipleObjects.h"
#include "World.h"


MultipleObjects::MultipleObjects()
	:Tracer(NULL)
{
}

MultipleObjects::MultipleObjects(World *pWorld)
	: Tracer(pWorld)
{
}


MultipleObjects::~MultipleObjects()
{
}

RGBColor MultipleObjects::TraceRay(const Ray& ray) const
{
    ShadeRec sr(pWorld->hit_bare_bones_objects(ray));

	if (sr.isHit)
		return sr.color;
	else
		return pWorld->backgroundColor;
}
