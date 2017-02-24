#ifndef _LW_SUM_HPP
#define _LW_SUM_HPP

#include <vector>
#include <array>
#include <numeric>
#include <unordered_map>

namespace LW {

// sums all elements
// e.g. vector<int> v; int s = sum(v.begin(), v.end());
//      float a[8]; float x = sum(a, a+8);
// end is one after last element
template<class forward_iterator>
inline auto sum(const forward_iterator begin, const forward_iterator end)
-> typename std::remove_const<typename std::remove_reference<decltype(*begin)>::type>::type
{
	return std::accumulate(begin, end, typename std::remove_const<typename std::remove_reference<decltype(*begin)>::type>::type());
}

// e.g. vector<string> w = {"Hello", " ", "world"}; string s = sum(w);
template<class T>
inline T sum(const std::vector<T>& v)
{
	return std::accumulate(v.cbegin(), v.cend(), T());
}

template<class T, std::size_t N >
inline T sum(const std::array<T,N>& v)
{
	return std::accumulate(v.cbegin(), v.cend(), T());
}

template<typename T, std::size_t N>
inline T sum(const T (&v)[N])
{
    return std::accumulate(v, v+N, T());
}

template<typename key, typename T>
inline T sum(const std::unordered_map<key,T>& v)
{
  T s = T();
  for(auto it = v.cbegin(); it != v.cend(); ++it)
    s += it->second;
  
  return s;
}

}

#endif // _LW_SUM_HPP
