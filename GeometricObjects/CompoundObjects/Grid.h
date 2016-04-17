#ifndef _GRID_H_
#define _GRID_H_


#include "Compound.h"
#include "ShadeRec.h"
#include "Mesh.h"

class Grid:public Compound
{
public:
	Grid();
	Grid(Mesh* pMesh);
	Grid(const Grid& other);
	virtual ~Grid();
	virtual Grid* Clone() const;
	Grid& 	operator= (const Grid& rhs);

	virtual BBox GetBoundingBox();
	void ReadFlatTriangles(const char* filename);
	void ReadSmoothTriangles(const char* filename);
	void TessellateFlatSphere(const int horizontalSteps, const int verticalSteps);
	void TessellateSmoothSphere(const int horizontalSteps, const int verticalSteps);

	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec& s)const;
	virtual bool ShadowHit(const Ray& ray, float &tmin) const;
	void  SetupCells();
	void ReverseMeshNormals();
	void StoreMaterial(Material* material, const int index);
private:
	std::vector<GeometricObject*> cells;
	int nx, ny, nz;//作为xyz方向上的索引
	BBox bbox;
	Mesh* pMesh;
	bool isReverseNormal;//部分PLY文件的顶点的法线是向内的,需要判断
private:
	Point3D FindMinBounds();
	Point3D FindMaxBounds();
	void ReadPLYFile(const char* filename, const int triangleType);
	void ComputeMeshNormals();
};


inline void Grid::ReverseMeshNormals() 
{
	isReverseNormal = true;
}


inline void
Grid::StoreMaterial(Material* material_ptr, const int index) 
{
	objects[index]->SetMaterial(material_ptr);
}

#endif//_GRID_H_
