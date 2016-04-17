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
	//�������Χ���ཻ
	bool Hit(const Ray& ray) const;

	BBox& operator= (const BBox& rhs);
	//�����жϹ�������Ƿ��ں�����
 	bool Inside(const Point3D& p) const;
	~BBox();

	double x0,y0,z0;//���ĵ�
	double x1, y1, z1;//��С�ĵ�
};


#endif //_BBOX_H_