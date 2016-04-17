#ifndef _PINHOLE_H_
#define _PINHOLE_H_

#include "Camera.h"
#include "Point2D.h"

//Õ∏ ” ”Õº
class Pinhole:public Camera
{
public:
	Pinhole();
	Pinhole(const Pinhole& ph);
	virtual ~Pinhole();

	virtual Camera* Clone() const override;

	Pinhole& operator=(const Pinhole& rhs);
	
	void SetViewDistance(const float vpd);
	
	void SetZoom(const float z);
	
	Vector3D GetDirection(const Point2D& p) const;
	
	void RenderScene(const World& w) override;
private:
	float d;
	float zoom;
};

inline void Pinhole::SetViewDistance(const float vpd)
{
	d = vpd;
}

inline void Pinhole::SetZoom(const float z)
{
	zoom = z;
}
#endif//_PINHOLE_H_