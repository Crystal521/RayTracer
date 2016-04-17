#ifndef _COMPOUND_H_
#define _COMPOUND_H_

#include <vector> 
#include "GeometricObject.h"


class Compound :public GeometricObject
{
public:
	Compound();
	Compound(const Compound& other);
	virtual ~Compound();

	Compound& operator=(const Compound& c);
	virtual Compound* Clone() const;
	virtual void SetMaterial(Material *pMat);
	virtual void AddObject(GeometricObject* pObj);
	int GetNumObjects();

	virtual bool Hit(const Ray& ray, double& tmin, ShadeRec& s)const;
	virtual bool ShadowHit(const Ray& ray, float &tmin) const;
protected:
	std::vector<GeometricObject*> objects;
private:
	void DeleteObjects();
	void CopyObjects(const std::vector<GeometricObject*>& rhs);
};

#endif//_COMPOUND_H_
