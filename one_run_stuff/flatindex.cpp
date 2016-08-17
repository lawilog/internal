#include <iostream>
#include <array>
#include <functional>
#include <numeric>
using namespace std;

template<unsigned k>
struct flatMapper
{
	static inline size_t index(const size_t* n, const size_t* i)
	{
		return i[k] + n[k] * flatMapper<k-1>::index(n, i);
	}
};

template<>
struct flatMapper<0>
{
	static inline size_t index(const size_t* n, const size_t* i)
	{
		return i[0];
	}
};

/*
template<unsigned N>
inline size_t variflat(array<size_t,N> n)
{
	return 0;
}

template<unsigned N, typename... Args>
inline size_t variflat(const array<size_t,N>& n, size_t i, Args... args)
{
	static const unsigned short int k = sizeof...(Args);
	return i * accumulate(&n[N-k], n.end(), 1, std::multiplies<size_t>()) + variflat<N>(n, args...);
}*/

template <unsigned N>
class flat
{
	private:
		array<size_t,N> n;
	
	public:
		flat(array<size_t,N> _n) : n(_n) {};
		
		inline size_t flat_ind(const array<size_t,N>& i) {return flatMapper<N-1>::index(&n[0], &i[0]);}
		
		inline size_t variflat()
		{
			return 0;
		}

		template<typename... Args>
		inline size_t variflat(size_t i, Args... args)
		{
			static const unsigned short int k = sizeof...(Args);
			return i * accumulate(&n[N-k], n.end(), 1, std::multiplies<size_t>()) + variflat(args...);
		}
		
		/*template<typename... Args>
		inline size_t variflat_ind(Args... args)
		{
			return variflat<N>(n, args...);
		}*/
};

int main()
{
	const array<size_t,4> S = {3, 5, 7, 1337};
	flat<4> a(S);
	array<size_t,4> ind;
	cin >> ind[0]; cin >> ind[1]; cin >> ind[2]; cin >> ind[3];
	cout<< a.flat_ind(ind) <<endl;
	
	// cout<< variflat<4>(S, ind[0], ind[1], ind[2], ind[3]) <<endl;
	// cout<< a.variflat_ind(ind[0], ind[1], ind[2], ind[3]) <<endl;
	cout<< a.variflat(ind[0], ind[1], ind[2], ind[3]) <<endl;
	return 0;
}