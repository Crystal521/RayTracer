#ifndef   _TRACER_H_
#define   _TRACER_H_


#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"

class World;

class Tracer
{
public:
	Tracer();
	Tracer(World* pWorld);
	virtual ~Tracer();

	virtual RGBColor TraceRay(const Ray& ray) const;
    virtual RGBColor TraceRay(const Ray& ray, const int depth) const;
	virtual RGBColor TraceRay(const Ray& ray, float& tmin, const int depth) const;
protected:
	World* pWorld;

private:
};
#endif // !_TRACER_H_
