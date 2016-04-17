#include "Instance.h"
#include "Constants.h"
#include <math.h>

Matrix Instance::forwardMatrix;

Instance::Instance()
	:GeometricObject(),
	pObj(0),
	invMatrix(),
	aabb(),
	isTransformTexture(false)
{
	forwardMatrix.set_identity();
}

Instance::Instance(GeometricObject * pobj)
	:GeometricObject(),
	pObj(pobj),
	invMatrix(),
	aabb(),
	isTransformTexture(false)
{
	forwardMatrix.set_identity();
}

Instance::Instance(const Instance & object)
	:GeometricObject(object),
	invMatrix(object.invMatrix),
	isTransformTexture(object.isTransformTexture)
{
	if (object.pObj)
		pObj = object.pObj;
	else
		pObj = NULL;
}

Instance & Instance::operator=(const Instance & rhs)
{
	if (this == &rhs)
		return *this;
	
	GeometricObject::operator=(rhs);
	if (pObj)
	{
		delete pObj;
		pObj = NULL;
	}
	if (rhs.pObj)
		pObj = rhs.pObj->Clone();
	else
		pObj = NULL;

	invMatrix = rhs.invMatrix;
	aabb = rhs.aabb;
	isTransformTexture = rhs.isTransformTexture;

	return *this;
}


Instance::~Instance()
{
	if (pObj) 
	{
		delete pObj;
		pObj = NULL;
	}
}

bool Instance::Hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	Ray invRay(ray);
	//对光线左乘逆变换矩阵，转化为穿过未变换对象上某点像素的光线
	invRay.o = invMatrix*invRay.o;
	invRay.d = invMatrix*invRay.d;
	if (pObj->Hit(invRay, tmin, sr))
	{
		//注意重载操作符*的第二个参数类型是法线类型
		//进行的是逆转置矩阵与法线相乘
		sr.normal = invMatrix*sr.normal;
		sr.normal.normalize();
		if (pObj->GetMaterial())
			pMaterial = pObj->GetMaterial();
		if (!isTransformTexture)
			sr.localHitPoint = ray.o + tmin*ray.d;
		return true;
	}
	return false;
}

Instance * Instance::Clone() const
{
	return new Instance(*this);
}

bool Instance::ShadowHit(const Ray & ray, float & tmin) const
{
	Ray invRay(ray);
	//对光线左乘逆变换矩阵，转化为穿过未变换对象上某点像素的光线
	invRay.o = invMatrix*invRay.o;
	invRay.d = invMatrix*invRay.d;
	return pObj->ShadowHit(invRay,tmin);
}

void Instance::ComputeBoundingBox()
{
	//获取未变换对象的包围盒
	BBox objectBBox = pObj->GetBoundingBox();

	//对该包围盒应用仿射变换，并求出包围盒的最小点和最大点
	Point3D v[8];
	v[0].x = objectBBox.x0; v[0].y= objectBBox.y0; v[0].z = objectBBox.z0;
	v[1].x = objectBBox.x1; v[1].y = objectBBox.y0; v[1].z = objectBBox.z0;
	v[2].x = objectBBox.x1; v[2].y = objectBBox.y1; v[2].z = objectBBox.z0;
	v[3].x = objectBBox.x0; v[3].y = objectBBox.y1; v[3].z = objectBBox.z0;

	v[4].x = objectBBox.x0; v[4].y = objectBBox.y0; v[4].z = objectBBox.z1;
	v[5].x = objectBBox.x1; v[5].y = objectBBox.y0; v[5].z = objectBBox.z1;
	v[6].x = objectBBox.x1; v[6].y = objectBBox.y1; v[6].z = objectBBox.z1;
	v[7].x = objectBBox.x0; v[7].y = objectBBox.y1; v[7].z = objectBBox.z1;
	//对该包围盒应用仿射变换
	v[0] = forwardMatrix *v[0];
	v[1] = forwardMatrix *v[1];
	v[2] = forwardMatrix *v[2];
	v[3] = forwardMatrix *v[3];
	v[4] = forwardMatrix *v[4];
	v[5] = forwardMatrix *v[5];
	v[6] = forwardMatrix *v[6];
	v[7] = forwardMatrix *v[7];

	//由于forwardMatrix是个静态变量
	//为了不用下一个Instance类型的对象使用
	//需重设为单位矩阵
	forwardMatrix.set_identity();

	//包围盒的最小点
	float x0 = kHugeValue;
	float y0 = kHugeValue;
	float z0 = kHugeValue;
	for (int i = 0; i <= 7; i++)
	{
		if (v[i].x < x0)
			x0 = v[i].x;

		if (v[i].y < y0)
			y0 = v[i].y;

		if (v[i].z < z0)
			z0 = v[i].z;
	}
	//包围盒的最大点
	float x1 = -kHugeValue;
	float y1 = -kHugeValue;
	float z1 = -kHugeValue;

	for (int i = 0; i <= 7; i++)
	{
		if (v[i].x > x1)
			x1 = v[i].x;

		if (v[i].y > y1)
			y1 = v[i].y;

		if (v[i].z > z1)
			z1 = v[i].z;
	}

	aabb.x0 = x0;
	aabb.y0 = y0;
	aabb.z0 = z0;
	aabb.x1 = x1;
	aabb.y1 = y1;
	aabb.z1 = z1;
}

BBox Instance::GetBoundingBox()
{
	return aabb;
}

void Instance::SetMaterial(Material * pMat)
{
	pMaterial = pMat;
}


void Instance::SetObject(GeometricObject * pobj)
{
	pObj = pobj;
}

Material * Instance::GetMaterial() const
{
	return pMaterial;
}

void Instance::Translate(const Vector3D & trans)
{
	Matrix invTranslationMatrix;
	//注意这里常用平移矩阵左乘顶点来进行变换
	//平移参数放在第四列
	invTranslationMatrix.m[0][3] = -trans.x;
	invTranslationMatrix.m[1][3] = -trans.y;
	invTranslationMatrix.m[2][3] = -trans.z;
	invMatrix = invMatrix*invTranslationMatrix;

	Matrix translationMatrix;
	translationMatrix.m[0][3] = trans.x;
	translationMatrix.m[1][3] = trans.y;
	translationMatrix.m[2][3] = trans.z;
	forwardMatrix = translationMatrix * forwardMatrix;
}
void Instance::Translate(const double dx, const double dy, const double dz)
{
	Matrix invTranslationMatrix;
	//注意这里常用平移矩阵左乘顶点来进行变换
	//平移参数放在第四列
	invTranslationMatrix.m[0][3] = -dx;
	invTranslationMatrix.m[1][3] = -dy;
	invTranslationMatrix.m[2][3] = -dz;
	invMatrix = invMatrix * invTranslationMatrix;

	Matrix translationMatrix;
	translationMatrix.m[0][3] = dx;
	translationMatrix.m[1][3] = dy;
	translationMatrix.m[2][3] = dz;
	forwardMatrix = translationMatrix * forwardMatrix;
}
void Instance::Scale(const Vector3D & s)
{
	Matrix invScaleMatrix;
	//注意这里常用平移矩阵左乘顶点来进行变换
	//平移参数放在第四列
	invScaleMatrix.m[0][0] = 1 / s.x;
	invScaleMatrix.m[1][1] = 1 / s.y;
	invScaleMatrix.m[2][2] = 1 / s.z;
	invMatrix = invMatrix*invScaleMatrix;

	Matrix scaleMatrix;
	scaleMatrix.m[0][0] = s.x;
	scaleMatrix.m[1][1] = s.y;
	scaleMatrix.m[2][2] = s.z;
	forwardMatrix = scaleMatrix * forwardMatrix;
}
void Instance::Scale(const double x, const double y, const double z)
{
	Matrix invScaleMatrix;
	//注意这里常用平移矩阵左乘顶点来进行变换
	//平移参数放在第四列
	invScaleMatrix.m[0][0] = 1/x;
	invScaleMatrix.m[1][1] = 1/y;
	invScaleMatrix.m[2][2] = 1/z;
	invMatrix = invMatrix*invScaleMatrix;

	Matrix scaleMatrix;
	scaleMatrix.m[0][0] = x;
	scaleMatrix.m[1][1] = y;
	scaleMatrix.m[2][2] = z;
	forwardMatrix = scaleMatrix * forwardMatrix;
}
void Instance::RotateX(const double theta)
{
	double sinTheta = sin(theta*PI_ON_180);
	double cosTheta = cos(theta*PI_ON_180);
	Matrix invRotateXMatrix;
	invRotateXMatrix.m[1][1] = cosTheta;
	invRotateXMatrix.m[1][2] = sinTheta;
	invRotateXMatrix.m[2][1] = -sinTheta;
	invRotateXMatrix.m[1][1] = cosTheta;
	invMatrix = invMatrix * invRotateXMatrix;

	Matrix rotateXMatrix;
	rotateXMatrix.m[1][1] = cosTheta;
	rotateXMatrix.m[1][2] = -sinTheta;
	rotateXMatrix.m[2][1] = sinTheta;
	rotateXMatrix.m[1][1] = cosTheta;
	forwardMatrix = rotateXMatrix * forwardMatrix;
}
void Instance::RotateY(const double theta)
{
	double sinTheta = sin(theta*PI_ON_180);
	double cosTheta = cos(theta*PI_ON_180);
	Matrix invRotateYMatrix;
	invRotateYMatrix.m[0][0] = cosTheta;
	invRotateYMatrix.m[0][2] = -sinTheta;
	invRotateYMatrix.m[2][0] = sinTheta;
	invRotateYMatrix.m[2][2] = cosTheta;
	invMatrix = invMatrix * invRotateYMatrix;

	Matrix rotateYMatrix;
	rotateYMatrix.m[0][0] = cosTheta;
	rotateYMatrix.m[0][2] = sinTheta;
	rotateYMatrix.m[2][0] = -sinTheta;
	rotateYMatrix.m[2][2] = cosTheta;
	forwardMatrix = rotateYMatrix * forwardMatrix;
}
void Instance::RotateZ(const double theta)
{
	double sinTheta = sin(theta*PI_ON_180);
	double cosTheta = cos(theta*PI_ON_180);
	Matrix invRotateZMatrix;
	invRotateZMatrix.m[0][0] = cosTheta;
	invRotateZMatrix.m[0][1] = sinTheta;
	invRotateZMatrix.m[1][0] = -sinTheta;
	invRotateZMatrix.m[1][1] = cosTheta;
	invMatrix = invMatrix * invRotateZMatrix;

	Matrix rotateZMatrix;
	rotateZMatrix.m[0][0] = cosTheta;
	rotateZMatrix.m[0][1] = -sinTheta;
	rotateZMatrix.m[1][0] = sinTheta;
	rotateZMatrix.m[1][1] = cosTheta;
	forwardMatrix = rotateZMatrix * forwardMatrix;
}
void Instance::Shear(const Matrix & s)
{
	Matrix invShearingMatrix;
	double d = 1.0 - s.m[1][0] * s.m[0][1] 
							  - s.m[2][0] * s.m[0][2]
							  - s.m[2][1] * s.m[1][2]
							 + s.m[1][0] * s.m[2][1] * s.m[0][2]
							 + s.m[2][0] * s.m[0][1] * s.m[2][1];

	// 齐次行
	invShearingMatrix.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
	invShearingMatrix.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
	invShearingMatrix.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
	invShearingMatrix.m[3][3] = d;
	// 第一行
	invShearingMatrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
	invShearingMatrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];
	// 第二行
	invShearingMatrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
	invShearingMatrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];
	// 第三行
	invShearingMatrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
	invShearingMatrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2];
	//
	invShearingMatrix = invShearingMatrix / d;

	invMatrix = invMatrix * invShearingMatrix;

	forwardMatrix = s * forwardMatrix;
}