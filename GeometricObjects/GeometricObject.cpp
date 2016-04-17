#include "GeometricObject.h"
#include "Constants.h"
#include "Material.h"

GeometricObject::GeometricObject()
	: pMaterial(NULL),
	shadows(false)
{
}

GeometricObject::GeometricObject(const GeometricObject& object)
	: shadows(false)
{
	if (object.pMaterial)
		pMaterial = object.pMaterial->Clone();
	else
		pMaterial = NULL;
}


GeometricObject::~GeometricObject()
{
	if (pMaterial)
	{
		delete pMaterial;
		pMaterial = NULL;
	}
}


GeometricObject &GeometricObject::operator=(const GeometricObject& rhs)
{
	if (this == &rhs)
		return (*this);

	if (pMaterial)
	{
		delete pMaterial;
		pMaterial = NULL;
	}

	if (rhs.pMaterial)
		pMaterial = rhs.pMaterial;

	return (*this);
}

void GeometricObject::SetMaterial(Material* pMat)
{
	pMaterial = pMat;
}

void GeometricObject::SetBoundingBox()
{

}
BBox GeometricObject::GetBoundingBox()
{
	return BBox();
}

Normal GeometricObject::GetNormal() const
{
	return Normal();
}

Normal GeometricObject::GetNormal(const Point3D & p)
{
	return Normal();
}