#include "Rectangle.h"
#include "Vector3D.h"
const double Rectangle::kEpsilon = 0.001;
Rectangle::Rectangle()
	:GeometricObject(),
	p(-1,0,-1),
	a(0,0,2),
	b(2,0,0),
	n(0,0,1),
	aSquare(4.0),
	bSquare(4.0)
{
}

Rectangle::~Rectangle()
{
}

Rectangle::Rectangle(const Point3D& p, const Vector3D& _a, const Vector3D& _b)
	:GeometricObject(),
	p(p), a(_a), b(_a),
	aSquare(a.len_squared()),
	bSquare(b.len_squared())
{
	aSquare = a*a;
	bSquare = b*b;
	n = a^b;
	n.normalize();
}

Rectangle::Rectangle(const Point3D& p, const Vector3D& _a, const Vector3D& _b, const Normal& _n)
	:GeometricObject(),
	p(p), a(_a), b(_a),
	aSquare(a.len_squared()),
	bSquare(b.len_squared()),
	n(_n)
{
	n.normalize();
}

Rectangle::Rectangle(const Rectangle& r)
	:GeometricObject(r),
	p(r.p), a(r.a), b(r.b),
	aSquare(r.aSquare),
	bSquare(r.bSquare),
	n(r.n)
{
}


bool Rectangle::Hit(const Ray& ray, double& tmin, ShadeRec &sr) const
{
	//射线与平面相交方程
	double t = (p - ray.o)*n / (ray.d*n);

	//与平面相交
	if (t < kEpsilon)
		return false;

	Point3D p0 = ray.o + t*ray.d;
	Vector3D d = p0 - p;

	double ddota = d*a; //ddota的值为向量d在a上的投影长度的平方
	if (ddota > aSquare || ddota < 0)//在平面上却不在矩形上
		return false;
	
	double ddotb = d*b; //ddota的值为向量d在b上的投影长度的平方
	if (ddotb > bSquare || ddotb < 0)//在平面上却不在矩形上
		return false;

	tmin = t;
	sr.hitPoint = p;
	sr.isHit = true;
	sr.normal = n;
	return true;
}

Rectangle* Rectangle::Clone() const
{
	return new Rectangle(*this);
}

bool Rectangle::ShadowHit(const Ray& ray, float &tmin) const
{
	//射线与平面相交方程
	double t = (p - ray.o)*n / (ray.d*n);

	//与平面相交
	if (t < kEpsilon)
		return false;

	Point3D p0 = ray.o + t*ray.d;
	Vector3D d = p0 - p;

	double ddota = d*a; //ddota的值为向量d在a上的投影长度的平方
	if (ddota > aSquare || ddota < 0)//在平面上却不在矩形上
		return false;

	double ddotb = d*b; //ddota的值为向量d在b上的投影长度的平方
	if (ddotb > bSquare || ddotb < 0)//在平面上却不在矩形上
		return false;

	tmin = t;
	return true;
}

Normal Rectangle::GetNormal(const Point3D& p)
{
	return n;
}

Rectangle& Rectangle::operator= (const Rectangle& rhs)
{
	if (this == &rhs)
		return *this;

	GeometricObject::operator=(rhs);
	p = rhs.p;
	a = rhs.a;
	b = rhs.b;
	n = rhs.n;
	aSquare = rhs.aSquare;
	bSquare = rhs.bSquare;

	return *this;
}

//float Rectangle::Pdf(ShadeRec& sr)
//{
//	return sr.p
//}