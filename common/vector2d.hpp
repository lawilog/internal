#ifndef _LW_VECTOR2D_HPP
#define _LW_VECTOR2D_HPP

#include <vector>
#include <array>
#include <stdexcept>
#include "printf++.hpp"

namespace LW {

template<class T>
class vector2d
{
	private:
		std::vector<T> flat;
		std::array<size_t,2> n;
	
	public:
		vector2d() {n = {0, 0};};
		vector2d(std::array<size_t,2> _n) : flat(_n[0]*_n[1]), n(_n) {};
		vector2d(size_t nx, size_t ny) : flat(nx*ny), n({nx, ny}) {};
		
		inline T& operator()       (size_t i, size_t j) noexcept       {return flat[n[1]*i+j];}
		inline const T& operator() (size_t i, size_t j) const noexcept {return flat[n[1]*i+j];}
		inline T& at               (size_t i, size_t j)
		{
			if(i >= n[0]) throw std::out_of_range(strprintf("vector2d: first index (which is %u) out of range (%u)", i, n[0]));
			if(j >= n[1]) throw std::out_of_range(strprintf("vector2d: second index (which is %u) out of range (%u)", j, n[1]));
			return flat.at(n[1]*i+j);
		}
		inline const T& at         (size_t i, size_t j) const
		{
			if(i >= n[0]) throw std::out_of_range(strprintf("vector2d: first index (which is %u) out of range (%u)", i, n[0]));
			if(j >= n[1]) throw std::out_of_range(strprintf("vector2d: second index (which is %u) out of range (%u)", j, n[1]));
			return flat.at(n[1]*i+j);
		}
		
		inline const std::array<size_t,2>& size() const noexcept {return n;}
		
		void resize(size_t nx, size_t ny) {flat.resize(nx*ny); n[0] = nx; n[1] = ny;}
		void resize(std::array<size_t,2> _n) {flat.resize(_n[0]*_n[1]); n = _n;}
		
		inline typename std::vector<T>::iterator flat_begin() {return flat.begin();}
		inline typename std::vector<T>::iterator flat_end() {return flat.end();}
		inline const std::vector<T>& flat_ref() const {return flat;}
};

}

#endif // _LW_VECTOR2D_HPP
