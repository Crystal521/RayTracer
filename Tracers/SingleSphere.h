#ifndef _SINGLESPHERE_H_
#define _SINGLESPHERE_H_

#include "Tracer.h"

class SingleSphere:public Tracer
{
public:
	SingleSphere();
	SingleSphere(World* pWorld);
	virtual ~SingleSphere();


    virtual RGBColor TraceRay(const Ray& ray) const;

protected:

private:
};
#endif // !_SINGLESPHERE_H_
