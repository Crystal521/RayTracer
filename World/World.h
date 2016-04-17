#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>

#include "ViewPlane.h"
#include "RGBColor.h"
#include "Tracer.h"
#include "GeometricObject.h"
#include "Sphere.h"
#include "Ray.h"

#include "Camera.h"
#include "Light.h"
#include "Ambient.h"



class QImage;

class World
{
public:
	ViewPlane vp;
	RGBColor backgroundColor;
	Tracer*  pTracer;
	Camera*  pCamera;
	Light* pAmbient;
	Sphere	 sphere;

	std::vector<GeometricObject*> objects;
	std::vector<Light*> lights;

	QImage*  renderArea;
public:
	World();
	~World();

	void AddObject(GeometricObject* pObeject);
	void AddLight(Light* pLight);

	void SetCamera(Camera* pCam);
	void SetAmbientLight(Ambient* pAmb);

	void RenderScene() const;

	void Build();

	RGBColor MaxToOne(const RGBColor& c) const;
	RGBColor ClampToColor(const RGBColor& c) const;

	void DisplayPixel(const int row, const int column, const RGBColor& pixelColor) const;

	ShadeRec HitObjects(const Ray& ray);
	//ShadeRec hit_bare_bones_objects(const Ray& ray);
private:
	void DeleteObjects();
	void DeleteLights();
};


inline void World::AddObject(GeometricObject* pObeject)
{
	objects.push_back(pObeject);
}

inline void World::AddLight(Light* pLight)
{
	lights.push_back(pLight);
}

inline void World::SetCamera(Camera* pCam)
{
	pCamera = pCam;
}
inline void World::SetAmbientLight(Ambient* pAmb)
{
	pAmbient = pAmb;
}
#endif//_WORLD_H_
