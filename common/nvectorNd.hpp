#ifndef _LW_NVECTORND_HPP
#define _LW_NVECTORND_HPP

#include <vector>
#include <array>
#include <cstdarg>
/* nvectorNd<T,N> creates nested N-dimensional std::vector of type T
 * e.g. nvectorNd<int,3> v; is effectively vector<vector<vector<int>>> v;
 * provides both v[1][2][3] and v(1,2,3) interface
 * also v.at(1,2,3) and v.at(1)[2].at(3), for boundary checks etc.
 * also allows direct access via v.value
 */

namespace LW {

template<class T, unsigned N> struct nvectorNd_helper;
template<class T> struct nvectorNd_helper<T,1>
{
	typedef std::vector<T> type;
	
	inline static void init(type& w, const size_t ni)
	{
		w.resize(ni);
	}
	template<typename... Ind>
	inline static typename std::vector<T>::reference elem(type& w, size_t i) noexcept
	{
		return w[i];
	}
	template<typename... Ind>
	inline static typename std::vector<T>::const_reference elem(const type& w, size_t i) noexcept
	{
		return w[i];
	}
	template<typename... Ind>
	inline static typename std::vector<T>::reference at(type& w, size_t i)
	{
		return w.at(i);
	}
	template<typename... Ind>
	inline static typename std::vector<T>::const_reference at(const type& w, size_t i)
	{
		return w.at(i);
	}
};
template<class T, unsigned N>
struct nvectorNd_helper
{
	typedef std::vector<typename nvectorNd_helper<T,N-1>::type> type;
	
	template<typename... Ind>
	inline static void init(type& w, const size_t ni, Ind... ind)
	{
		w.resize(ni);
		for(unsigned i = 0; i < ni; ++i)
			nvectorNd_helper<T,N-1>::init(w[i], ind...);
	}
	template<typename... Ind>
	inline static typename std::vector<T>::reference elem(type& w, size_t i, Ind... ind) noexcept
	{
		return nvectorNd_helper<T,N-1>::elem(w[i], ind...);
	}
	template<typename... Ind>
	inline static typename std::vector<T>::const_reference elem(const type& w, size_t i, Ind... ind) noexcept
	{
		return nvectorNd_helper<T,N-1>::elem(w[i], ind...);
	}
	template<typename... Ind>
	inline static typename std::vector<T>::reference at(type& w, size_t i, Ind... ind)
	{
		return nvectorNd_helper<T,N-1>::at(w.at(i), ind...);
	}
	template<typename... Ind>
	inline static typename std::vector<T>::const_reference at(const type& w, size_t i, Ind... ind)
	{
		return nvectorNd_helper<T,N-1>::at(w.at(i), ind...);
	}
};

template<class T, unsigned N>
class nvectorNd
{
	using nested_vector = typename nvectorNd_helper<T,N>::type;
	
	private:
		template<typename... Ind>
		inline void check_ind(Ind... ind) const
		{
			static_assert(N == sizeof...(Ind), "Wrong number of indices.");
		}
		
	public:
		nested_vector value;
		
		nvectorNd() {}
		
		nvectorNd(const nested_vector& _value) : value(_value) {}
		
		template<typename... Ind>
		nvectorNd(Ind... ind)
		{
			check_ind(ind...);
			nvectorNd_helper<T,N>::init(value, ind...);
		}
		
		template<typename... Ind>
		inline typename std::vector<T>::reference operator()(Ind... ind) noexcept
		{
			check_ind(ind...);
			return nvectorNd_helper<T,N>::elem(value, ind...);
		}
		template<typename... Ind>
		inline typename std::vector<T>::const_reference operator() (Ind... ind) const noexcept
		{
			check_ind(ind...);
			return nvectorNd_helper<T,N>::elem(value, ind...);
		}
		template<typename... Ind>
		inline typename std::vector<T>::reference at(Ind... ind)
		{
			check_ind(ind...);
			return nvectorNd_helper<T,N>::at(value, ind...);
		}
		template<typename... Ind>
		inline typename std::vector<T>::const_reference at(Ind... ind) const
		{
			check_ind(ind...);
			return nvectorNd_helper<T,N>::at(value, ind...);
		}
		
		inline typename nested_vector::reference       operator[](size_t i) noexcept { return value[i]; }
		inline typename nested_vector::const_reference operator[](size_t i) const noexcept { return value[i]; }
		inline typename nested_vector::reference       at(size_t i) { return value.at(i); }
		inline typename nested_vector::const_reference at(size_t i) const { return value.at(i); }
};

}

#endif // _LW_NVECTORND_HPP
