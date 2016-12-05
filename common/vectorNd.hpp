#ifndef _LW_VECTORND_HPP
#define _LW_VECTORND_HPP

#include <vector>
#include <array>
#include <functional>
#include <numeric>

namespace LW {

template<class T, unsigned N>
class vectorNd
{
	private:
		std::vector<T> flat;
		std::array<size_t,N> n;
		
		inline void check_range() const {}
		
		template<typename... Ind>
		inline void check_range(size_t i, Ind... ind) const
		{
			// asserts we never get too many "ind"s (ok, because this is a private function, only called after check_ind)
			static const unsigned k = N - 1 - sizeof...(Ind);
			if(i >= n[k])
				throw std::out_of_range("vectorNd<"+ std::to_string(N) + ">: index "+ std::to_string(k) + " (which is "+ std::to_string(i) + ") is out of range ("+ std::to_string(n[k]) + ")");
			
			check_range(ind...);
		}
		
		template<typename... Ind>
		inline void check_ind(Ind... ind) const
		{
			static_assert(N == sizeof...(Ind), "Wrong number of indices.");
		}
		
		inline size_t flat_index() const noexcept
		{
			return 0;
		}
		
		template<typename... Ind>
		inline size_t flat_index(size_t i, Ind... ind) const noexcept
		{
			return i * accumulate(&n[N - sizeof...(Ind)], n.end(), 1, std::multiplies<size_t>()) + flat_index(ind...);
		}
	
	public:
		vectorNd() { std::fill(n.begin(), n.end(), 0); }
		vectorNd(std::array<size_t,N> _n) :
			flat( std::accumulate(_n.begin(), _n.end(), 1, std::multiplies<size_t>()) ),
			n(_n) {}
		
		template<typename... Ind>
		inline typename std::vector<T>::reference operator()       (Ind... ind) noexcept
		{
			check_ind(ind...);
			return flat[flat_index(ind...)];
		}
		template<typename... Ind>
		inline typename std::vector<T>::const_reference operator() (Ind... ind) const noexcept
		{
			check_ind(ind...);
			return flat[flat_index(ind...)];
		}
		template<typename... Ind>
		inline typename std::vector<T>::reference at               (Ind... ind)
		{
			check_ind(ind...);
			check_range(ind...);
			return flat.at(flat_index(ind...));
		}
		template<typename... Ind>
		inline typename std::vector<T>::const_reference at         (Ind... ind) const
		{
			check_ind(ind...);
			check_range(ind...);
			return flat.at(flat_index(ind...));
		}
		
		inline const std::array<size_t,N>& size() const noexcept {return n;}
		
		void resize(const std::array<size_t,N>& _n)
		{
			flat.resize( std::accumulate(_n.begin(), _n.end(), 1, std::multiplies<size_t>()) );
			n = _n;
		}
		
		inline typename std::vector<T>::iterator flat_begin() noexcept {return flat.begin();}
		inline typename std::vector<T>::iterator flat_end() noexcept {return flat.end();}
		inline const std::vector<T>& flat_cref() const noexcept {return flat;}
		inline T* flat_data() noexcept {return flat.data();}
		inline const T* flat_data() const noexcept {return flat.data();}
};

}

#endif // _LW_VECTORND_HPP
