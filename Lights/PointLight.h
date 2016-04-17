#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "Light.h"

class PointLight:public Light
{
public:

	PointLight();

	PointLight(const PointLight& pl);

	PointLight& operator= (const PointLight& rhs);

	Light* Clone() const override;

	virtual ~PointLight();

	virtual Vector3D GetDirection(ShadeRec& sr);

	virtual RGBColor L(ShadeRec& sr);
	virtual bool IsInShadow(const Ray& ray, ShadeRec& sr)const override;

	void ScaleRadiance(const float b);
	void LightAttenuation(const double a, const double b, const double c);

	void SetColor(const float c);
	void SetColor(const float r, const float g, const float b);
	void SetColor(const RGBColor& c);

	void SetLocation(const Point3D& loca);
	void SetLocation(const float x, const float y, const float z);

	virtual bool CastShadow() const;
private:
	float ls;
	RGBColor color;
	double a0, a1,a2;//Ë¥¼õÏµÊý
	Point3D location;
};

inline void PointLight::ScaleRadiance(const float b)
{
	ls = b;
}
inline void PointLight::LightAttenuation(const double a, const double b, const double c)
{
	a0 = a; a1 = b; a2 = c;
}

inline void PointLight::SetColor(const float c)
{
	color.r = c; color.g = c; color.b = c;
}
inline void PointLight::SetColor(const float r, const float g, const float b)
{
	color.r = r; color.g = g; color.b = b;
}
inline void PointLight::SetColor(const RGBColor& c)
{
	color = c;
}


inline void PointLight::SetLocation(const Point3D& loca)
{
	location = loca;
}
inline void PointLight::SetLocation(const float x, const float y, const float z)
{
	location.x = x; location.y = y; location.z = z;
}

inline bool PointLight::CastShadow() const
{
	return true;
}

#endif//_POINT_LIGHT_H_