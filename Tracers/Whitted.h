#ifndef _WHITTED_H_
#define _WHITTED_H_

#include "Tracer.h"

class Whitted :public Tracer
{
public:
	Whitted();
	Whitted(World* pWorld);
	virtual ~Whitted();

	virtual RGBColor TraceRay(const Ray& ray, const int depth) const;
	virtual RGBColor TraceRay(const Ray& ray, float& tmin, const int depth) const;
};

#endif//_WHITTED_H_