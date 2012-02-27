#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	ofstream hDatei("rand.dat");
	if(!hDatei) {cerr<<"cannot open rand.dat"<<endl; return -1;}
	for(int i=0; i<2000; ++i)
	{
		int r=rand()%1000;
		hDatei<<(r*100)<<'\t'<<(4200*r)<<endl;
	}
	return 0;
}
