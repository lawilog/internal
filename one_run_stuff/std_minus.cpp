#include <iostream>
#include <vector>
#include <algorithm>    // std::transform
#include <functional>   // std::minus, std::plus
#include <numeric>      // std::accumulate
#include "../common/vout.hpp"
using namespace std;
using namespace LW;

int main()
{
	vector<int> a = {10, 20, 30, 40};
	vector<int> b = { 1,  2,  3,  4};
	vector<int> c(a.size());
	transform(a.begin(), a.end(), b.begin(), c.begin(), minus<int>());
	cout<< c <<endl;
	
	int sum = accumulate(c.begin(), c.end(), 0); // , plus<int>()
	cout<< sum << endl;
	return 0;
}
