#ifndef _MULTIPLE_OBJECTS_H_
#define _MULTIPLE_OBJECTS_H_

#include "Tracer.h"

class MultipleObjects:public Tracer
{
public:
	MultipleObjects();
	MultipleObjects(World *pWorld);
	virtual ~MultipleObjects();

	virtual RGBColor TraceRay(const Ray& ray) const;
private:

};


#endif //_MULTIPLE_OBJECTS_H