#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>
using namespace std;

struct Vektor
{
	double x;
	double y;
	double z;
};

/*
struct Ladung
{
	double q;
	Punkt p;
};
*/

double dBetrag(double x, double y, double z)
{
	return sqrt(x*x+y*y+z*z);
}

int main()
{
	srand(time(NULL));
	long iBalance[3]={0,0,0};
	vector <Vektor> vPunkte;
	for(unsigned i=0; i<1000000; ++i)
	{
		Vektor vRichtung=
		{ 
			2*(rand()/((double)RAND_MAX))-1,
			2*(rand()/((double)RAND_MAX))-1,
			2*(rand()/((double)RAND_MAX))-1
		};
		double dLaenge=dBetrag(vRichtung.x, vRichtung.y, vRichtung.z);
		if(0.0<dLaenge && dLaenge<=1.0)
		{
			vRichtung.x/=dLaenge; vRichtung.y/=dLaenge; vRichtung.z/=dLaenge;
			vPunkte.push_back(vRichtung);
			//
			iBalance[0]+=(vRichtung.x>0)?1:-1;
			iBalance[1]+=(vRichtung.y>0)?1:-1;
			iBalance[2]+=(vRichtung.z>0)?1:-1;
			//
		}
	}
	unsigned iCount=vPunkte.size();
	cout<<"Habe "<<iCount<<" Punkte erzeugt (Balance "<<iBalance[0]<<", "<<iBalance[1]<<", "<<iBalance[2]<<")."<<endl;
	ofstream hData("hohlkugel.txt");
	for(double dOrt=0.0; dOrt<=5.0; dOrt+=0.01)
	{
		unsigned iDropped=0;
		Vektor vKraft={0.0, 0.0, 0.0};
		const Vektor vR={dOrt, dOrt, dOrt};
		vector <Vektor>::iterator i=vPunkte.begin();
		while(i != vPunkte.end())
		{
			const Vektor vr={1*((i->x)-vR.x), 1*((i->y)-vR.y), 1*((i->y)-vR.y)};
			double dFak=dBetrag(vr.x, vr.y, vr.z); dFak*=dFak*dFak; // ^3
			if(dFak<=0.001) {++i; ++iDropped; continue;}
			vKraft.x+=(vr.x/dFak);
			vKraft.y+=(vr.y/dFak);
			vKraft.z+=(vr.z/dFak);
			++i;
		}
		hData<<dBetrag(vR.x, vR.y, vR.z)<<'\t'<<(dBetrag(vKraft.x, vKraft.y, vKraft.z)/((double)iCount))<<'\t'<<vKraft.x<<'\t'<<vKraft.y<<'\t'<<vKraft.z<<'\t'<<iDropped<<'\n';
	}
	hData.close();
	return 0;
}
