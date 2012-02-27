#include <iostream>
#include <cmath>
using namespace std;

struct Complex
{
	float Re;
	float Im;
};

float f(float x) {return (exp(-x*x));}

float 

int main()
{
	const unsigned int iXcount=1000;
	float* x=new float[iXcount];
	float* y=new float[iXcount];
	for(unsigned int i=0; i<iXcount; ++i)
	{
		x[i]=-10.0+i*20.0/iXcount;
		y[i]=f(x[i]);
		// cout<<x[i]<<'\t'<<y[i]<<endl;
	}
	// cout<<endl;
	
	delete [] x;
	delete [] y;
	return 0;
}
