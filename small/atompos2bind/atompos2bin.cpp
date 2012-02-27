#include <iostream>
using namespace std;

struct double3
{
	double x;
	double y;
	double z;
};

struct atomNode
{
	bool done;
	unsigned id;
	unsigned parrent_id;
	double distance;
};

int main()
{
	double3 atoms[] = {
		{1,3,0}, {3,1,0}, {6,1,0}, {8,3,0}, {6,5,0}, {3,5,0},
		{0,4,0}, {3,0,0}, {7,1,0}, {9,3,0}, {7,6,0}, {4,6,0}
	};
	
	const unsigned n = sizeof(atoms)/sizeof(double3);
	
	atomNode
	
	double* w_mem = new double[n * n];
	double** w = new double*[n];
	for(unsigned i = 0; i < n; ++i)
		w[i] = & w_mem[i * n];
	
	for(unsigned i = 0; i < n; ++i)
	{
		for(unsigned j = 0; j < n; ++j)
		{
			double dx = atoms[i].x - atoms[j].x;
			double dy = atoms[i].y - atoms[j].y;
			double dz = atoms[i].z - atoms[j].z;
			w[i][j] = dx*dx + dy*dy + dz*dz;
		}
	}
	
	
	
	delete [] w;
	
	return 0;
}
