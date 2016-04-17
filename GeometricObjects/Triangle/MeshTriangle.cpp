#include "MeshTriangle.h"
#include "Maths.h"
#include "Constants.h"
MeshTriangle::MeshTriangle()
	:GeometricObject(),pMesh(NULL),
	index0(0),index1(0),index2(0),
	normal()
{

}

MeshTriangle::MeshTriangle(const MeshTriangle& mt)
	:GeometricObject(), pMesh(mt.pMesh),
	index0(mt.index0), index1(mt.index1), index2(mt.index2),
	normal(mt.normal)
{
}

MeshTriangle::MeshTriangle(Mesh* pMesh, const int i1, const int i2, const int i3)
	:GeometricObject(), pMesh(pMesh),
	index0(i1), index1(i2), index2(i3)
{
}
MeshTriangle::~MeshTriangle()
{
	if (pMesh)
	{
		delete pMesh;
		pMesh = NULL;
	}
}

MeshTriangle& MeshTriangle::operator= (const MeshTriangle& rhs)
{
	if (this == &rhs)
		return *this;


	if (pMesh)
	{
		delete pMesh;
		pMesh = NULL;
	}
	if (rhs.pMesh)
		pMesh = rhs.pMesh;

	index0 = rhs.index0;
	index1 = rhs.index1;
	index2 = rhs.index2;
	normal = rhs.normal;
	return *this;
}

bool MeshTriangle::ShadowHit(const Ray& ray, float& tmin) const
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

	if (beta < 0 || beta>1)
		return false;

	double r = e*l - h*i;
	double e2 = a*n + d*q + c*r;
	double gamma = e2*invDenom;

	if (gamma < 0 || gamma>1)
		return false;
	if (gamma + beta > 1)
		return false;

	double e3 = a*p - b*r + d*s;
	double t = e3*invDenom;

	if (t < kEpsilon)
		return false;

	tmin = t;
	return true;
}
Normal MeshTriangle::GetNormal() const
{
	return normal;
}

BBox MeshTriangle::GetBoundingBox()
{
	double delta = 0.0001;
	Point3D v0 = pMesh->vertices[index0];
	Point3D v1 = pMesh->vertices[index1];
	Point3D v2 = pMesh->vertices[index2];

	return BBox(
		min(min(v0.x, v1.x), v2.x) - delta, max(max(v0.x, v1.x), v2.x) + delta,
		min(min(v0.y, v1.y), v2.y) - delta, max(max(v0.y, v1.y), v2.y) + delta,
		min(min(v0.z, v1.z), v2.z) - delta, max(max(v0.z, v1.z), v2.z) + delta);
}

void MeshTriangle::ComputeNormal(const bool isRevNormal)
{
	normal = 
		(pMesh->vertices[index1] - pMesh->vertices[index0])
		^
		(pMesh->vertices[index2] - pMesh->vertices[index0]);
	normal.normalize();

	if (isRevNormal)
		normal = -normal;
}

float MeshTriangle::InterpolateU(const float beta, const float gamma) const
{
	return (1 - beta - gamma) * pMesh->v[0] + beta * pMesh->v[1] + gamma *pMesh->v[2];
}

float MeshTriangle::InterpolateV(const float beta, const float gamma) const
{
	return (1 - beta - gamma) * pMesh->u[0] + beta * pMesh->u[1] + gamma *pMesh->u[2];
}