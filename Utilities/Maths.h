#ifndef __MATHS__
#define __MATHS__

inline double max(double x0, double x1);

inline double max(double x0, double x1)
{
	return((x0 > x1) ? x0 : x1);
}

inline double min(double x0, double x1);

inline double min(double x0, double x1)
{
	return((x0 < x1) ? x0 : x1);
}


inline double clamp(const double x, const double min, const double max) 
{
	return (x < min ? min : (x > max ? max : x));
}
#endif
