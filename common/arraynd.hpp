#ifndef _LW_ARRAYND_HPP
#define _LW_ARRAYND_HPP

#include <vector>
#include <array>
#include <iostream>
#include "printf++.hpp"

namespace LW {
	
template<unsigned k>
struct arraynd_
{
	static inline size_t flat_index(const size_t* n, const size_t* i)
	{
		return i[k] + n[k] * arraynd_<k-1>::flat_index(n, i);
	}
	static inline size_t prod(const size_t* a)
	{
		return a[k] * arraynd_<k-1>::prod(a);
	}
};

template<>
struct arraynd_<0>
{
	static inline size_t flat_index(const size_t* n, const size_t* i)
	{
		return i[0];
	}
	static inline size_t prod(const size_t* a)
	{
		return a[0];
	}
};

template<class T, unsigned N>
class arraynd
{
	private:
		std::vector<T> flat;
		std::array<size_t,N> n;
		
		inline void check_ind(const std::array<size_t,N>& ind) const
		{
			for(unsigned dim = 0; dim < N; ++dim)
				if(ind[dim] >= n[dim])
					throw std::out_of_range(strprintf("arraynd<%u>: index %u (which is %u) is out of range (%u)", N, dim, ind[dim], n[dim]));
		}
	
	public:
		arraynd()
		{
			for(unsigned dim = 0; dim < N; ++dim)
				n[dim] = 0;
		}
		arraynd(std::array<size_t,N> _n) : flat(arraynd_<N-1>::prod(&_n[0])), n(_n) {}
		
		inline T& operator()       (const std::array<size_t,N>& ind) noexcept
		{
			return flat[arraynd_<N-1>::flat_index(&n[0], &ind[0])];
		}
		inline const T& operator() (const std::array<size_t,N>& ind) const noexcept
		{
			return flat[arraynd_<N-1>::flat_index(&n[0], &ind[0])];
		}
		inline T& at               (const std::array<size_t,N>& ind)
		{
			check_ind(ind);
			return flat.at(arraynd_<N-1>::flat_index(&n[0], &ind[0]));
		}
		inline const T& at         (const std::array<size_t,N>& ind) const
		{
			check_ind(ind);
			return flat.at(arraynd_<N-1>::flat_index(&n[0], &ind[0]));
		}
		
		inline const std::array<size_t,N>& size() const {return n;}
		
		void resize(const std::array<size_t,N>& _n)
		{
			flat.resize(arraynd_<N-1>::prod(&_n[0]));
			n = _n;
		}
		
		inline typename std::vector<T>::iterator flat_begin() {return flat.begin();}
		inline typename std::vector<T>::iterator flat_end() {return flat.end();}
		inline const std::vector<T>& flat_ref() const {return flat;}
};

}

#endif // _LW_ARRAYND_HPP
