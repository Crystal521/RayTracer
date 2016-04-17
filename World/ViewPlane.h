#ifndef _VIEWPLANE_H_
#define _VIEWPLANE_H_

class ViewPlane
{
public:
	int hres;		//ˮƽ�ֱ���
	int vres;		//��ֱ�ֱ���
	
	int numSamples;//ÿ�����ص�������������ڶ��ز�������ݼ�����

	float pixelSize;//���ش�С
	float gamma;	//٤��У�����ӣ�Ĭ��Ϊ1.0����ֵ��С��ƽ̨�й�
	float invGamma;//٤��У�����ӵĵ�����Ĭ��Ϊ1.0

	bool showOutOfGamut;//������ʾɫ�ʵ�ɫ��Χ

	int maxDepth;//���ߵݹ���ٵ�����������
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
