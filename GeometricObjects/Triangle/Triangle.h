#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "GeometricObject.h"

class Triangle :public GeometricObject
{
public:
	Triangle();
	Triangle(Point3D v0, Point3D v1, Point3D v2);
	Triangle(const Triangle& rhs);
	~Triangle();

	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec &sr) const;
	virtual Triangle* Clone() const;

	virtual bool ShadowHit(const Ray& ray, float &tmin) const;
	virtual BBox GetBoundingBox();
	Triangle &operator=(const Triangle& rhs);

	void ComputeNormal();
private:
	Point3D v0, v1, v2;
	Normal normal;

};

#endif//_TRIANGLE_H_
