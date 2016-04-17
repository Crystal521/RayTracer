#include "Constants.h"
#include "ShadeRec.h"


ShadeRec::ShadeRec(World & wr)
	:isHit(false),
	pMaterial(NULL),
	hitPoint(),
	localHitPoint(),
	normal(),
	ray(),
	depth(0),
	t(0.0f),
	w(wr)
{}

ShadeRec::ShadeRec(const ShadeRec & sr)
	:isHit(sr.isHit),
	pMaterial(sr.pMaterial),
	hitPoint(sr.hitPoint),
	localHitPoint(sr.localHitPoint),
	normal(sr.normal),
	ray(sr.ray),
	depth(sr.depth),
	t(sr.t),
	w(sr.w)
{}

ShadeRec::~ShadeRec()
{
}

//ShadeRec & ShadeRec::operator=(const ShadeRec & rhs)
//{
//	// TODO: 在此处插入 return 语句
//}
