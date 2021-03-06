#ifndef _LW_POWER_HPP
#define _LW_POWER_HPP

#include <type_traits>

// provides function power(x, N), where N is known at compile time, but x is not

// HRR. This is not working as wanted. with -O2, gcc 5.2.0 is not able to transform e.g. y = power<12>(x) into something like temp1=x*x*x; temp2=temp1*temp1; y = b*b;

namespace LW {
	
template<int N, class T, bool positive, bool even> struct power_;

template<int N, class T, bool positive>
struct power_<N, T, positive, true>
{
	static inline T of(const T& x)
	{
		static const T y = power_<N/2, T, (N/2>0), ((N/2)%2==0)>::of(x);
		return y * y;
	}
};

template<int N, class T>
struct power_<N, T, true, false>
{
	static inline T of(const T& x)
	{
		static const T y = power_<N/2, T, (N/2>0), ((N/2)%2==0)>::of(x);
		return x * (y * y);
	}
};

template<int N, class T>
struct power_<N, T, false, false>
{
	static inline T of(const T& x)
	{
		static const T y = power_<N/2, T, (N/2>0), ((N/2)%2==0)>::of(x);
		return (y * y) / x;
	}
};

template<class T>
struct power_<0, T, false, true>
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
	return power_<N,T,(N/2>0),((N/2)%2==0)>::of(x);
}


}

#endif // _LW_POWER_HPP
