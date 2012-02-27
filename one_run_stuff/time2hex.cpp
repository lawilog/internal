#include <iostream>
using namespace std;

int main()
{
	const char sHex[]="0123456789ABCDEF";
	for(short h=0; h<24; ++h)
	{
		for(short m=0; m<60; m+=15)
		{
			short n=(h*60+m) *16*16/(24*60);
			cout<<'\t'<<h<<':'<<m<<'\t'<<sHex[n/16]<<sHex[n%16];
		}
		cout<<endl;
	}
	return 0;
}
