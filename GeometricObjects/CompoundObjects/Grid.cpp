#include <iostream>
#include <vector>

#include "Constants.h"
#include "Maths.h"
#include "Point3D.h"
#include "Grid.h"
#include "MeshTriangle.h"
#include "FlatMeshTriangle.h"
#include "SmoothMeshTriangle.h"

#include "Triangle.h"
#include "SmoothTriangle.h"

#include "ply.h"

typedef enum {
	flat,
	smooth
} TriangleType;

Grid::Grid()
	:Compound(),
	nx(0), ny(0), nz(0),
	pMesh(new Mesh),
	isReverseNormal(false)
{}

Grid::Grid(Mesh* pMesh)
	:Compound(),
	nx(0), ny(0), nz(0),
	pMesh(pMesh),
	isReverseNormal(false)
{}

Grid* Grid::Clone() const
{
	return new Grid(*this);
}

Grid & Grid::operator=(const Grid & rhs)
{
	return *this;
}


Grid::Grid(const Grid& grid) {}

Grid::~Grid()
{
}

BBox Grid::GetBoundingBox()
{
	return bbox;
}

void Grid::ReadFlatTriangles(const char * filename)
{
	ReadPLYFile(filename, flat);
}

void Grid::ReadSmoothTriangles(const char * filename)
{
	ReadPLYFile(filename, smooth);
	ComputeMeshNormals();
}


#pragma region  TessellateSphere
void Grid::TessellateFlatSphere(const int horizontalSteps, const int verticalSteps)
{
	double pi = 3.1415926535897932384;

	//定义顶部全部链接与一点的三角形
	int k = 1;

	for (int j = 0; j <= horizontalSteps - 1; j++) {
		Point3D v0(0, 1, 0);																		// top (north pole)

		Point3D v1(sin(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps), 			// bottom left
			cos(pi * k / verticalSteps),
			cos(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps));

		Point3D v2(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps), 		// bottom  right
			cos(pi * k / verticalSteps),
			cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps));

		Triangle* pTriangle = new Triangle(v0, v1, v2);
		objects.push_back(pTriangle);
	}


	//定义底部全部链接与一点的三角形
	k = verticalSteps - 1;

	for (int j = 0; j <= horizontalSteps - 1; j++) {
		// define vertices

		Point3D v0(sin(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps), 			// top left
			cos(pi * k / verticalSteps),
			cos(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps));

		Point3D v1(0, -1, 0);																		// bottom (south pole)		

		Point3D v2(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps), 		// top right 
			cos(pi * k / verticalSteps),
			cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps));

		Triangle* pTriangle = new Triangle(v0, v1, v2);
		objects.push_back(pTriangle);
	}



	//中部三角形
	for (int k = 1; k <= verticalSteps - 2; k++) {
		for (int j = 0; j <= horizontalSteps - 1; j++) {
			// define the first triangle

			// vertices

			Point3D v0(sin(2.0 * pi * j / horizontalSteps) * sin(pi * (k + 1) / verticalSteps), 				// bottom left, use k + 1, j
				cos(pi * (k + 1) / verticalSteps),
				cos(2.0 * pi * j / horizontalSteps) * sin(pi * (k + 1) / verticalSteps));

			Point3D v1(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * (k + 1) / verticalSteps), 		// bottom  right, use k + 1, j + 1
				cos(pi * (k + 1) / verticalSteps),
				cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * (k + 1) / verticalSteps));

			Point3D v2(sin(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps), 					// top left, 	use k, j
				cos(pi * k / verticalSteps),
				cos(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps));

			Triangle* pTriangle = new Triangle(v0, v1, v2);
			objects.push_back(pTriangle);


			// define the second triangle

			// vertices

			v0 = Point3D(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps), 			// top right, use k, j + 1
				cos(pi * k / verticalSteps),
				cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps));

			v1 = Point3D(sin(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps), 				// top left, 	use k, j
				cos(pi * k / verticalSteps),
				cos(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps));

			v2 = Point3D(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * (k + 1) / verticalSteps), 	// bottom  right, use k + 1, j + 1
				cos(pi * (k + 1) / verticalSteps),
				cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * (k + 1) / verticalSteps));

			Triangle* pTriangle2 = new Triangle(v0, v1, v2);
			objects.push_back(pTriangle2);
		}
	}
}

void Grid::TessellateSmoothSphere(const int horizontalSteps, const int verticalSteps)
{
	double pi = 3.1415926535897932384;

	// define the top triangles

	int k = 1;

	for (int j = 0; j <= horizontalSteps - 1; j++) {
		// define vertices

		Point3D v0(0, 1, 0);																		// top

		Point3D v1(sin(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps), 			// bottom left
			cos(pi * k / verticalSteps),
			cos(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps));

		Point3D v2(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps), 		// bottom  right
			cos(pi * k / verticalSteps),
			cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps));

		SmoothTriangle* pTriangle = new SmoothTriangle(v0, v1, v2);
		pTriangle->n0 = v0;
		pTriangle->n1 = v1;
		pTriangle->n2 = v2;
		objects.push_back(pTriangle);
	}


	// define the bottom triangles

	k = verticalSteps - 1;

	for (int j = 0; j <= horizontalSteps - 1; j++) {
		// define vertices

		Point3D v0(sin(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps), 			// top left
			cos(pi * k / verticalSteps),
			cos(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps));

		Point3D v1(0, -1, 0);																		// bottom			

		Point3D v2(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps), 		// top right 
			cos(pi * k / verticalSteps),
			cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps));

		SmoothTriangle* pTriangle = new SmoothTriangle(v0, v1, v2);
		pTriangle->n0 = v0;
		pTriangle->n1 = v1;
		pTriangle->n2 = v2;
		objects.push_back(pTriangle);
	}


	//  define the other triangles

	for (int k = 1; k <= verticalSteps - 2; k++) {
		for (int j = 0; j <= horizontalSteps - 1; j++) {
			// define the first triangle

			// vertices

			Point3D v0(sin(2.0 * pi * j / horizontalSteps) * sin(pi * (k + 1) / verticalSteps), 				// bottom left, use k + 1, j
				cos(pi * (k + 1) / verticalSteps),
				cos(2.0 * pi * j / horizontalSteps) * sin(pi * (k + 1) / verticalSteps));

			Point3D v1(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * (k + 1) / verticalSteps), 		// bottom  right, use k + 1, j + 1
				cos(pi * (k + 1) / verticalSteps),
				cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * (k + 1) / verticalSteps));

			Point3D v2(sin(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps), 					// top left, 	use k, j
				cos(pi * k / verticalSteps),
				cos(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps));

			SmoothTriangle* pTriangle1 = new SmoothTriangle(v0, v1, v2);
			pTriangle1->n0 = v0;
			pTriangle1->n1 = v1;
			pTriangle1->n2 = v2;
			objects.push_back(pTriangle1);


			// define the second triangle

			// vertices

			v0 = Point3D(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps), 			// top right, use k, j + 1
				cos(pi * k / verticalSteps),
				cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * k / verticalSteps));

			v1 = Point3D(sin(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps), 				// top left, 	use k, j
				cos(pi * k / verticalSteps),
				cos(2.0 * pi * j / horizontalSteps) * sin(pi * k / verticalSteps));

			v2 = Point3D(sin(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * (k + 1) / verticalSteps), 	// bottom  right, use k + 1, j + 1
				cos(pi * (k + 1) / verticalSteps),
				cos(2.0 * pi * (j + 1) / horizontalSteps) * sin(pi * (k + 1) / verticalSteps));

			SmoothTriangle* pTriangle2 = new SmoothTriangle(v0, v1, v2);
			pTriangle2->n0 = v0;
			pTriangle2->n1 = v1;
			pTriangle2->n2 = v2;
			objects.push_back(pTriangle2);
		}
	}
}
#pragma endregion

bool Grid::Hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double x0 = bbox.x0;
	double y0 = bbox.y0;
	double z0 = bbox.z0;
	double x1 = bbox.x1;
	double y1 = bbox.y1;
	double z1 = bbox.z1;

	double txmin, tymin, tzmin;
	double txmax, tymax, tzmax;

	//求光线与栅格的包围盒相交的最近（小）值和最远（大）值参数t
	double a = 1.0 / dx;
	if (a >= 0)
	{
		txmin = (x0 - ox) * a;
		txmax = (x1 - ox) * a;
	}
	else
	{
		txmin = (x1 - ox) * a;
		txmax = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0)
	{
		tymin = (y0 - oy) * b;
		tymax = (y1 - oy) * b;
	}
	else
	{
		tymin = (y1 - oy) * b;
		tymax = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0)
	{
		tzmin = (z0 - oz) * c;
		tzmax = (z1 - oz) * c;
	}
	else
	{
		tzmin = (z1 - oz) * c;
		tzmax = (z0 - oz) * c;
	}

	double t0, t1;
	t0 = max(txmin, max(tymin, tzmin));
	t1 = min(txmax, min(tymax, tzmax));

	if (t0 > t1)
		return(false);

	//求最初相交的栅格
	int ix, iy, iz;
	//光线起点是否在包围盒中
	if (bbox.Inside(ray.o))
	{
		ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	else
	{//光线与包围盒相交最近（小）值的交点
		Point3D p = ray.o + t0 * ray.d;
		ix = clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1);
	}

	//步进增量
	double dtx = (txmax - txmin) / nx;
	double dty = (tymax - tymin) / ny;
	double dtz = (tzmax - tzmin) / nz;
	double 	txnext, tynext, tznext;
	int 	ixstep, iystep, izstep;
	int 	ixstop, iystop, izstop;
	//x轴方向上与下一个相交栅格的射线参数t
	if (dx > 0)
	{
		txnext = txmin + (ix + 1) * dtx;
		ixstep = +1;
		ixstop = nx;
	}
	else
	{
		txnext = txmin + (nx - ix) * dtx;
		ixstep = -1;
		ixstop = -1;
	}
	if (dx == 0.0)
	{
		txnext = kHugeValue;
		ixstep = -1;
		ixstop = -1;
	}

	//y轴方向上与下一个相交栅格的射线参数t
	if (dy > 0)
	{
		tynext = tymin + (iy + 1) * dty;
		iystep = +1;
		iystop = ny;
	}
	else
	{
		tynext = tymin + (ny - iy) * dty;
		iystep = -1;
		iystop = -1;
	}
	if (dy == 0.0)
	{
		tynext = kHugeValue;
		iystep = -1;
		iystop = -1;
	}
	//z轴方向上与下一个相交栅格的射线参数t
	if (dz > 0)
	{
		tznext = tzmin + (iz + 1) * dtz;
		izstep = +1;
		izstop = nz;
	}
	else
	{
		tznext = tzmin + (nz - iz) * dtz;
		izstep = -1;
		izstop = -1;
	}
	if (dz == 0.0)
	{
		tznext = kHugeValue;
		izstep = -1;
		izstop = -1;
	}

	//光线遍历全部栅格
	while (1)
	{
		GeometricObject* pObj = cells[ix + nx * iy + nx * ny * iz];
		//光线始终经过txnext，tynext，tznext三者中最小的一方轴向的栅格
		if (txnext < tynext&&txnext < tznext)
		{//求最近碰撞点
			if (pObj&&pObj->Hit(ray, tmin, sr) && tmin < txnext)
			{
				pMaterial = pObj->GetMaterial();
				return true;
			}
			txnext += dtx;
			ix += ixstep;
			if (ix == ixstop)
				return false;
		}
		else if (tynext < tznext)
		{
			//求最近碰撞点
			if (pObj&&pObj->Hit(ray, tmin, sr) && tmin < tynext)
			{
				pMaterial = pObj->GetMaterial();
				return true;
			}
			tynext += dty;
			iy += iystep;
			if (iy == iystop)
				return false;
		}
		else
		{
			//求最近碰撞点
			if (pObj&&pObj->Hit(ray, tmin, sr) && tmin < tznext)
			{
				pMaterial = pObj->GetMaterial();
				return true;
			}
			tznext += dtz;
			iz += izstep;
			if (iz == izstop)
				return false;
		}
	}
}

bool Grid::ShadowHit(const Ray & ray, float & tmin) const
{
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double x0 = bbox.x0;
	double y0 = bbox.y0;
	double z0 = bbox.z0;
	double x1 = bbox.x1;
	double y1 = bbox.y1;
	double z1 = bbox.z1;

	double txmin, tymin, tzmin;
	double txmax, tymax, tzmax;

	//求阴影光线与栅格的包围盒相交的最近（小）值和最远（大）值参数t
	double a = 1.0 / dx;
	if (a >= 0)
	{
		txmin = (x0 - ox) * a;
		txmax = (x1 - ox) * a;
	}
	else
	{
		txmin = (x1 - ox) * a;
		txmax = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0)
	{
		tymin = (y0 - oy) * b;
		tymax = (y1 - oy) * b;
	}
	else
	{
		tymin = (y1 - oy) * b;
		tymax = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0)
	{
		tzmin = (z0 - oz) * c;
		tzmax = (z1 - oz) * c;
	}
	else
	{
		tzmin = (z1 - oz) * c;
		tzmax = (z0 - oz) * c;
	}

	double t0, t1;
	t0 = max(txmin, max(tymin, tzmin));
	t1 = min(txmax, min(tymax, tzmax));

	if (t0 > t1)
		return(false);

	//求最初相交的栅格
	int ix, iy, iz;
	//阴影光线起点是否在包围盒中
	if (bbox.Inside(ray.o))
	{
		ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	else
	{//阴影光线与包围盒相交最近（小）值的交点
		Point3D p = ray.o + t0 * ray.d;
		ix = clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1);
	}

	//步进增量
	double dtx = (txmax - txmin) / nx;
	double dty = (tymax - tymin) / ny;
	double dtz = (tzmax - tzmin) / nz;
	double 	txnext, tynext, tznext;
	int 	ixstep, iystep, izstep;
	int 	ixstop, iystop, izstop;
	//x轴方向上与下一个相交栅格的射线参数t
	if (dx > 0)
	{
		txnext = txmin + (ix + 1) * dtx;
		ixstep = +1;
		ixstop = nx;
	}
	else
	{
		txnext = txmin + (nx - ix) * dtx;
		ixstep = -1;
		ixstop = -1;
	}
	if (dx == 0.0)
	{
		txnext = kHugeValue;
		ixstep = -1;
		ixstop = -1;
	}

	//y轴方向上与下一个相交栅格的射线参数t
	if (dy > 0)
	{
		tynext = tymin + (iy + 1) * dty;
		iystep = +1;
		iystop = ny;
	}
	else
	{
		tynext = tymin + (ny - iy) * dty;
		iystep = -1;
		iystop = -1;
	}
	if (dy == 0.0)
	{
		tynext = kHugeValue;
		iystep = -1;
		iystop = -1;
	}
	//z轴方向上与下一个相交栅格的射线参数t
	if (dz > 0)
	{
		tznext = tzmin + (iz + 1) * dtz;
		izstep = +1;
		izstop = nz;
	}
	else
	{
		tznext = tzmin + (nz - iz) * dtz;
		izstep = -1;
		izstop = -1;
	}
	if (dz == 0.0)
	{
		tznext = kHugeValue;
		izstep = -1;
		izstop = -1;
	}

	//阴影光线遍历全部栅格
	while (1)
	{
		GeometricObject* pObj = cells[ix + nx * iy + nx * ny * iz];
		//阴影光线始终经过txnext，tynext，tznext三者中最小的一方轴向的栅格
		if (txnext < tynext&&txnext < tznext)
		{//求最近碰撞点
			if (pObj&&pObj->ShadowHit(ray, tmin) && tmin < txnext)
			{
				return true;
			}
			txnext += dtx;
			ix += ixstep;
			if (ix == ixstop)
				return false;
		}
		else if (tynext < tznext)
		{
			//求最近碰撞点
			if (pObj&&pObj->ShadowHit(ray, tmin) && tmin < tynext)
			{
				return true;
			}
			tynext += dty;
			iy += iystep;
			if (iy == iystop)
				return false;
		}
		else
		{
			//求最近碰撞点
			if (pObj&&pObj->ShadowHit(ray, tmin) && tmin < tznext)
			{
				return true;
			}
			tznext += dtz;
			iz += izstep;
			if (iz == izstop)
				return false;
		}
	}
}

void Grid::SetupCells()
{
	Point3D p0 = FindMinBounds();
	Point3D p1 = FindMaxBounds();

	bbox.x0 = p0.x;
	bbox.y0 = p0.y;
	bbox.z0 = p0.z;

	bbox.x1 = p1.x;
	bbox.y1 = p1.y;
	bbox.z1 = p1.z;

	//----------计算xyz每个轴的栅格的个数------------
	int numObjs = objects.size();
	//xyz每个轴的长度
	double wx = p1.x - p0.x;
	double wy = p1.y - p0.y;
	double wz = p1.z - p0.z;
	//栅格个数放大系数，系数大小取决于物体数目
	double multiplier = 1.5;
	//单个栅格的长度
	double s = pow(wx*wy*wz / numObjs, 0.333333);
	//xyz每个轴的栅格的个数
	nx = multiplier*wx / s + 1;
	ny = multiplier*wy / s + 1;
	nz = multiplier*wz / s + 1;

	//初始化全部栅格
	int numCells = nx*ny*nz;
	cells.reserve(numCells);
	for (int i = 0; i < numCells; i++)
		cells.push_back(NULL);

	//临时变量，记录每个栅格的物体数目
	int *counts = new int[numCells];
	for (int i = 0; i < numCells; i++)
		counts[i] = 0;

	BBox objBox;
	int index;
	for (int i = 0; i < numObjs; i++)
	{
		objBox = objects[i]->GetBoundingBox();
		//求出包围盒最小顶点和最大顶点的索引(ix,iy,iz)
		int ixmin = clamp((objBox.x0 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymin = clamp((objBox.y0 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmin = clamp((objBox.z0 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);
		int ixmax = clamp((objBox.x1 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymax = clamp((objBox.y1 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmax = clamp((objBox.z1 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);
		//把物体添加到栅格上
		for (int iz = izmin; iz <= izmax; iz++)
		{
			for (int iy = iymin; iy <= iymax; iy++)
			{
				for (int ix = ixmin; ix <= ixmax; ix++)
				{//三维索引转化为一维索引计算来维护一维数组
					index = ix + nx*iy + nx*ny*iz;
					if (counts[index] == 0)
					{
						cells[index] = objects[i];
						++counts[index];
					}
					else if (counts[index] == 1)
					{
						Compound* pCompound = new Compound;
						pCompound->AddObject(cells[index]);//添加原有的物体，即第一个物体
						pCompound->AddObject(objects[i]);//添加即第二个物体
						cells[index] = pCompound;//指向Compound， 实现存储多个物体
						++counts[index];
					}
					else
					{
						static_cast<Compound*>(cells[index])->AddObject(objects[i]);
						++counts[index];
					}
				}
			}
		}
	}
	objects.erase(objects.begin(), objects.end());

	delete[] counts;

}

Point3D Grid::FindMinBounds()
{
	BBox objectBox;
	Point3D p0(kHugeValue);
	int num = objects.size();
	for (int i = 0; i < num; i++)
	{
		objectBox = objects[i]->GetBoundingBox();
		if (objectBox.x0 < p0.x)
			p0.x = objectBox.x0;
		if (objectBox.y0 < p0.y)
			p0.y = objectBox.y0;
		if (objectBox.z0 < p0.z)
			p0.z = objectBox.z0;
	}

	p0.x -= kEpsilon;
	p0.y -= kEpsilon;
	p0.z -= kEpsilon;
	return p0;
}
Point3D Grid::FindMaxBounds()
{
	BBox objectBox;
	Point3D p1(-kHugeValue);
	int num = objects.size();
	for (int i = 0; i < num; i++)
	{
		objectBox = objects[i]->GetBoundingBox();
		if (objectBox.x0 > p1.x)
			p1.x = objectBox.x1;
		if (objectBox.y0 > p1.y)
			p1.y = objectBox.y1;
		if (objectBox.z0 > p1.z)
			p1.z = objectBox.z1;
	}

	p1.x += kEpsilon;
	p1.y += kEpsilon;
	p1.z += kEpsilon;
	return p1;
}


/*ReadPLYFile
*
*
*读取PLY文件来建模
*
*/
void Grid::ReadPLYFile(const char * filename, const int triangleType)
{
	//定义顶点
	typedef struct Vertex
	{
		float x, y, z;//空间坐标系
	}Vertex;
	//定义面
	typedef struct Face
	{
		unsigned char numVertices;
		int *vertices;
	}Face;

	PlyProperty vertProps[] =
	{
		{ "x",Float32,Float32,offsetof(Vertex,x),0,0,0,0 },
		{ "y",Float32,Float32,offsetof(Vertex,y),0,0,0,0 },
		{ "z",Float32,Float32,offsetof(Vertex,z),0,0,0,0 }
	};

	PlyProperty faceProps[] =
	{
		{ "vertex_indices",Int32,Int32,offsetof(Face,vertices),1,Uint8,Uint8,offsetof(Face,numVertices)}
	};

	int 			i, j;
	PlyFile*		ply;
	FILE* pFile = fopen(filename, "r");
	ply = read_ply(pFile);

	int 			nelems = ply->num_elem_types;		// number of element types: 2 in our case - vertices and faces

	int 			nprops;		// number of properties each element has
	int 			num_elems;	// number of each type of element: number of vertices or number of faces
	PlyProperty**	plist;

	char*			elem_name;


#ifdef TEST
	int 			file_type = ply->file_type;
	float 			version = ply->version;
	printf("Version %f\n", version);
	printf("type %d\n", file_type);
#endif
	for (i = 0; i < nelems; i++)
	{
		elem_name = ply->elems[i]->name;
		plist = get_element_description_ply(ply, elem_name, &num_elems, &nprops);
#ifdef TEST
		// print the name of the element, for debugging
		std::cout << "element name  " << elem_name << "  num elements = " << num_elems << "  num properties =  " << nprops << std::endl;
#endif

		if (equal_strings("vertex", elem_name))
		{
			ply_get_property(ply, elem_name, &vertProps[0]);
			ply_get_property(ply, elem_name, &vertProps[1]);
			ply_get_property(ply, elem_name, &vertProps[2]);

			//存储在网格当中
			pMesh->numVertices = num_elems;
			pMesh->vertices.reserve(num_elems);

			for (j = 0; j < num_elems; j++)
			{
				Vertex* pVertex = new Vertex;
				ply_get_element(ply, (void *)pVertex);
				pMesh->vertices.push_back(Point3D(pVertex->x, pVertex->y, pVertex->z));
				delete pVertex;
			}
		}

		if (equal_strings("face", elem_name))
		{
			ply_get_property(ply, elem_name, &faceProps[0]);
			pMesh->numTriangles = num_elems;
			objects.reserve(num_elems);

			pMesh->vertexFaces.reserve(pMesh->numVertices);
			std::vector<int> faceList;

			for (j = 0; j < pMesh->numVertices; j++)
				pMesh->vertexFaces.push_back(faceList);

			int count = 0;
			for (j = 0; j < num_elems; j++)
			{
				Face* face_ptr = new Face;

				ply_get_element(ply, (void *)face_ptr);

				// construct a mesh triangle of the specified type

				if (triangleType == flat) {
					FlatMeshTriangle* triangle_ptr = new FlatMeshTriangle(pMesh, face_ptr->vertices[0], face_ptr->vertices[1], face_ptr->vertices[2]);
					triangle_ptr->ComputeNormal(isReverseNormal);
					objects.push_back(triangle_ptr);
				}

				if (triangleType == smooth) {
					SmoothMeshTriangle* triangle_ptr = new SmoothMeshTriangle(pMesh, face_ptr->vertices[0], face_ptr->vertices[1], face_ptr->vertices[2]);
					triangle_ptr->ComputeNormal(isReverseNormal); 	// the "flat triangle" normal is used to compute the average normal at each mesh vertex
					objects.push_back(triangle_ptr); 				// it's quicker to do it once here, than have to do it on average 6 times in compute_mesh_normals

																	// the following code stores a list of all faces that share a vertex
																	// it's used for computing the average normal at each vertex in order(num_vertices) time

					pMesh->vertexFaces[face_ptr->vertices[0]].push_back(count);
					pMesh->vertexFaces[face_ptr->vertices[1]].push_back(count);
					pMesh->vertexFaces[face_ptr->vertices[2]].push_back(count);
					count++;
				}
			}

			if (triangleType == flat)
				pMesh->vertexFaces.erase(pMesh->vertexFaces.begin(), pMesh->vertexFaces.end());
		}

		// print out the properties we got, for debugging
#ifdef TEST
		for (j = 0; j < nprops; j++)
			printf("property %s\n", plist[j]->name);
#endif
	}  // end of for (i = 0; i < nelems; i++) 


	   // grab and print out the comments in the file
#ifdef TEST
	comments = get_comments_ply(ply, &num_comments);

	for (i = 0; i < num_comments; i++)
		printf("comment = '%s'\n", comments[i]);

	// grab and print out the object information

	obj_info = get_obj_info_ply(ply, &num_obj_info);

	for (i = 0; i < num_obj_info; i++)
		printf("obj_info = '%s'\n", obj_info[i]);
#endif
	// close the ply file 

	close_ply(ply);
	free_ply(ply);
}


void Grid::ComputeMeshNormals()
{
	pMesh->normals.reserve(pMesh->numVertices);
	for (int i = 0; i < pMesh->numVertices; i++)
	{
		Normal normal;

		for (int j = 0; j < pMesh->vertexFaces[i].size(); j++)
		{
			normal += objects[pMesh->vertexFaces[i][j]]->GetNormal();
		}
		if (normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0)
			normal.y = 1.0;
		else
			normal.normalize();

		pMesh->normals.push_back(normal);
	}

	//释放资源
	for (int i = 0; i < pMesh->numVertices; i++)
	{
		pMesh->vertexFaces[i].erase(pMesh->vertexFaces[i].begin(), pMesh->vertexFaces[i].end());
	}
	pMesh->vertexFaces.erase(pMesh->vertexFaces.begin(), pMesh->vertexFaces.end());
}