#include <iostream>
#include <vector>
#include "rand_choose.hpp"
#include "vout.hpp"
using namespace std;
using namespace LW;

int main()
{
	const unsigned N = 600;
	
	vector<vector<double>> pp = {
		{1.0/2.0, 1.0/3.0, 1.0/6.0},
		{0, 1.0/2.0, 1.0/3.0, 1.0/6.0},
		{1.0/2.0, 0, 1.0/3.0, 1.0/6.0},
		{1.0/2.0, 1.0/3.0, 0, 1.0/6.0},
		{1.0/2.0, 1.0/3.0, 1.0/6.0, 0},
		{0, 0, 1.0/2.0, 1.0/3.0, 1.0/6.0},
		{1.0/2.0, 0, 0, 1.0/3.0, 1.0/6.0},
		{1.0/2.0, 1.0/3.0, 0, 0, 1.0/6.0},
		{1.0/2.0, 1.0/3.0, 1.0/6.0, 0, 0},
		{0, 0, 1.0/2.0, 0, 0, 1.0/3.0, 0, 0, 1.0/6.0, 0, 0}
	};
	
	for(vector<double>& p: pp)
	{
		vector<unsigned> n(p.size());
		for(unsigned i = 0; i < N; ++i) ++n.at(rand_choose(p));
		cout<< p <<"\n"<< n <<"\n"<<endl;
	}
	
	try
	{
		unsigned i = rand_choose({});
	}
	catch(const out_of_range& e)
	{
		cout<<"As expected, an error occured: "<< e.what() <<endl;
	}
	catch(...) {throw;}
	
	return 0;
}