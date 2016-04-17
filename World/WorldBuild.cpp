#include "World.cpp"

void World::Build() {
	int numSamples = 16;

	vp.SetHres(400);
	vp.SetVres(400);
	vp.SetSamples(numSamples);
	vp.SetMaxDepth(1);

	backgroundColor = RGBColor(0.35, 0.62, 1.0);

	pTracer = new Whitted(this);

	Ambient* pAmb = new Ambient;
	pAmb->ScaleRadiance(0.5);
	SetAmbientLight(pAmb);


	Pinhole* pPinhole = new Pinhole;
	pPinhole->SetEye(-300, 100, 0);
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

	//const char *file_name = "ply_models/cube.ply";

	//Grid* pHorse = new Grid(new Mesh);
	////	horse_ptr->read_flat_triangles(file_name);	
	//pHorse->ReadSmoothTriangles(file_name);
	//pHorse->SetMaterial(pDielectric);
	//pHorse->SetupCells();





	//Instance* pBigSphere = new Instance(sp);
	////pBigSphere->Scale(1.0);
	////pBigSphere->Translate(40,10,0);
	//AddObject(pBigSphere);

	//Instance* pBigSphere2 = new Instance(pBigSphere);
	//pBigSphere2->Scale(1.5);
	//pBigSphere2->Translate(-10, 0, 0);
	//AddObject(pBigSphere2);

	Matte* pMatte = new Matte;
	pMatte->SetKa(0.55);
	pMatte->SetKd(0.3);
	pMatte->SetCd(0, 1, 0);   	// light green

	Plane* plane = new Plane(Point3D(0), Normal(0, 1, 0));
	plane->SetMaterial(pMatte);
	AddObject(plane);

	Phong *pPhong = new Phong;
	pPhong->SetCd(1, 1, 1);
	pPhong->SetExp(1.0);
	pPhong->SetKa(1.0);
	pPhong->SetKd(1.25);
	pPhong->SetKs(0.30);

	Sphere *sp = new Sphere;
	sp->SetCenter(-30, 20, -10);
	sp->SetRadius(20);
	sp->SetMaterial(pPhong);
	AddObject(sp);

	Phong *pPhong2 = new Phong;
	pPhong2->SetCd(1, 0, 1);
	pPhong2->SetExp(1.0);
	pPhong2->SetKa(1.0);
	pPhong2->SetKd(1.25);
	pPhong2->SetKs(0.30);

	Sphere *sp2 = new Sphere;
	sp2->SetCenter(-150, 15, 20);
	sp2->SetRadius(15);
	sp2->SetMaterial(pPhong2);
	AddObject(sp2);

}