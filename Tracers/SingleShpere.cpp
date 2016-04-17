#include "SingleSphere.h"
#include "Constants.h"

#include "World.h"
#include "ShadeRec.h"

SingleSphere::SingleSphere()
	:Tracer()
{}
SingleSphere::SingleSphere(World* pWorld)
	: Tracer(pWorld)
{

}
SingleSphere::~SingleSphere()
{}

RGBColor SingleSphere::TraceRay(const Ray& ray) const
{
	ShadeRec sr(*pWorld);
	double t;

	if (pWorld->sphere.Hit(ray, t, sr))
		return RGBColor(0,1.0,0);
	else
		return black;
}