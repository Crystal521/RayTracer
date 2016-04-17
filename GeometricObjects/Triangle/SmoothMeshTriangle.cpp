#include "SmoothMeshTriangle.h"
#include "Constants.h"
SmoothMeshTriangle::SmoothMeshTriangle()
	:MeshTriangle()
{
}

SmoothMeshTriangle::SmoothMeshTriangle(const SmoothMeshTriangle& fmt)
	: MeshTriangle(fmt)
{
}
SmoothMeshTriangle::SmoothMeshTriangle(Mesh* pMesh, const int i0, const int i1, const int i2)
	: MeshTriangle(pMesh,i0,i1,i2)
{

}
SmoothMeshTriangle::~SmoothMeshTriangle()
{
}

SmoothMeshTriangle* SmoothMeshTriangle::Clone() const
{
	return new SmoothMeshTriangle(*this);
}
SmoothMeshTriangle& SmoothMeshTriangle::operator= (const SmoothMeshTriangle& rhs)
{
	if (this == &rhs)
		return (*this);

	MeshTriangle::operator= (rhs);

	return *this;
}
bool SmoothMeshTriangle::Hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	Point3D v0 = pMesh->vertices[index0];
	Point3D v1 = pMesh->vertices[index1];
	Point3D v2 = pMesh->vertices[index2];

	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
	double q = g*i - e*k, s = e*j - f*i;

	double invDenom = 1.0 / (a*m + b*q + c*s);

	double e1 = d*m - b*n - c*p;
	double beta = e1*invDenom;

	if (beta < 0)
		return false;

	double r = e*l - h*i;
	double e2 = a*n + d*q + c*r;
	double gamma = e2*invDenom;

	if (gamma < 0)
		return false;
	if (gamma + beta > 1)
		return false;

	double e3 = a*p - b*r + d*s;
	double t = e3*invDenom;

	if (t < kEpsilon)
		return false;

	tmin = t;
	sr.normal = InterpolateNormal(beta, gamma);;
	sr.localHitPoint = ray.o + t*ray.d;

	return true;
}

//bool SmoothMeshTriangle::ShadowHit(const Ray& ray, float &tmin) const
//{
//	Point3D v0 = pMesh->vertices[index0];
//	Point3D v1 = pMesh->vertices[index1];
//	Point3D v2 = pMesh->vertices[index2];
//
//	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
//	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
//	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;
//
//	double m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
//	double q = g*i - e*k, s = e*j - f*i;
//
//	double invDenom = 1.0 / (a*m + b*q + c*s);
//
//	double e1 = d*m - b*n - c*p;
//	double beta = e1*invDenom;
//
//	if (beta < 0)
//		return false;
//
//	double r = e*l - h*i;
//	double e2 = a*n + d*q + c*r;
//	double gamma = e2*invDenom;
//
//	if (gamma < 0)
//		return false;
//	if (gamma + beta > 1)
//		return false;
//
//	double e3 = a*p - b*r + d*s;
//	double t = e3*invDenom;
//
//	if (t < kEpsilon)
//		return false;
//
//	tmin = t;
//	return true;
//}

Normal SmoothMeshTriangle::InterpolateNormal(const float beta, const float gamma) const
{
	Normal n((1 - beta - gamma)*pMesh->normals[index0] + 
				beta * pMesh->normals[index1] + 
				gamma * pMesh->normals[index2]);
	n.normalize();
	return n;
}