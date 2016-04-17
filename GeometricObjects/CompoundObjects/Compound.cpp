#include "Compound.h"
#include "Constants.h"
Compound::Compound()
	:GeometricObject()
{
}

Compound::Compound(const Compound & other)
	: GeometricObject(other)
{
	CopyObjects(objects);
}

Compound::~Compound()
{
	DeleteObjects();
}

Compound & Compound::operator=(const Compound & rhs)
{
	if (this == &rhs)
		return *this;

	GeometricObject::operator= (rhs);

	CopyObjects(rhs.objects);

	return *this;
}

Compound * Compound::Clone() const
{
	return new Compound(*this);
}

void Compound::SetMaterial(Material * pMat)
{
	int num = objects.size();
	for (int i = 0; i < num; ++i)
	{
		objects[i]->SetMaterial(pMat);
	}
}

void Compound::AddObject(GeometricObject * pObj)
{
	objects.push_back(pObj);
}

int Compound::GetNumObjects() 
{
	return objects.size();
}

bool Compound::Hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	double t;
	Normal normal;
	Point3D localHitPoint;
	bool isHit = false;
	int num = objects.size();
	tmin = kHugeValue;
	for (int j = 0; j < num; j++)
	{
		if (objects[j]->Hit(ray, t, sr) && (t < tmin))
		{
			isHit = true;
			tmin = t;
			pMaterial = objects[j]->GetMaterial();
			normal = sr.normal;
			localHitPoint = sr.localHitPoint;
		}
	}
	if (isHit)
	{
		sr.t = tmin;
		sr.normal = normal;
		sr.localHitPoint = localHitPoint;
	}
	return isHit;
}

bool Compound::ShadowHit(const Ray & ray, float & tmin) const
{
	int num = objects.size();
	bool isHit = false;
	float t = kHugeValue;
	tmin = kHugeValue;
	
	for (int j = 0; j < num; j++)
	{
		if (objects[j]->ShadowHit(ray, t)&&t<tmin)
		{
			tmin = t;
			isHit = true;
		}
	}

	return isHit;
}


void Compound::DeleteObjects()
{
	int num = objects.size();
	for (int i = 0; i < num; i++)
	{
		delete objects[i];
		objects[i] = NULL;
	}
	objects.erase(objects.begin(), objects.end());
}

void Compound::CopyObjects(const std::vector<GeometricObject*>& rhs)
{
	DeleteObjects();
	int num = rhs.size();
	for (int i = 0; i < num; i++)
	{
		objects.push_back(rhs[i]);
	}
}