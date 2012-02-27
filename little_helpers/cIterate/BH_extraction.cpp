#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
using namespace std;

#include "cReadDat.hpp"

int main(int argc, char** argv)
{
	if(argc<=2)
	{
		cout<<"usage: "<<argv[0]<<" file_unten.dat file_oben.dat"<<endl;
		return 0;
	}
	
	cInterate oKurve;
	if(! oKurve.bReadFile(argv[1])) return 0;
	oKurve.vPunkteHomogenisieren();
	oKurve.vBackupWerte();
	
	if(! oKurve.bReadFile(argv[2])) return 0;
	oKurve.vPunkteHomogenisieren();
	
	oKurve.vIntegriere();
	
	return 0;
}

/*int main(int argc, char** argv)
{
	if(argc<=1)
	{
		cout<<"usage: "<<argv[0]<<" file.dat"<<endl;
		return 0;
	}
	
	cInterate oKurve;
	if(! oKurve.bReadFile(argv[1])) return 0;
	
	// cout<<"Homogenisiere..."<<endl;
	oKurve.vPunkteHomogenisieren();
	oKurve.vFeatureExtraction2();
	
	char* sBuffer=new char[strlen(argv[1])+9];
	strcpy(sBuffer, argv[1]);
	strcat(sBuffer, ".hom.dat");
	oKurve.bWriteFile(sBuffer);
	delete [] sBuffer;
	
	return 0;
}
*/
