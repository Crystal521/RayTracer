#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "ShadeRec.h"

class Material
{
public:
	Material();
	Material(const Material& material);
	virtual ~Material();

	virtual Material* Clone() const = 0;
	virtual RGBColor Shade(ShadeRec& sr);
protected:
	Material& operator=(const Material& rhs);
};

#endif//_MATERIAL_H_