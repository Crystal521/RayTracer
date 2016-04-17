#ifndef __SMOOTH_TRIANGLE_H_
#define __SMOOTH_TRIANGLE_H_

#include "GeometricObject.h"

//本类含有三个顶点法线，
//用于平滑着色时跟碰撞点处进行线性插值
class SmoothTriangle:public GeometricObject
{
public:

	SmoothTriangle();
	SmoothTriangle(const SmoothTriangle& st);
	SmoothTriangle(const Point3D& a, const Point3D& b, const Point3D& c);

	~SmoothTriangle();

	SmoothTriangle &operator=(const SmoothTriangle& rhs);

	virtual SmoothTriangle* Clone() const override;
	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec &sr) const;
	virtual bool ShadowHit(const Ray& ray, float &tmin) const;
	virtual BBox GetBoundingBox();
public:
	Normal n0, n1, n2;
private:
	Point3D v0, v1, v2;
	Normal InterpolateNormal(const float beta, const float gtamma)const;
};

#endif//__SMOOTH_TRIANGLE_H_