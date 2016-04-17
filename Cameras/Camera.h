#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Point3D.h"
#include "Vector3D.h"

class World;

//正交视图
class Camera
{
public:
	Camera();
	Camera(const Camera& cam);
	virtual ~Camera();

	virtual Camera* Clone() const = 0;
	virtual void RenderScene(const World& w) = 0;

	void SetEye(const Point3D& p);
	void SetEye(const float x, const float y, const float z);

	void SetLookAt(const Point3D& p);
	void SetLookAt(const float x, const float y, const float z);

	void SetUpVector(const Point3D& u);
	void SetUpVector(const float x, const float y, const float z);

	void SetRoll(const float ra);

	void SetExposureTime(const float exposure);

	void ComputeUVW();

protected:
	//视点、视向的位置、上方方位
	Point3D eye;
	Point3D lookAt;
	Vector3D up;

	float ra;
	float exposureTime;
	//相机坐标系的uvw正交坐标系
	Vector3D u, v, w;

	Camera& operator=(const Camera& cam);
private:

};


inline void Camera::SetEye(const Point3D& p)
{
	eye = p;
}
inline void Camera::SetEye(const float x, const float y, const float z)
{
	eye.x = x; eye.y = y; eye.z = z;
}

inline void Camera::SetLookAt(const Point3D& p)
{
	lookAt = p;
}

inline void Camera::SetLookAt(const float x, const float y, const float z)
{
	lookAt.x = x; lookAt.y = y; lookAt.z = z;
}
 
inline void Camera::SetUpVector(const Point3D& u)
{
	up = u;
}


inline void Camera::SetUpVector(const float x, const float y, const float z)
{
	up.x = x; up.y = y; up.z = z;
}

inline void Camera::SetRoll(const float r)
{
	ra = r;
}

inline void Camera::SetExposureTime(const float exposure)
{
	exposureTime = exposure;
}
#endif//_CAMERAS_H_