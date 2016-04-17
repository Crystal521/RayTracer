#ifndef _AMBIENT_H_
#define _AMBIENT_H_
#include "Light.h"
class Ambient:public Light
{
public:
	Ambient();
	Ambient(const Ambient& ambient);
	virtual ~Ambient();

	Light* Clone() const override;
	Ambient& operator=(const Ambient& rhs);

	void ScaleRadiance(const float b);

	void SetColor(const float c);
	void SetColor(const float r, const float g, const float b);
	void SetColor(const RGBColor& c);

	virtual Vector3D GetDirection(ShadeRec& s);

	virtual bool IsInShadow(const Ray& ray, ShadeRec& sr)const override;

	//���𷵻�ls*color��ֵ
	virtual RGBColor L(ShadeRec& s);

	virtual bool CastShadow() const;
private:
	float ls;		//������ɫϵ������Ӧ�ڹ�����ʹ�õķ������
	RGBColor color; //������ɫ
};

inline void Ambient::ScaleRadiance(const float b)
{
	ls = b;
}
inline void Ambient::SetColor(const float c)
{
	color.r = c; color.g = c; color.b = c;
}
inline void Ambient::SetColor(const float r, const float g, const float b)
{
	color.r = r; color.g = g; color.b = b;
}
inline void Ambient::SetColor(const RGBColor& c)
{
	color = c;
}

inline bool Ambient::CastShadow() const
{
	return false;
}
#endif//_AMBIENT_H_