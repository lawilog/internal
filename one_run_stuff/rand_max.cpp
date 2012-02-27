#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));
	const unsigned short iMaxTemp=1000;
	const unsigned iJahreMax=100;
	const unsigned iN=1000;
	unsigned short iCount[iN];
	unsigned iMittelHotest=0;
	for(unsigned i=0; i<iN; ++i)
	{
		int iHotestTemp=-1;
		unsigned iHotestCount=0;
		for(unsigned short j=0; j<iJahreMax; ++j)
		{
			unsigned short iTemp=rand()%iMaxTemp;
			if(iTemp > iHotestTemp)
			{
				++iHotestCount;
				iHotestTemp=iTemp;
			}
		}
		iMittelHotest+=iCount[i]=iHotestCount;
	}
	//cout<<iHotestCount<<" of "<<iGes<<" "<<(100*iHotestCount/((float)iGes))<<"%"<<endl;
	cout<<"im Mittel waren unter "<<iJahreMax<<" Jahren "<<iMittelHotest/((float)iN)<<" Jahre die waermsten."<<endl;
	double fSum=0;
	for(short i=1; i<=100; ++i) fSum+=1/(float)i;
	cout<<"fSum = "<<fSum<<endl;
	return 0;
}
