#ifndef _LW_POWER_HPP
#define _LW_POWER_HPP

#include <type_traits>

// provides function power(x, N), where N is known at compile time, but x is not

// HRR. This is not working as wanted. with -O2, gcc 5.2.0 is not able to transform e.g. y = power<12>(x) into something like temp1=x*x*x; temp2=temp1*temp1; y = b*b;

namespace LW {

template<int N, class T>
struct power_
{
	static inline T of(const T& x)
	{
		static const T y = power_<N/2, T>::of(x);
		static const T y2 = y * y;
		static constexpr bool even = (N % 2 == 0);
		static constexpr bool positive = (N > 0);
		return even ? y2 : (positive ? x * y2 : y2 / x);
	}
};

template<class T>
struct power_<0, T>
{
	static inline T of(const T& x)
	{
		return 1;
	}
};

template<int N, class T>
inline T power(const T& x)
{
	static_assert(std::is_floating_point<T>::value || N>=0, "Non-floating point base to negative exponent is forbidden, e.g. power<-2>(3) would be 1/3/3, which is 0 (because of integer division). Use something like power<-2>(3.0) or power<-2>((double)x) instead.");
	return power_<N,T>::of(x);
}


}

#endif // _LW_POWER_HPP
