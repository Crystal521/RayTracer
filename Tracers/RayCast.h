#ifndef __RAY_CAST_H_
#define __RAY_CAST_H_

#include "Tracer.h"

class RayCast : public Tracer
{
public:
	RayCast();

	RayCast(World* pWorld);

	virtual ~RayCast();

	virtual RGBColor TraceRay(const Ray& ray) const;

	virtual RGBColor TraceRay(const Ray& ray, const int depth) const;
};

#endif//__RAY_CAST_H_