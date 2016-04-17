#ifndef _VIEWPLANE_H_
#define _VIEWPLANE_H_

class ViewPlane
{
public:
	int hres;		//水平分辨率
	int vres;		//垂直分辨率
	
	int numSamples;//每个像素点的样本数（用于多重采样抗锯齿技术）

	float pixelSize;//像素大小
	float gamma;	//伽玛校正因子，默认为1.0，数值大小跟平台有关
	float invGamma;//伽玛校正因子的倒数，默认为1.0

	bool showOutOfGamut;//超出显示色彩的色域范围

	int maxDepth;//光线递归跟踪的最大深度限制
public:
	ViewPlane();
	ViewPlane(const ViewPlane &vp);
	ViewPlane& operator= (const ViewPlane &rhs);
	~ViewPlane();

	void SetHres(const int h);
	void SetVres(const int v);
	void SetSamples(const int n);
	void SetPixelSize(const float s);
	void SetGamma(const float g);
	void SetGamutDisplay(const bool show);
	void SetMaxDepth(const int depth);
};

inline void ViewPlane::SetGamutDisplay(const bool show)
{
	showOutOfGamut = show;
}


inline void ViewPlane::SetMaxDepth(const int depth)
{
	maxDepth = depth;
}


inline void ViewPlane::SetHres(const int h)
{
	hres = h;
}

inline void ViewPlane::SetVres(const int v)
{
	vres = v;
}

inline void ViewPlane::SetSamples(const int n)
{
	numSamples = n;
}

inline void ViewPlane::SetPixelSize(const float s)
{
	pixelSize = s;
}

inline void ViewPlane::SetGamma(const float g)
{
	gamma = g;
	invGamma = 1.0 / gamma;
}
#endif//_VIEWPLANE_H_
