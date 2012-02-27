#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
using namespace std;

#include "cIterate.hpp"

float f(float x, float p)
{
	const float p0=;
	const float p2=;
	const float p3=;
	return (p0*p*2/M_2_SQRTPI*exp(- (p*(x-p2))*(p*(x-p2))) - (x-p2) + p3);
}

int main(int argc, char** argv)
{
	if(argc<=1)
	{
		cout<<"usage: "<<argv[0]<<" file.dat"<<endl;
		return 0;
	}
	
	cInterate oKurve(f);
	
	if(! oKurve.bReadFile(argv[1])) return 0;
	
	float fBounds[2];
	oKurve.vGetBounds(&fBounds);
	cout<<fBounds[0]<<"\t"<<fBounds[1]<<endl;

	return 0;
}
