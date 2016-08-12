#ifndef _LW_ARRAY3D_HPP
#define _LW_ARRAY3D_HPP

#include <vector>
#include <array>

namespace LW {

template<class T>
class array3d
{
	private:
		std::vector<T> flat;
		std::array<size_t,3> n;
		size_t nn;
	
	public:
		array3d() {nn = 0;};
		array3d(std::array<size_t,3> _n) : flat(_n[0]*_n[1]*_n[2]), n(_n) {nn = _n[1]*_n[2];};
		array3d(size_t nx, size_t ny, size_t nz) : flat(nx*ny*nz), n({nx, ny, nz}) {nn = ny*nz;};
		
		inline T& operator()       (size_t i, size_t j, size_t k) noexcept       {return flat[nn*i+n[2]*j+k];}
		inline T& at               (size_t i, size_t j, size_t k)                {return flat.at(nn*i+n[2]*j+k);}
		inline const T& operator() (size_t i, size_t j, size_t k) const noexcept {return flat[nn*i+n[2]*j+k];}
		inline const T& at         (size_t i, size_t j, size_t k) const          {return flat.at(nn*i+n[2]*j+k);}
		
		inline const std::array<size_t,3>& size() const {return n;}
		
		void resize(size_t nx, size_t ny, size_t nz) {flat.resize(nx*ny*nz); n[0] = nx; n[1] = ny; n[2] = nz; nn = ny*nz;}
		void resize(std::array<size_t,3> _n) {flat.resize(_n[0]*_n[1]*_n[2]); n = _n; nn = _n[1]*_n[2];}
		
		inline T* flat_begin() const {return flat.begin();}
		inline T* flat_end() const {return flat.end();}
};

}

#endif // _LW_ARRAY3D_HPP
