#include <iostream>
#include <array>
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

template <unsigned N>
class flat
{
	private:
		array<size_t,N> n;
	
	public:
		flat(array<size_t,N> _n) : n(_n) {};
		
		inline size_t flat_ind(const array<size_t,N>& i) {return flatMapper<N-1>::index(&n[0], &i[0]);}
};

int main()
{
	flat<4> a({3, 5, 7, 1337});
	array<size_t,4> ind;
	cin >> ind[0]; cin >> ind[1]; cin >> ind[2]; cin >> ind[3];
	cout<< a.flat_ind(ind) <<endl;
	return 0;
}