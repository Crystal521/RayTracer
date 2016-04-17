#ifndef _INSTANCE_H_
#define _INSTANCE_H_
#include "GeometricObject.h"
#include "Matrix.h"
class Instance :public GeometricObject
{
public:
	Instance();
	Instance(GeometricObject* pobj);
	Instance(const Instance& object);
	Instance& Instance::operator= (const Instance& rhs);
	virtual ~Instance();

	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec &sr) const;
	virtual Instance* Clone() const;

	virtual bool ShadowHit(const Ray& ray, float &tmin) const;
	virtual void ComputeBoundingBox();
	virtual BBox GetBoundingBox();

	void SetObject(GeometricObject* pobj);
	void TransformTexture(const bool transform);
	
	virtual Material* GetMaterial() const;
	virtual void SetMaterial(Material* pMaterial);

	void Translate(const Vector3D& trans);
	void Translate(const double dx, const double dy, const double dz);

	void Scale(const Vector3D& s);
	void Scale(const double x, const double y, const double z);

	void RotateX(const double r);
	void RotateY(const double r);
	void RotateZ(const double r);

	void Shear(const Matrix& m);
private:
	GeometricObject* pObj;		//变换的物体
	Matrix invMatrix;			//逆矩阵
	static Matrix forwardMatrix;//变换矩阵
	BBox aabb;					//AABB包围盒
	bool isTransformTexture;		//是否变换纹理
};

inline void Instance::TransformTexture(const bool transform)
{
	isTransformTexture = transform;
}
#endif//_INSTANCE_H_