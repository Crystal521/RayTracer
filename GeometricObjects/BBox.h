#ifndef _BBOX_H_
#define _BBOX_H_

#include "Point3D.h"
#include "Ray.h"
class BBox
{
public:
	BBox();
	BBox(const BBox& box);
	BBox(const Point3D& a, const Point3D& b);
	BBox(const double xmin, const double xmax,
		const double ymin, const double ymax,
		const double zmin, const double zmax);
	//光线与包围盒相交
	bool Hit(const Ray& ray) const;

	BBox& operator= (const BBox& rhs);
	//用来判断光线起点是否在盒子里
 	bool Inside(const Point3D& p) const;
	~BBox();

	double x0,y0,z0;//最大的点
	double x1, y1, z1;//最小的点
};


#endif //_BBOX_H_