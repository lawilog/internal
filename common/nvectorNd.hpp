#ifndef _LW_NVECTORND_HPP
#define _LW_NVECTORND_HPP

#include <vector>
#include <array>
#include <cstdarg>

namespace LW {

template<class T, unsigned N> struct nvectorNd_helper;
template<class T> struct nvectorNd_helper<T,1>
{
	typedef std::vector<T> type;
	static void init(type& w, const size_t* dim)
	{
		w.resize(*dim);
	}
	static inline typename std::vector<T>::reference element(type& w, const size_t* dim)
	{
		return w[*dim];
	}
};
template<class T, unsigned N>
struct nvectorNd_helper
{
	typedef std::vector<typename nvectorNd_helper<T,N-1>::type> type;
	static void init(type& w, const size_t* dim)
	{
		w.resize(*dim);
		for(unsigned i = 0; i < *dim; ++i)
			nvectorNd_helper<T,N-1>::init(w[i], dim+1);
	}
	static inline typename std::vector<T>::reference element(type& w, const size_t* dim)
	{
		return nvectorNd_helper<T,N-1>::element(w[*dim], dim+1);
	}
};

template<class T, unsigned N>
struct nvectorNd
{
	using nested_vector = typename nvectorNd_helper<T,N>::type;
	nested_vector value;
	
	nvectorNd() {}
	//nvectorNd(const std::array<size_t,N>& n) { nvectorNd_helper<T,N>::init(&n[0], value);}
	nvectorNd(size_t i...)
	{
		std::array<size_t,N> n;
		n[0] = i;
		va_list L;
		va_start(L, i);
		for(unsigned i = 1; i < N; ++i)
			n[i] = va_arg(L, size_t);
		
		va_end(L);
		
		nvectorNd_helper<T,N>::init(value, &n[0]);
	}
	
	inline typename std::vector<T>::reference operator()(size_t i...) noexcept
	{
		std::array<size_t,N> n;
		n[0] = i;
		va_list L;
		va_start(L, i);
		for(unsigned i = 1; i < N; ++i)
			n[i] = va_arg(L, size_t);
		
		va_end(L);
		
		return nvectorNd_helper<T,N>::element(value, &n[0]);
	}
	
	inline typename nested_vector::reference       operator[](size_t i) noexcept { return value[i]; }
	inline typename nested_vector::const_reference operator[](size_t i) const noexcept { return value[i]; }
	inline typename nested_vector::reference       at(size_t i) { return value.at(i); }
	inline typename nested_vector::const_reference at(size_t i) const { return value.at(i); }
};

}

#endif // _LW_NVECTORND_HPP
