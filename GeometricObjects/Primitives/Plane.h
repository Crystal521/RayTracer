#ifndef _PLANE_H_
#define _PLANE_H_

#include "GeometricObject.h"


class Plane: public GeometricObject
{
public:
	Plane();
	Plane(const Plane& plane);
	Plane(const Point3D p, const Normal& n);

	virtual ~Plane();

	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec& s)const override;
	virtual bool ShadowHit(const Ray& ray, float &tmin) const override;
	Plane & operator=(const Plane&rhs);
	virtual Plane * Clone() const override;
private:
	//平面上的任意一点
	Point3D point;
	//平面上的法向量
	Normal normal;
	//用于阴影的计算和次光线
	static const double kEpsilon;
};


#endif
