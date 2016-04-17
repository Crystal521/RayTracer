#ifndef _DIRECTIONAL_H_
#define _DIRECTIONAL_H_
#include "Light.h"
class Directional :public Light
{
public:
	Directional();
	Directional(const Directional& diretional);
	virtual ~Directional();

	Light* Clone() const override;
	Directional& operator=(const Directional& rhs);

	void ScaleRadiance(const float b);

	void SetColor(const float c);
	void SetColor(const float r, const float g, const float b);
	void SetColor(const RGBColor& c);

	void SetDirection(const Vector3D d);
	void SetDirection(const float x, const float y, const float z);

	virtual Vector3D GetDirection(ShadeRec& s);

	//负责返回ls*color的值
	virtual RGBColor L(ShadeRec& s);

	virtual bool IsInShadow(const Ray& ray, ShadeRec& sr)const override;

	virtual bool CastShadow() const;
private:
	Vector3D dir;

	float ls;		//光照颜色系数，对应于光照所使用的发射材质
	RGBColor color; //光照颜色
};

inline void Directional::ScaleRadiance(const float b)
{
	ls = b;
}
inline void Directional::SetColor(const float c)
{
	color.r = c; color.g = c; color.b = c;
}
inline void Directional::SetColor(const float r, const float g, const float b)
{
	color.r = r; color.g = g; color.b = b;
}
inline void Directional::SetColor(const RGBColor& c)
{
	color = c;
}
inline void Directional::SetDirection(const Vector3D d)
{
	dir = d;
	dir.normalize();
}
inline void Directional::SetDirection(const float x, const float y, const float z)
{
	dir.x = x; dir.y = y; dir.z = z;
	dir.normalize();
}

inline bool Directional::CastShadow() const
{
	return true;
}
#endif//_DIRECTIONAL_H_