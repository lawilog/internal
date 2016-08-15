#ifndef _LW_SUM_HPP
#define _LW_SUM_HPP

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

}

#endif // _LW_SUM_HPP
