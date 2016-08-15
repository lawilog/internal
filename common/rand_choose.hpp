#ifndef _LW_RAND_CHOOSE
#define _LW_RAND_CHOOSE

#include <vector>
#include "RandDistrib.hpp"

namespace LW {

// input: vector p, where sum of all arguments is 1
// output: index i is returned with probability p[i], 0 <= i < p.size()
unsigned rand_choose(const std::vector<double>& p)
{
	if(p.empty()) throw std::out_of_range("rand_choose: cannot choose from empty vector");
	
	static RandDistrib<double,std::uniform_real_distribution> rand(0, 1);
	const double r = rand();
	double s = p[0]; // valid, since p is not empty
	unsigned c = 0;
	while(c < p.size()-1 && r > s) s += p[++c];
	return c;
}

/* equivalent Matlab code:
function c = rand_choose(this, p) % given vector p with sum(p)==1, return i with probability p(i)
	c = find(rand() <= cumsum(p), 1, 'first');
end
*/

}

#endif // _LW_RAND_CHOOSE
