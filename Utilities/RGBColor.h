#ifndef _RGBCOLOR_H_
#define _RGBCOLOR_H_

class RGBColor
{
public:
	RGBColor();
	RGBColor(float c);
	RGBColor(float _r, float _g, float _b);
	RGBColor(const RGBColor & color);
	~RGBColor();

	RGBColor & operator =(const RGBColor &rhs);

	RGBColor  operator +(const RGBColor &color) const;
	RGBColor & operator +=(const RGBColor &color);

	RGBColor  operator *(const float a) const;
	RGBColor operator* (const RGBColor &color) const;
	RGBColor & operator *=(const float a);

	RGBColor  operator /(const float a) const;
	RGBColor & operator /=(const float a);

	bool operator == (const RGBColor &color) const;

	RGBColor powc(float p) const;
	float average() const;
public:
	float	r, g, b;
};



inline  RGBColor RGBColor::operator+(const RGBColor & color) const
{
	return RGBColor(color.r + r, color.g + g, color.b + b);
}

inline RGBColor & RGBColor::operator+=(const RGBColor & color)
{
	r += color.r;
	g += color.g;
	b += color.b;

	return (*this);
}

inline RGBColor RGBColor::operator*(const float a) const
{
	return RGBColor(r*a, g*a, b*a);
}

inline RGBColor RGBColor::operator*(const RGBColor & color) const
{
	return RGBColor(r*color.r, g*color.g, color.b*b);
}


//内联非成员函数
//左乘标量
inline RGBColor operator* (const float a, const RGBColor& c)
{
	return (RGBColor(a * c.r, a * c.g, a * c.b));
}

inline RGBColor & RGBColor::operator*=(const float a)
{
	r *= a;
	g *= a;
	b *= a;
	return (*this);
}

inline RGBColor RGBColor::operator/(const float a) const
{
	return RGBColor(r / a, g / a, b / a);
}

inline RGBColor & RGBColor::operator/=(const float a)
{
	r /= a;
	g /= a;
	b /= a;

	return (*this);
}

inline bool RGBColor::operator==(const RGBColor & color) const
{
	return (r == color.r&&g == color.g&&b == color.b);
}


inline float RGBColor::average() const
{
	return (0.333333333333f * (r + g + b));
}

#endif
