#ifndef _LW_SUM_HPP
#define _LW_SUM_HPP

#include <vector>

namespace LW {

// sums all elements
// e.g. vector<int> v; int s = sum(v.begin(), v.end());
//      float a[8]; float x = sum(a, a+8);
// end is one after last element
template<class forward_iterator>
inline auto sum(const forward_iterator begin, const forward_iterator end)
-> typename std::remove_reference<decltype(*begin)>::type
{
	typename std::remove_reference<decltype(*begin)>::type s = 0;
	for(forward_iterator p = begin; p != end; ++p) s += *p;
	return s;
}

template<class T>
inline T sum(const std::vector<T>& v)
{
	return sum(v.begin(), v.end());
}

// note: after writing this I found:
// #include <numeric>
// sum = std::accumulate(v.begin(), v.end(), 0);

}

#endif // _LW_SUM_HPP
