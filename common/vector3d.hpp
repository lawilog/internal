#ifndef _LW_VECTOR3D_HPP
#define _LW_VECTOR3D_HPP

#include <vector>
#include <array>

namespace LW {

template<class T>
class vector3d
{
	private:
		std::vector<T> flat;
		std::array<size_t,3> n;
		size_t nn;
		inline void check_range(size_t i, size_t j, size_t k) const
		{
			if(i >= n[0]) throw std::out_of_range("vector3d: first index (which is " + std::to_string(i) + ") out of range ("+ std::to_string(n[0]) + ")");
			if(j >= n[1]) throw std::out_of_range("vector3d: second index (which is "+ std::to_string(j) + ") out of range ("+ std::to_string(n[1]) + ")");
			if(k >= n[2]) throw std::out_of_range("vector3d: third index (which is "+ std::to_string(k) + ") out of range ("+ std::to_string(n[2]) + ")");
		}
	
	public:
		vector3d() {n = {0, 0, 0}; nn = 0;};
		vector3d(std::array<size_t,3> _n) : flat(_n[0]*_n[1]*_n[2]), n(_n) {nn = _n[1]*_n[2];};
		vector3d(size_t nx, size_t ny, size_t nz) : flat(nx*ny*nz), n({nx, ny, nz}) {nn = ny*nz;};
		
		inline typename std::vector<T>::reference operator()       (size_t i, size_t j, size_t k) noexcept       {return flat[nn*i+n[2]*j+k];}
		inline typename std::vector<T>::const_reference operator() (size_t i, size_t j, size_t k) const noexcept {return flat[nn*i+n[2]*j+k];}
		inline typename std::vector<T>::reference at               (size_t i, size_t j, size_t k)
		{
			check_range(i, j, k);
			return flat.at(nn*i+n[2]*j+k);
		}
		inline typename std::vector<T>::const_reference at         (size_t i, size_t j, size_t k) const
		{
			check_range(i, j, k);
			return flat.at(nn*i+n[2]*j+k);
		}
		
		inline const std::array<size_t,3>& size() const {return n;}
		
		void resize(size_t nx, size_t ny, size_t nz) {flat.resize(nx*ny*nz); n[0] = nx; n[1] = ny; n[2] = nz; nn = ny*nz;}
		void resize(std::array<size_t,3> _n) {flat.resize(_n[0]*_n[1]*_n[2]); n = _n; nn = _n[1]*_n[2];}
		
		inline typename std::vector<T>::iterator flat_begin() {return flat.begin();}
		inline typename std::vector<T>::iterator flat_end() {return flat.end();}
		inline const std::vector<T>& flat_cref() const noexcept {return flat;}
		inline typename std::vector<T>::pointer flat_data() noexcept {return flat.data();}
		inline typename std::vector<T>::const_pointer flat_data() const noexcept {return flat.data();}
};

}

#endif // _LW_VECTOR3D_HPP
