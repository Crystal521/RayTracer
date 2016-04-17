#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_
#include "GeometricObject.h"

class Rectangle:public GeometricObject
{
public:
	Rectangle();
	Rectangle(const Point3D& p, const Vector3D& a, const Vector3D& b);
	Rectangle(const Point3D& p, const Vector3D& a, const Vector3D& b,const Normal& n);
	Rectangle(const Rectangle& r);
	~Rectangle();


	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec &sr) const;
	virtual Rectangle* Clone() const;
	virtual bool ShadowHit(const Ray& ray, float &tmin) const;
	virtual Normal GetNormal(const Point3D& p);
	float Pdf(ShadeRec& sr);

	Rectangle& operator= (const Rectangle& rhs);

	//BBox GetBoundingBox();

private:
	Point3D p;		//�Ƕ���
	Vector3D a;		//��
	Vector3D b;		//��
	Normal n;		//����

	double aSquare;	// a�߳���ƽ��
	double bSquare;	// b�߳���ƽ��

	static const double kEpsilon;
};



#endif//_RECTANGLE_H_