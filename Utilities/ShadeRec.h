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

	//�����������Ƿ���ײ
	bool isHit;
	Material* pMaterial;
	//��������ϵ����ײ�ĵ�
	Point3D hitPoint;
	//��ײ�ĵ�Ե�������������꣬��������任
	Point3D localHitPoint;
	//��ײ��ķ���
	Normal normal;
	//��Ҫ�߹������ƹ�
	Ray ray;
	//�ݹ�����
	int depth;
	//���߷����еĲ���t
	float t;
	//���ڵ���ɫ��������
	World &w;

	RGBColor color;
	//ShadeRec& operator=(const ShadeRec& rhs);
};


#endif
