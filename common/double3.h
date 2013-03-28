#ifndef _LW_DOUBLE3_
#define _LW_DOUBLE3_

struct double3
{
	double r[3];
	
	double3() {}
	
	double3(const double (&v)[3])
	{
		r[0] = v[0];
		r[1] = v[1];
		r[2] = v[2];
	}
	
	double3(const double& x, const double& y, const double& z)
	{
		r[0] = x;
		r[1] = y;
		r[2] = z;
	}
	
	double& operator[](unsigned n)
	{
		return r[n];
	}
	
	const double& operator[](unsigned n) const
	{
		return r[n];
	}
};

#endif // _LW_DOUBLE3_
