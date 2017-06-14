#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "rand_choose.hpp"
#include "vout.hpp"
using namespace std;
using namespace LW;

int main()
{
	const unsigned N = 600;
	
	const vector<vector<double>> pp = {
		{1.0/2.0, 1.0/3.0, 1.0/6.0},
		{0, 1.0/2.0, 1.0/3.0, 1.0/6.0},
		{1.0/2.0, 0, 1.0/3.0, 1.0/6.0},
		{1.0/2.0, 1.0/3.0, 0, 1.0/6.0},
		{1.0/2.0, 1.0/3.0, 1.0/6.0, 0},
		{0, 0, 1.0/2.0, 1.0/3.0, 1.0/6.0},
		{1.0/2.0, 0, 0, 1.0/3.0, 1.0/6.0},
		{1.0/2.0, 1.0/3.0, 0, 0, 1.0/6.0},
		{1.0/2.0, 1.0/3.0, 1.0/6.0, 0, 0},
		{0, 0, 1.0/2.0, 0, 0, 1.0/3.0, 0, 0, 1.0/6.0, 0, 0},
		
		{0, 0, 0},
		{0.4, 0.4, -0.1, 0.3},
		{-0.4, -0.2, 1.0, 0.3, 0.3}
	};
	
	for(const vector<double>& p: pp)
	{
		vector<unsigned> n(p.size());
		for(unsigned i = 0; i < N; ++i) ++n.at(rand_choose(p));
		cout<< p <<"\n"<< n <<"\n"<<endl;
	}
	
	const vector<vector<double>> qq = {
		{2, 2, 2},
		{4, 1, 1},
		{0, 6, 0}
	};
	
	for(const vector<double>& q: qq)
	{
		vector<unsigned> n(q.size());
		for(unsigned i = 0; i < N; ++i) ++n.at(rand_choose(q, 0));
		cout<< q <<"\n"<< n <<"\n"<<endl;
	}
	
	cout<<"different from run to tun: "<< rand_choose(vector<double>({1, 2, 3, 4, 5, 6}), -1) << endl;
	
	RandChooseSeeded rand_choose_seeded(1337);
	cout<<"the same every run: "<< rand_choose_seeded(vector<double>({1, 2, 3}), -1) <<endl;
	
	std::unordered_map<std::string,double> x;
	x.emplace("red",   0.7);
	x.emplace("green", 0.01);
	x.emplace("blue",  0.29);
	// x.emplace("zero",  0);
	
	cout<<"30 map choices:";
	for(int i = 0; i < 30; ++i)
		cout<<" "<< rand_choose_seeded(x)->first;
	
	cout<<endl;
	
	try
	{
		vector<int> v;
		cout<< rand_choose(v) <<endl;
	}
	catch(const out_of_range& e)
	{
		cout<<"As expected, an error occured: "<< e.what() <<endl;
	}
	catch(...) {throw;}
	
	return 0;
}