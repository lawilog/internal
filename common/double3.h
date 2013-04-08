#ifndef _LW_DOUBLE3_
#define _LW_DOUBLE3_

struct double3
{
	union
	{
		struct {double x, y, z;}; 
		double r[3];
	};
	
	double3() {}
	
	double3(const double (&v)[3])
	{
		r[0] = v[0];
		r[1] = v[1];
		r[2] = v[2];
	}
	
	double3(const double& _x, const double& _y, const double& _z)
	{
		r[0] = _x;
		r[1] = _y;
		r[2] = _z;
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
