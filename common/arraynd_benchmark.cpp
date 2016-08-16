#include <iostream>
#include "arraynd.hpp"
using namespace std;
using namespace LW;

unsigned mypow(unsigned base, unsigned exp)
{
	if(exp == 0) return 1;
	else if(exp == 1) return base;
	else return base * mypow(base, exp-1);
}

int main(int argc, char** argv)
{
	if(argc < 8)
	{
		cout<<"usage: "<< argv[0] <<" mode  mx my mz  ci cj ck"<<endl;
		return 1;
	}
	const int mode = atoi(argv[1]);
	const int mx = atoi(argv[2]);
	const int my = atoi(argv[3]);
	const int mz = atoi(argv[4]);
	const int ci = atoi(argv[5]);
	const int cj = atoi(argv[6]);
	const int ck = atoi(argv[7]);
	const unsigned px = 29, py = 23, pz = 19;
	const unsigned Nx = mypow(px, mx), Ny = mypow(py, my), Nz = mypow(pz, mz);
	cout<<"array dimensions: "<< Nx <<" "<< Ny <<" "<< Nz <<endl;
	if(mode == 1)
	{
		cout<<"mode arraynd<int,3>"<<endl;
		array3d<int> a({Nx, Ny, Nz});
		for(unsigned i = 0, x = 0; i < Nx; ++i, x=(x+15)%Nx)
			for(unsigned j = 0, y = 0; j < Ny; ++j, y=(y+15)%Ny)
				for(unsigned k = 0, z = 0; k < Nz; ++k, z=(z+15)%Nz)
					a({x, y, z}) += i + j + k;
		
		cout<<"a("<< ci <<","<< cj <<","<< ck <<") = "<< a({ci, cj, ck}) <<endl;
	}
	else
	{
		cout<<"mode vector<vector<vector<int>>>"<<endl;
		vector<vector<vector<int>>> a(Nx);
		for(unsigned i = 0; i < Nx; ++i)
		{
			a[i].resize(Ny);
			for(unsigned j = 0; j < Ny; ++j)
				a[i][j].resize(Nz);
		}
		for(unsigned i = 0, x = 0; i < Nx; ++i, x=(x+15)%Nx)
			for(unsigned j = 0, y = 0; j < Ny; ++j, y=(y+15)%Ny)
				for(unsigned k = 0, z = 0; k < Nz; ++k, z=(z+15)%Nz)
					a[x][y][z] += i + j + k;
		
		cout<<"a["<< ci <<"]["<< cj <<"]["<< ck <<"] = "<< a[ci][cj][ck] <<endl;
	}
	
	return 0;
}
