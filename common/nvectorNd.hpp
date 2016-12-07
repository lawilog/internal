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
	static void init(type& w, const size_t* dim)
	{
		w.resize(*dim);
		for(unsigned i = 0; i < *dim; ++i)
			nvectorNd_helper<T,N-1>::init(w[i], dim+1);
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
	using T_reference = typename std::vector<T>::reference;
	using T_const_reference = typename std::vector<T>::const_reference;
	
	private:
		template<typename... Ind>
		inline void check_ind(Ind... ind) const
		{
			static_assert(N == sizeof...(Ind), "Wrong number of indices.");
		}
		
	public:
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
		
		template<typename... Ind>
		inline T_reference operator()       (Ind... ind) noexcept
		{
			check_ind(ind...);
			return nvectorNd_helper<T,N>::elem(value, ind...);
		}
		template<typename... Ind>
		inline T_const_reference operator() (Ind... ind) const noexcept
		{
			check_ind(ind...);
			return nvectorNd_helper<T,N>::elem(value, ind...);
		}
		template<typename... Ind>
		inline T_reference at               (Ind... ind)
		{
			check_ind(ind...);
			return nvectorNd_helper<T,N>::at(value, ind...);
		}
		template<typename... Ind>
		inline T_const_reference at         (Ind... ind) const
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
