#include <iostream>
#include <vector>
using namespace std;

vector<int> global_vec {10, 20, 30, 40};

template <typename T> T gimme() { return global_vec; }

template <typename T>
void incr_first()
{
	auto&& vec = gimme<T>();
	cout << "A "<< ++vec[0] << endl;
}

int main()
{
	incr_first< vector<int>  >();
	cout << "B " << global_vec[0] << endl;
	incr_first< vector<int>& >();
	cout << "b " << global_vec[0] << endl;
	
	
	vector< vector<int> > vv = { {50, 55}, {60, 66}, {70, 77} };
	for(auto v: vv) cout<< "C "<< v[0] <<endl;
	
	for(auto v: vv) ++v[0];
	for(auto v: vv) cout<< "D "<< v[0] <<endl;
	
	for(auto& v: vv) ++v[0];
	for(auto v: vv) cout<< "E "<< v[0] <<endl;
	
	for(auto&& v: vv) ++v[0];
	for(auto v: vv) cout<< "F "<< v[0] <<endl;
	
	
	vector<bool> w(32);
	cout << "G "; for(auto b: w) cout<<b; cout<<endl;
	
	for(auto b: w) b = !b;
	cout << "H "; for(auto b: w) cout<<b; cout<<endl;
	
	// fails to compile, because vector<bool>::begin() cannot bind to lvalue reference (?)
	// for(auto& b: w) b = !b;
	// cout << "I "; for(auto b: w) cout<<b; cout<<endl;
	
	for(auto&& b: w) b = !b;
	cout << "J "; for(auto b: w) cout<<b; cout<<endl;
	
	return 0;
}
