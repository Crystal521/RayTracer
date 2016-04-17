#ifndef _GLOSSY_SPECULAR_H_
#define _GLOSSY_SPECULAR_H_

#include <math.h>

#include "RGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"

#include "BRDF.h"

class Sampler;
class GlossySpecular : public BRDF
{
public:
	GlossySpecular();
	GlossySpecular(const GlossySpecular &object);
	//GlossySpecular(Sampler* pSampler);
	~GlossySpecular();


	virtual GlossySpecular* Clone() const;
	//返回GlossySpecular
	virtual RGBColor F(const ShadeRec& sr, const Vector3D &wo, const Vector3D & wi) const override;
	virtual RGBColor SamplerF(const ShadeRec& sr, const Vector3D &wo, Vector3D & wi, float &pdf) const override;
	virtual RGBColor Rho(const ShadeRec& sr, const Vector3D &wo) const override;

	void SetKs(const float ks);
	void SetExp(const double exp);
	void SetCs(const RGBColor& c);
	void SetCs(const float r, const float g, const float b);
	void SetCs(const float c);
	//void SetNormal(const Normal& n);

	GlossySpecular& operator = (const GlossySpecular& rhs);

private:
	double exp;//描述材质的粗糙程度
	float ks;
	RGBColor cs;
	Sampler* pSampler;
};


inline void GlossySpecular::SetKs(const float k)
{
	ks = k;
}

inline void GlossySpecular::SetExp(const double e)
{
	exp = e;
}

inline void GlossySpecular::SetCs(const RGBColor & c)
{
	cs = c;
}

inline void GlossySpecular::SetCs(const float r, const float g, const float b)
{
	cs.r = r; cs.g = g; cs.b = b;
}

inline void GlossySpecular::SetCs(const float c)
{
	cs.r = c; cs.g = c; cs.b = c;
}
#endif//_GLOSSY_SPECULAR_H_