#include "Pinhole.h"
#include "World.h"
#include "ViewPlane.h"
#include "Ray.h"


Pinhole::Pinhole()
	:Camera(),
	d(500.0f),
	zoom(1.0f)
{
}

Pinhole::Pinhole(const Pinhole& ph)
	:Camera(ph),
	d(ph.d),
	zoom(ph.zoom)
{
}

Pinhole::~Pinhole()
{
}

Camera* Pinhole::Clone() const
{
	return new Pinhole(*this);
}

Vector3D Pinhole::GetDirection(const Point2D& p)const 
{
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();

	return dir;
}

void Pinhole::RenderScene(const World& w)
{
	RGBColor L(0);
	ViewPlane vp(w.vp);
	Ray ray;
	int depth = 0;
	Point2D pp;
	int n = (int)sqrt((float)vp.numSamples);

	vp.pixelSize /= zoom;
	ray.o = eye;

	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++)
		{
			L = black;
			//多重采样
			for (int p = 0; p < n; p++)
			{// up pixel
				pp.y = vp.pixelSize * (r - 0.5 * vp.vres + (p + 0.5) / n);
				for (int q = 0; q < n; q++)
				{	// across pixel
					pp.x = vp.pixelSize * (c - 0.5 * vp.hres + (q + 0.5) / n);
					
					ray.d = GetDirection(pp);
					L += w.pTracer->TraceRay(ray, depth);
				}
			}
			L /= vp.numSamples;
			L *= exposureTime;
			w.DisplayPixel(r, c, L);
		}
	}
}

Pinhole& Pinhole::operator=(const Pinhole& rhs)
{
	if (this == &rhs)
		return (*this);

	Camera::operator= (rhs);

	d = rhs.d;
	zoom = rhs.zoom;

	return (*this);
}