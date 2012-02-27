#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
using namespace std;

#include "cIterate.hpp"

float f(float x, float* p)
{
	return (p[0]*p[1]*2/M_2_SQRTPI*exp(- (p[1]*(x-p[2]))*(p[1]*(x-p[2]))) - (x-p[2]) + p[3]);
}

int main(int argc, char** argv)
{
	if(argc<=1)
	{
		cout<<"usage: "<<argv[0]<<" file.dat"<<endl;
		return 0;
	}
	
	const unsigned short iParamCount=4;
	cInterate oKurve(iParamCount, f);
	
	if(! oKurve.bReadFile(argv[1])) return 0;
	
	stParam param[iParamCount] =
	{
		{-10000, 0, 200},
		{0, 0.1, 0.005},
		{300, 350, 5},
		{350, 400, 5}
	};
	float fParamMin[iParamCount];
	oKurve.vStartIteration(param, fParamMin, 2);
	for(unsigned short i=0; i<iParamCount; ++i) cout<<"\np"<<i<<" = "<<fParamMin[i];
	cout<<endl;
	return 0;
}
