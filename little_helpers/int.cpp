#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
	if(argc<=1) {cout<<"[info] usage: "<<argv[0]<<" input_file"<<endl; return 0;}
	float f[7]; for(short i=0; i<7; ++i) f[i]=0.0; // 5 letzte Funktionswerte + 2 davor
	short i=0; // f-index
	long t=0; // Zeitschritt
	float fIntegral=0.0;
	bool bInitial=true;
	float fInitialF=0.0, fFinalF=0.0;
	char* sBuffer=new char[32];
	ifstream hDatei(argv[1]);
	if(! hDatei) {cout<<"[error] Cannot open file "<<argv[1]<<" for reading"<<endl; return -1;}
	while(hDatei.good())
	{
		hDatei.getline(sBuffer, 32);
		// Tab suchen
		short j=0; while(j<31 && sBuffer[j]!='\t') ++j;
		if(j==31) {cout<<"[warning] Line with no delimiter found. Aborting."<<endl; break;}
		// ggf , durch . ersetzten und nach float konvertieren
		short k=j; while(k<31 && sBuffer[k]!=',') ++k;
		if(j<31) sBuffer[k]='.';
		f[i]=atof(sBuffer+j+1);
		//cout<< t <<'\t'<< f[i] <<endl;
		++t;
		if(++i==5)
		{
			// verarbeite f[0..4]
			if(bInitial)
			{
				bInitial=false;
				fInitialF=f[0];
				fIntegral+=2/45.0*(7*f[0]+32*f[1]+12*f[2]+32*f[3]+7*f[4]);
				fIntegral+=1/3.0*(f[0]+4*f[1]+f[2]);
				
			}
			else
			{
				fIntegral+=2/45.0*(7*f[0]+32*f[1]+12*f[2]+32*f[3]+7*f[4]);
				fIntegral+=2/45.0*(7*f[5]+32*f[6]+12*f[0]+32*f[1]+7*f[2]);
			}
			f[0]=f[4]; f[5]=f[2]; f[6]=f[3]; // last point gets first [0] and save 2 points before
			i=1;
			//cout<<"Integral = "<<fIntegral<<endl;
		}
	}
	hDatei.close();
	delete [] sBuffer;
	switch(i)
	{	// addiere ende dazu
		case 1: fFinalF=f[0]; fIntegral+=1/3.0*(f[5]+4*f[6]+f[0]); break;
		case 2: fFinalF=f[1]; fIntegral+=3/8.0*(f[5]+3*f[6]+3*f[0]+f[1])+1/2.0*(f[0]+f[1]); break;
		case 3: fFinalF=f[2]; fIntegral+=2/45.0*(7*f[5]+32*f[6]+12*f[0]+32*f[1]+7*f[2])+1/3.0*(f[0]+4*f[1]+f[2]); break;
		case 4: fFinalF=f[3]; fIntegral+=5/288.0*(19*f[5]+75*f[6]+50*f[0]+50*f[1]+75*f[2]+19*f[3])+3/8.0*(f[0]+3*f[1]+3*f[2]+f[3]); break;
		default: cout<<"[error] Too few points found."<<endl; break;
	}
	--t;
	// stepsize 0.5 * 1/2 (dobble integration)
	cout<<"Integral = "<<(fIntegral/4.0)<<endl;
	//cout<<"fIntegral="<<fIntegral<<"\tt="<<t<<"\tfInitialF="<<fInitialF<<"\tfFinalF="<<fFinalF<<"\tt*(fInitialF+fFinalF)/2.0="<<(t*(fInitialF+fFinalF)/2.0)<<endl;
	cout<<"Integral minus Trapez = "<<((fIntegral-t*(fInitialF+fFinalF))/4.0)<<endl;
	return 0;
}
