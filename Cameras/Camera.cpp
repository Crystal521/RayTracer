#include "Camera.h"
#include "World.h"

Camera::Camera()
	:eye(0.0f,0.0f,500.0f),
	lookAt(0.0f), up(0.0f,1.0f,0.0f),
	u(1.0f,0.0f,0.0f),
	v(0.0f, 1.0f, 0.0f),
	w(0.0f, 0.0f, 1.0f),
	ra(0.0f), exposureTime(1.0f)
	
{
}

Camera::Camera(const Camera& cam)
	:eye(cam.eye),
	lookAt(cam.lookAt), up(cam.up),
	u(cam.u),
	v(cam.v),
	w(cam.w),
	ra(cam.ra), exposureTime(cam.exposureTime)
{
}

Camera::~Camera()
{
}

void Camera::ComputeUVW()
{
	//wΪ���������������Ϊ��Ҫ������������ϵ
	//�������������������ONB������������ʽ����
	w = eye - lookAt;
	w.normalize();
	u = up^w;
	u.normalize();
	v = w^u;

	//ע��һЩ��ֵ��������

	//�������ֱ����ʱ���ı䷽����ǰ��
	if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y > lookAt.y)
	{ 
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);
	}

	//�����ֱ����ʱ���ı䷽������
	if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y < lookAt.y) 
	{
		u = Vector3D(1, 0, 0);
		v = Vector3D(0, 0, 1);
		w = Vector3D(0, -1, 0);
	}
}

Camera& Camera::operator=(const Camera& rhs)
{
	if (this == &rhs)
		return (*this);

	eye = rhs.eye;
	lookAt = rhs.lookAt;
	ra = rhs.ra;
	up = rhs.up;
	u = rhs.u;
	v = rhs.v;
	w = rhs.w;
	exposureTime = rhs.exposureTime;

	return (*this);
}