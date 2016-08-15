#ifndef _LW_RAND_CHOOSE
#define _LW_RAND_CHOOSE

#include <vector>
#include "RandDistrib.hpp"

namespace LW {

// input: vector p and optionally sum
//        elements of p must be >= 0
//        at least one element of p should be > 0 (otherwise: choice is not random)
//        if sum is omitted, it is assumed that sum(p) == 1
//        if sum is non-positive (e.g. 0 or -1), sum is calculated from vector
// output: index i is returned with probability p[i]/sum(p), 0 <= i < p.size()
unsigned rand_choose(const std::vector<double>& p, double sum=1.0)
{
	if(p.empty()) throw std::out_of_range("rand_choose: cannot choose from empty vector");
	if(sum <= 0)
	{
		sum = 0;
		for(auto& x: p)
			sum += x;
	}
	
	static RandDistrib<double,std::uniform_real_distribution> rand(0, 1);
	const double r = sum * rand();
	double cumsum = p[0]; // valid, since p is not empty
	unsigned choice = 0;
	while(choice < p.size()-1 && r > cumsum) cumsum += p[++choice];
	return choice;
}

/* equivalent Matlab code:
function c = rand_choose(this, p) % given vector p with sum(p)==1, return i with probability p(i)
	c = find(rand() <= cumsum(p/sum(p)), 1, 'first');
end
*/

}

#endif // _LW_RAND_CHOOSE
