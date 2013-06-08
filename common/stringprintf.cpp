#include <iostream>
#include <fstream>
#include <string>
#include "printf++.hpp"
using namespace std;
using namespace LW;

void wout() {}

template<typename T, typename... Args>
void wout(T value, Args... args)
{
	std::cout<< value;
	wout(args...);
}

void woutn()
{
	std::cout<<std::endl;
}

template<typename T, typename... Args>
void woutn(T value, Args... args)
{
	std::cout<< value;
	woutn(args...);
}

int main()
{
	string test = strprintf("%5.2f\n", 1.234567);
	cout<< test <<endl;
	
	ofstream fp("foobar.txt");
	fprintf(fp, "%5.2f\n", 1.234567);
	fp.close();
	
	wout("Hello ", 42, " world", '!', '\n');
	woutn("another", " test: ", 1.234567);
	
	return 0;
}
