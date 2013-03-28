#include <iostream>
#include "parse.hpp"
using namespace std;
using namespace LW;

int main()
{
	const char foo[] = "-1.234";
	
	cout<< parse<string>(foo) <<endl;
	
	double bar = parse<double>(foo);
	cout<< bar <<endl;
	
	int i = parse<int>(foo);
	cout<< i <<endl;
	cout<< parse<short>(foo) <<endl;
	
	string s = "5.6";
	cout<< s <<endl;
	cout<< parse<float>(s) <<endl;
	cout<< parse<int>(s) <<endl;
	cout<< parse<unsigned>(s) <<endl;
	
	vector<string> vstr = {"1.2", "-3.2", " 77.0 ", "042"};
	vector<float> v = parse<float>(vstr);
	for(float& f : v)
		cout<< f <<endl;
	
	return 0;
}
	
