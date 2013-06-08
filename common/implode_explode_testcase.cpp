#include <iostream>
#include <string>
#include <vector>
#include "implode_explode.h"
using namespace std;
using namespace LW;

int main()
{
	string L;
	vector<string> v;
	
	L = "12,34,56,78";
	v = explode(",", L);
	cout<<"\""<< implode("\" , \"", v) <<"\""<<endl;
	for(auto s: v) cout<< s <<endl;
	
	L = "A, B, C, D";
	v = explode(", ", L);
	cout<<"\""<< implode("\" , \"", v) <<"\""<<endl;
	for(auto s: v) cout<< s <<endl;
	
	L = "aaa bbb  ccc   ddd";
	v = explode(" ", L);
	cout<<"\""<< implode("\" , \"", v) <<"\""<<endl;
	for(auto s: v) cout<< s <<endl;
	
	L = "test";
	v = explode(" ", L);
	cout<<"\""<< implode("\" , \"", v) <<"\""<<endl;
	for(auto s: v) cout<< s <<endl;
	
	return 0;
}
