#ifndef __FLAT_MESH_TRIANGLE__
#define __FLAT_MESH_TRIANGLE__


#include "MeshTriangle.h"

class FlatMeshTriangle: public MeshTriangle {	
	public:
		
		FlatMeshTriangle();   									
		FlatMeshTriangle(const FlatMeshTriangle& fmt);
		FlatMeshTriangle(Mesh* pMesh, const int i0, const int i1, const int i2);		

		virtual FlatMeshTriangle* Clone() const;
		virtual	~FlatMeshTriangle();   									
		//virtual bool ShadowHit(const Ray& ray, float &tmin) const;

		FlatMeshTriangle& operator= (const FlatMeshTriangle& rhs);
				
		virtual	bool Hit(const Ray& ray, double& tmin, ShadeRec& sr) const; 																	
};

#endif

