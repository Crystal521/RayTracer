#ifndef _SMOOTH_MESH_TRIANGLE_H_
#define _SMOOTH_MESH_TRIANGLE_H_

#include "MeshTriangle.h"

class SmoothMeshTriangle : public MeshTriangle {
public:
	SmoothMeshTriangle();
	SmoothMeshTriangle(const SmoothMeshTriangle& fmt);
	SmoothMeshTriangle(Mesh* pMesh, const int i0, const int i1, const int i2);
	virtual ~SmoothMeshTriangle();

	virtual SmoothMeshTriangle* Clone() const;
	SmoothMeshTriangle& operator= (const SmoothMeshTriangle& rhs);
	virtual	bool Hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	//virtual bool ShadowHit(const Ray& ray, float &tmin) const override;
protected:
	Normal InterpolateNormal(const float beta, const float gamma) const;
};

#endif//_SMOOTH_MESH_TRIANGLE_H_