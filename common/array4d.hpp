#ifndef _LW_ARRAY4D_HPP
#define _LW_ARRAY4D_HPP

#include <vector>
#include <array>
#include <iostream>
#include "printf++.hpp"

namespace LW {

template<class T>
class array4d
{
	private:
		std::vector<T> flat;
		std::array<size_t,4> n;
		size_t n32;
		size_t n321;
		inline void check_ind(size_t i, size_t j, size_t k, size_t l) const
		{
			if(i >= n[0]) throw std::out_of_range(strprintf("array4d: first index (which is %u) out of range (%u)", i, n[0]));
			if(j >= n[1]) throw std::out_of_range(strprintf("array4d: second index (which is %u) out of range (%u)", j, n[1]));
			if(k >= n[2]) throw std::out_of_range(strprintf("array4d: third index (which is %u) out of range (%u)", k, n[2]));
			if(l >= n[3]) throw std::out_of_range(strprintf("array4d: fourth index (which is %u) out of range (%u)", l, n[3]));
		}
		inline size_t flatind(size_t i, size_t j, size_t k, size_t l) {return n321*i+n32*j+n[3]*k+l;}
	
	public:
		array4d() : array4d(0, 0, 0, 0) {};
		array4d(std::array<size_t,4> n) : array4d(n[0], n[1], n[2], n[3]) {};
		array4d(size_t n0, size_t n1, size_t n2, size_t n3) : flat(n0*n1*n2*n3), n({n0, n1, n2, n3}), n32(n3*n2), n321(n3*n2*n1) {};
		
		inline T& operator()       (size_t i, size_t j, size_t k, size_t l) noexcept       {return flat[flatind(i, j, k, l)];}
		inline const T& operator() (size_t i, size_t j, size_t k, size_t l) const noexcept {return flat[flatind(i, j, k, l)];}
		inline T& at               (size_t i, size_t j, size_t k, size_t l)
		{
			check_ind(i, j, k, l);
			return flat.at(flatind(i, j, k, l));
		}
		inline const T& at         (size_t i, size_t j, size_t k, size_t l) const
		{
			check_ind(i, j, k, l);
			return flat.at(flatind(i, j, k, l));
		}
		
		inline const std::array<size_t,4>& size() const {return n;}
		
		void resize(size_t n0, size_t n1, size_t n2, size_t n3)
		{
			flat.resize(n0 * n1 * n2 * n3);
			n[0] = n0; n[1] = n1; n[2] = n2; n[3] = n3;
			n32 = n3*n2; n321 = n3*n2*n1;
		}
		void resize(std::array<size_t,4> n) {this->resize(n[0], n[1], n[2], n[3]);}
		
		inline typename std::vector<T>::iterator flat_begin() {return flat.begin();}
		inline typename std::vector<T>::iterator flat_end() {return flat.end();}
		inline const std::vector<T>& flat_ref() const {return flat;}
};

}

#endif // _LW_ARRAY4D_HPP
