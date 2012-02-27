#include <iostream>
using namespace std;

int main()
{
	int iN=6;
	float* iX=new float[iN];
	float* iY=new float[iN];
	iX[0]=1.0; iX[1]=4.0; iX[2]=2.0; iX[3]=3.0; iX[4]=2.0; iX[5]=1.0;
	iY[0]=1.0; iY[1]=1.0; iY[2]=2.0; iY[3]=3.0; iY[4]=4.0; iY[5]=3.0;
	
	float iA=0.0;
	for(int i=0; i<iN; ++i)
	{
		iA+=iY[i]*(iX[(i-1+iN)%iN]-iX[(i+1+iN)%iN]);
	}
	iA/=2.0;
	cout<<"A = "<<iA<<endl;
	
	iA=0.0;
	int iSkip=0;
	while(CEIL(iN/(iSkip+1))>=3)
	{
		for(int i=0; i<iN-2; i+=2)
		{
			iA=(iX[i+1]-iX[i])*(iY[i+2]-iY[i+1])-(iX[i+2]-iX[i+1])*(iY[i+1]-iY[i]);
		}
		++iSkip;
	}
	iA/=2.0;
	cout<<"A = "<<iA<<endl;
	
	delete [] iY;
	delete [] iX;
	return 0;
}
