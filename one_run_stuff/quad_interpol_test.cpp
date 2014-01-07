#include <iostream>
using namespace std;

typedef double xtype;
typedef double ytype;

ytype interpol_quadratic(const xtype& x0, const ytype& y0, const xtype& x1, const ytype& y1, const xtype& x2, const ytype& y2, const xtype& xi) // const
{
	// Lagrange interpolation
	return y0 * (xi-x1)*(xi-x2)/( (x0-x1)*(x0-x2) )  +  y1 * (xi-x0)*(xi-x2)/( (x1-x0)*(x1-x2) )  +  y2 * (xi-x0)*(xi-x1)/( (x2-x0)*(x2-x1) );
}

int main()
{
	for(double x=-1; x<=5; x+=0.5)
		cout<< x <<"\t"<< interpol_quadratic(0,4, 2,0, 4,4, x) <<endl;
	return 0;
}
