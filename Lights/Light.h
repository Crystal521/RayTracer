#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec;

class Light {
public:

	Light();

	Light(const Light& ls);

	Light& operator= (const Light& rhs);

	virtual Light* Clone() const = 0;

	virtual ~Light();

	virtual Vector3D GetDirection(ShadeRec& sr) = 0;

	virtual RGBColor L(ShadeRec& sr);
	
	virtual bool IsInShadow(const Ray& ray, ShadeRec& sr)const =0;

	virtual bool CastShadow() const = 0;
private :
	bool shadow;
};

#endif//_LIGHT_H_