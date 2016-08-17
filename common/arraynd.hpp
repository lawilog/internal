#ifndef _LW_ARRAYND_HPP
#define _LW_ARRAYND_HPP

#include <vector>
#include <array>
#include <functional>
#include <numeric>
#include "printf++.hpp"

namespace LW {

template<class T, unsigned N>
class arraynd
{
	private:
		std::vector<T> flat;
		std::array<size_t,N> n;
		
		inline void check_ind() const {}
		
		template<typename... Ind>
		inline void check_ind(size_t i, Ind... ind) const
		{
			static const unsigned k = N - 1 - sizeof...(Ind);
			if(i >= n[k])
				throw std::out_of_range(strprintf("arraynd<%u>: index %u (which is %u) is out of range (%u)", N, k, i, n[k]));
			check_ind(ind...);
		}
		
		inline size_t flat_index()
		{
			return 0;
		}
		
		template<typename... Ind>
		inline size_t flat_index(size_t i, Ind... ind)
		{
			return i * accumulate(&n[N - sizeof...(Ind)], n.end(), 1, std::multiplies<size_t>()) + flat_index(ind...);
		}
	
	public:
		arraynd() { std::fill(n.begin(), n.end(), 0); }
		arraynd(std::array<size_t,N> _n) :
			flat( std::accumulate(_n.begin(), _n.end(), 1, std::multiplies<size_t>()) ),
			n(_n) {}
		
		template<typename... Ind>
		inline T& operator()       (Ind... ind) noexcept
		{
			return flat[flat_index(ind...)];
		}
		template<typename... Ind>
		inline const T& operator() (Ind... ind) const noexcept
		{
			return flat[flat_index(ind...)];
		}
		template<typename... Ind>
		inline T& at               (Ind... ind)
		{
			check_ind(ind...);
			return flat.at(flat_index(ind...));
		}
		template<typename... Ind>
		inline const T& at         (Ind... ind) const
		{
			check_ind(ind...);
			return flat.at(flat_index(ind...));
		}
		
		inline const std::array<size_t,N>& size() const {return n;}
		
		void resize(const std::array<size_t,N>& _n)
		{
			flat.resize( std::accumulate(_n.begin(), _n.end(), 1, std::multiplies<size_t>()) );
			n = _n;
		}
		
		inline typename std::vector<T>::iterator flat_begin() {return flat.begin();}
		inline typename std::vector<T>::iterator flat_end() {return flat.end();}
		inline const std::vector<T>& flat_ref() const {return flat;}
};

}

#endif // _LW_ARRAYND_HPP
