#ifndef _GEOMETRICOBJECT_H_
#define _GEOMETRICOBJECT_H_

#include "ShadeRec.h"
#include "RGBColor.h"
#include "Ray.h"
#include "BBox.h"
#include "Material.h"
class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);
	~GeometricObject();
	
	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec &sr) const = 0;
	virtual GeometricObject* Clone() const = 0;

	virtual bool ShadowHit(const Ray& ray, float &tmin) const = 0;
	virtual void SetBoundingBox();
	virtual BBox GetBoundingBox();

	Material* GetMaterial() const;
	virtual void SetMaterial(Material* pMaterial);

	void SetShadows(bool openShadows);

	// 用于平滑着色三角网格
	virtual Normal GetNormal() const;
	virtual Normal GetNormal(const Point3D& p);
protected:
	bool shadows;
	mutable Material*   pMaterial;
	GeometricObject &operator=(const GeometricObject& rhs);
};

inline Material* GeometricObject::GetMaterial() const 
{
	return pMaterial;
}

inline void GeometricObject::SetShadows(bool openShadows) {
	shadows = openShadows;
}
#endif
