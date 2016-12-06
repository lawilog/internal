#ifndef _LW_NVECTORND_HPP
#define _LW_NVECTORND_HPP

#include <vector>
#include <array>

namespace LW {

template<class T, unsigned N> struct nvectorNd_helper;
template<class T> struct nvectorNd_helper<T,1>
{
	typedef std::vector<T> type;
	static void init(const size_t* dim, type& w)
	{
		w.resize(*dim);
	}
};
template<class T, unsigned N>
struct nvectorNd_helper
{
	typedef std::vector<typename nvectorNd_helper<T,N-1>::type> type;
	static void init(const size_t* dim, type& w)
	{
		w.resize(*dim);
		for(unsigned i = 0; i < *dim; ++i)
			nvectorNd_helper<T,N-1>::init(dim+1, w[i]);
	}
};

template<class T, unsigned N>
class nvectorNd
{
	using nested_vector = typename nvectorNd_helper<T,N>::type;
	
	private:
		nested_vector v;
	
	public:
		nvectorNd() {}
		nvectorNd(const std::array<size_t,N>& n) { nvectorNd_helper<T,N>::init(&n[0], v);}
		
		inline typename nested_vector::reference       operator[](size_t i) noexcept { return v[i]; }
		inline typename nested_vector::const_reference operator[](size_t i) const noexcept { return v[i]; }
		inline typename nested_vector::reference       at(size_t i) noexcept { return v.at(i); }
		inline typename nested_vector::const_reference at(size_t i) const noexcept { return v.at(i); }
};

}

#endif // _LW_NVECTORND_HPP
