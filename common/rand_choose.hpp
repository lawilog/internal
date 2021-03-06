#ifndef _LW_RAND_CHOOSE
#define _LW_RAND_CHOOSE

#include <vector>
#include <unordered_map>
#include "RandDistrib.hpp"
#include "sum.hpp"

namespace LW {

// input: vector p and optionally sum
//        elements of p must be >= 0
//        at least one element of p should be > 0 (otherwise: choice is not random)
//        if sum is omitted, it is assumed that sum(p) == 1
//        if sum is non-positive (e.g. 0 or -1), sum is calculated from vector
// output: index i is returned with probability p[i]/sum(p), 0 <= i < p.size()
template <class T> // thinking of T as std::vector<double> or std::array<double>
unsigned rand_choose(const T& p, double sum=1.0)
{
	if(p.empty())
		throw std::out_of_range("rand_choose: cannot choose from empty vector");
	
	if(sum <= 0)
		sum = LW::sum(p);
	
	static RandDistrib<double,std::uniform_real_distribution> rand(0, 1);
	const double r = sum * rand();
	double cumsum = p[0]; // valid, since p is not empty
	unsigned choice = 0;
	while(choice < p.size()-1 && r > cumsum) cumsum += p[++choice];
	return choice;
}

template <class T>
unsigned rand_choose_1337(const T& p, double sum=1.0)
{
	if(p.empty())
		throw std::out_of_range("rand_choose: cannot choose from empty vector");
	
	if(sum <= 0)
		sum = LW::sum(p);
	
	static std::default_random_engine generator(1337);
	static std::uniform_real_distribution<double> rand(0, 1);
	const double r = sum * rand(generator);
	double cumsum = p[0]; // valid, since p is not empty
	unsigned choice = 0;
	while(choice < p.size()-1 && r > cumsum) cumsum += p[++choice];
	return choice;
}

class RandChooseSeeded
{
	private:
		RandDistrib<double,std::uniform_real_distribution> rand;
	
	public:
		RandChooseSeeded(unsigned seed) : rand(0, 1) {rand.reseed(seed);}
		
		template<class T>
		unsigned operator() (const T& p, double sum=1.0)
		{
			if(p.empty())
				throw std::out_of_range("rand_choose: cannot choose from empty vector");
			
			if(sum <= 0)
				sum = LW::sum(p);
			
			const double r = sum * rand();
			double cumsum = p[0]; // valid, since p is not empty
			unsigned choice = 0;
			while(choice < p.size()-1 && r > cumsum) cumsum += p[++choice];
			return choice;
		}
		
		template<class key, class T>
		typename std::unordered_map<key,T>::const_iterator operator() (
			const std::unordered_map<key,T>& p, double sum=1.0)
		{
			if(p.empty())
				throw std::out_of_range("rand_choose: cannot choose from empty unordered_map");
			
			if(sum <= 0)
				sum = LW::sum(p);
			
			const double r = sum * rand();
			auto it = p.cbegin(), choice = it;
			double cumsum = (it++)->second; // valid, since p is not empty
			while(it != p.cend() && r > cumsum)
			{
				cumsum += it->second;
				choice = it++;
			}
			return choice;
		}
};

/* equivalent Matlab code:
function c = rand_choose(this, p) % given vector p with sum(p)==1, return i with probability p(i)
	c = find(rand() <= cumsum(p/sum(p)), 1, 'first');
end
*/

}

#endif // _LW_RAND_CHOOSE
