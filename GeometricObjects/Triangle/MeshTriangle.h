#ifndef __MESH_TRIANGLE_H_
#define __MESH_TRIANGLE_H_

#include "GeometricObject.h"
#include "Mesh.h"

//本类含有三个顶点法线，
//用于平滑着色时跟碰撞点处进行线性插值
class MeshTriangle :public GeometricObject
{
public:

	MeshTriangle();
	MeshTriangle(const MeshTriangle& mt);
	MeshTriangle(Mesh* pMesh, const int i1, const int i2, const int i3);
	virtual ~MeshTriangle();

	virtual MeshTriangle* Clone() const = 0;
	MeshTriangle& operator= (const MeshTriangle& rhs);

	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
	virtual	bool ShadowHit(const Ray& ray, float & tmin) const;
	virtual Normal GetNormal() const;
	virtual BBox GetBoundingBox();
	
	void ComputeNormal(const bool revNormal);

public:
	Mesh* 		pMesh;
	int			index0, index1, index2;  //网格中单个三角形，在数组中的索引
	Normal		normal;
	float		area;					//用于透明

protected:
	float InterpolateU(const float beta, const float gamma) const;
	float InterpolateV(const float beta, const float gamma) const;

};

#endif//__MESH_TRIANGLE_H_