#ifndef _LW_ARRAY4D_HPP
#define _LW_ARRAY4D_HPP

#include <vector>
#include <array>
#include "printf++.hpp"

namespace LW {

template<class T>
class array4d
{
	private:
		std::vector<T> flat;
		std::array<size_t,4> n;
		size_t n2;
		size_t n3;
	
	public:
		array4d() {n = {0, 0, 0, 0}; n2 = 0; n3 = 0;};
		array4d(std::array<size_t,4> _n) : flat(_n[0]*_n[1]*_n[2]*_n[3]), n(_n) {n2 = _n[1]*_n[2]; n3 = _n[1]*_n[2]*_n[3];};
		array4d(size_t nx, size_t ny, size_t nz, size_t nu) : flat(nx*ny*nz*nu), n({nx, ny, nz, nu}) {n2 = ny*nz*nu; n3 = ny*nz*nu;};
		
		inline T& operator()       (size_t i, size_t j, size_t k, size_t l) noexcept       {return flat[n3*i+n2*j+n[3]*k+l];}
		inline const T& operator() (size_t i, size_t j, size_t k, size_t l) const noexcept {return flat[n3*i+n2*j+n[3]*k+l];}
		inline T& at               (size_t i, size_t j, size_t k, size_t l)
		{
			if(i >= n[0]) throw std::out_of_range(strprintf("array4d: first index (which is %u) out of range (%u)", i, n[0]));
			if(j >= n[1]) throw std::out_of_range(strprintf("array4d: second index (which is %u) out of range (%u)", j, n[1]));
			if(k >= n[2]) throw std::out_of_range(strprintf("array4d: third index (which is %u) out of range (%u)", k, n[2]));
			if(l >= n[3]) throw std::out_of_range(strprintf("array4d: fourth index (which is %u) out of range (%u)", l, n[3]));
			return flat.at(n3*i+n2*j+n[3]*k+l);
		}
		inline const T& at         (size_t i, size_t j, size_t k, size_t l) const
		{
			if(i >= n[0]) throw std::out_of_range(strprintf("array4d: first index (which is %u) out of range (%u)", i, n[0]));
			if(j >= n[1]) throw std::out_of_range(strprintf("array4d: second index (which is %u) out of range (%u)", j, n[1]));
			if(k >= n[2]) throw std::out_of_range(strprintf("array4d: third index (which is %u) out of range (%u)", k, n[2]));
			if(l >= n[3]) throw std::out_of_range(strprintf("array4d: fourth index (which is %u) out of range (%u)", l, n[3]));
			return flat.at(n3*i+n2*j+n[3]*k+l);
		}
		
		inline const std::array<size_t,4>& size() const {return n;}
		
		void resize(size_t nx, size_t ny, size_t nz, size_t nu) {flat.resize(nx*ny*nz*nu); n[0] = nx; n[1] = ny; n[2] = nz; n[3] = nu; n2 = ny*nz; n3 = ny*nz*nu;}
		void resize(std::array<size_t,4> _n) {flat.resize(_n[0]*_n[1]*_n[2]*_n[3]); n = _n; n2 = _n[1]*_n[2]; n3 = _n[1]*_n[2]*_n[3];}
		
		inline typename std::vector<T>::iterator flat_begin() {return flat.begin();}
		inline typename std::vector<T>::iterator flat_end() {return flat.end();}
		inline const std::vector<T>& flat_ref() const {return flat;}
};

}

#endif // _LW_ARRAY4D_HPP
