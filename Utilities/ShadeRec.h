#ifndef _SHADEREC_H_
#define _SHADEREC_H_


#include "Normal.h"
#include "RGBColor.h"
#include "Point3D.h"
#include "Ray.h"

class Material;
class World;
class ShadeRec
{
public:
	ShadeRec(World &wr);
	ShadeRec(const ShadeRec& sr);
	~ShadeRec();

	//光线与物体是否碰撞
	bool isHit;
	Material* pMaterial;
	//世界坐标系下碰撞的点
	Point3D hitPoint;
	//碰撞的点对到物体纹理的坐标，用于纹理变换
	Point3D localHitPoint;
	//碰撞点的法线
	Normal normal;
	//需要高光和区域灯光
	Ray ray;
	//递归的深度
	int depth;
	//光线方程中的参数t
	float t;
	//用于的着色世界坐标
	World &w;

	RGBColor color;
	//ShadeRec& operator=(const ShadeRec& rhs);
};


#endif
