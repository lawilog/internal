#include <iostream>
#include <string>
#include <vector>
#include "implode_explode.h"
#include "parse.hpp"
using namespace std;
using namespace LW;

int main()
{
	string L = "12,34, 50,60, 78,9";
	// vector<int>
	auto v = parse<int>(explode(",", L));

	for(int& x: v) cout<< x <<endl;
	
	return 0;
}
