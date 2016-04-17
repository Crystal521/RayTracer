// this file contains the definition of the World class

#include <QImage.h>
#include <qRGB>

#include "World.h"
#include "Constants.h"

#include "Plane.h"
#include "Sphere.h"
#include "RayCast.h"
#include "Whitted.h"
#include "Pinhole.h"
#include "Matte.h"
#include "Dielectric.h"
#include "Phong.h"

#include "Directional.h"
#include "PointLight.h"


#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"
#include "Mesh.h"
#include "Instance.h"
#include "Grid.h"


World::World()
	: backgroundColor(black),
	pTracer(NULL),
	pAmbient(new Ambient),
	pCamera(NULL),
	renderArea(new QImage(450,450,QImage::Format_ARGB32))
{}



World::~World()
{

	if (pTracer) {
		delete pTracer;
		pTracer = NULL;
	}


	if (pAmbient) {
		delete pAmbient;
		pAmbient = NULL;
	}


	if (pCamera) {
		delete pCamera;
		pCamera = NULL;
	}

	DeleteObjects();
	DeleteLights();

	delete renderArea;
}

//用于正交视图
void World::RenderScene() const
{

	RGBColor	pixel_color;
	Ray			ray;
	int 		hres = vp.hres;
	int 		vres = vp.vres;
	float		pixelSize = vp.pixelSize;
	float		zw = 100.0;

	ray.d = Vector3D(0, 0, -1);

	for (int r = 0; r < vres; r++)
		for (int c = 0; c <= hres; c++) {
			ray.o = Point3D(pixelSize * (c - hres / 2.0 + 0.5), pixelSize * (r - vres / 2.0 + 0.5), zw);
			pixel_color = pTracer->TraceRay(ray);
			DisplayPixel(r, c, pixel_color);
		}
}


RGBColor World::MaxToOne(const RGBColor& c) const
{
	float max_value = max(c.r, max(c.g, c.b));

	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}



RGBColor World::ClampToColor(const RGBColor& raw_color) const
{
	RGBColor c(raw_color);

	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}

	return (c);
}

void
World::DisplayPixel(const int row, const int column, const RGBColor& raw_color) const
{
	RGBColor color;

	if (vp.showOutOfGamut)
		color = ClampToColor(raw_color);
	else
		color = MaxToOne(raw_color);

	if (vp.gamma != 1.0)
		color = color.powc(vp.invGamma);

	int x = column;
	int y = vp.vres - row - 1;

	int r = (int)(color.r * 255);
	int g = (int)(color.g * 255);
	int b = (int)(color.b * 255);
	renderArea->setPixel(x, y, qRgb(r, g,b));
}


ShadeRec World::HitObjects(const Ray& ray) 
{
	ShadeRec	sr(*this);
	double		t;
	Normal normal;
	Point3D localHitPoint;
	double		tmin = kHugeValue;
	int 		numObjects = objects.size();

	for (int j = 0; j < numObjects; j++)
		if (objects[j]->Hit(ray, t, sr) && (t < tmin)) {
			sr.isHit = true;
			tmin = t;
			sr.pMaterial = objects[j]->GetMaterial();
			sr.hitPoint = ray.o + t * ray.d;
			normal = sr.normal;
			localHitPoint = sr.localHitPoint;
		}

	if (sr.isHit) {
		sr.t = tmin;
		sr.normal = normal;
		sr.localHitPoint = localHitPoint;
	}

	return sr;
}


void World::DeleteObjects() 
{
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}

	objects.erase(objects.begin(), objects.end());
}

void World::DeleteLights() {
	int numlights = lights.size();

	for (int j = 0; j < numlights; j++) {
		delete lights[j];
		lights[j] = NULL;
	}

	lights.erase(lights.begin(), lights.end());
}

void World::Build() {
	int numSamples = 16;

	vp.SetHres(450);
	vp.SetVres(450);
	vp.SetSamples(numSamples);
	vp.SetMaxDepth(1);

	backgroundColor=RGBColor(0.35,0.62,1.0);

	pTracer = new Whitted(this);

	Ambient* pAmb = new Ambient;
	pAmb->ScaleRadiance(0.5);
	SetAmbientLight(pAmb);


	Pinhole* pPinhole = new Pinhole;
	pPinhole->SetEye(-300, 150, -20);
	pPinhole->SetLookAt(0);
	pPinhole->SetViewDistance(300);
	pPinhole->ComputeUVW();
	SetCamera(pPinhole);

	Directional *sunLight = new Directional();
	sunLight->SetDirection(-1, 1, 1);
	AddLight(sunLight);

	//Dielectric* pDielectric = new Dielectric;
	//pDielectric->SetKa(0.0);
	//pDielectric->SetKd(0.0);
	//pDielectric->SetKs(0.2);
	//pDielectric->SetExp(2000.0);
	//pDielectric->SetEtaIn(1.5);
	//pDielectric->SetEtaOut(1.0);
	//pDielectric->SetCfIn(0.65, 0.65, 0.1);   // lemon
	//pDielectric->SetCfOut(white);



		
	//Ground
	Matte* pMatte = new Matte;
	pMatte->SetKa(0.55);
	pMatte->SetKd(0.3);
	pMatte->SetCd(0, 1, 0);   	// light green

	Plane* plane = new Plane(Point3D(0), Normal(0, 1, 0));
	plane->SetMaterial(pMatte);
	AddObject(plane);

	//Sphere one
	//Phong *pPhong = new Phong;
	//pPhong->SetCd(1, 1, 1);
	//pPhong->SetExp(1.0);
	//pPhong->SetKa(1.0);
	//pPhong->SetKd(1.25);
	//pPhong->SetKs(0.30);

	//Sphere *sp = new Sphere;
	//sp->SetCenter(-30, 20,-10);
	//sp->SetRadius(20);
	//sp->SetMaterial(pPhong);
	//AddObject(sp);


	/***************Material*****************/
	Phong *pPhong2 = new Phong;
	pPhong2->SetCd(1, 0, 1);
	pPhong2->SetExp(1.0);
	pPhong2->SetKa(1.0);
	pPhong2->SetKd(1.25);
	pPhong2->SetKs(0.30);

	/***************Sphere*****************/
	//Sphere *sp2 = new Sphere;
	//sp2->SetCenter(0);
	//sp2->SetRadius(2);
	//sp2->SetMaterial(pPhong2);

	//Instance* pBigSphere = new Instance(sp2);
	//pBigSphere->Translate(1,1,-5);
	//pBigSphere->Scale(50, 25, 4.15);
	//AddObject(pBigSphere);

	/***************model cube*****************/
	const char *file_name = "ply_models/bun_zipper.ply";
	Grid* pCube = new Grid(new Mesh);
	//pHorse->ReadFlatTriangles(file_name);	
	pCube->ReadSmoothTriangles(file_name);
	pCube->SetMaterial(pPhong2->Clone());
	pCube->SetupCells();

	Instance* pBigCube = new Instance(pCube);
	pBigCube->Scale(100.0);
	pBigCube->RotateY(0.3);
	//pBigCube->Translate(-50, 80, 40);
	AddObject(pBigCube);
}