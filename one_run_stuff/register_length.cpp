#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	//unsigned n=256;
	// cout<<"enter 256"<<endl; cin>>n;
	float f = 1.0, g;
	unsigned nExp, nExpBits=1, nDig, nDigBits=1, nBits = 8*sizeof(float);
	cout<<"sizeof(float) = "<<sizeof(float)<<" Bytes  = "<<nBits<<" Bits"<<endl;
	while(true)
	{
		g = 2.0 * f;
		if(g < f || isinf(g)) break;
		++nExp;
		f = g;
	}
	cout<<"positiv float expontent can go up to "<<nExp<<endl;
	f = 1.0;
	while(true)
	{
		g = f / 2.0;
		if(g == 0.0) break;
		++nExp;
		f = g;
	}
	cout<<"float can hold "<<nExp<<" different exponents"<<endl;
	while(nExp > 1)
	{
		nExp /= 2;
		++nExpBits;
	}
	cout<<"this means the exponent has "<<nExpBits<<" bits large"<<endl;
	return 0;
}
