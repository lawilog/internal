#ifndef _LW_ARRAY2D_HPP
#define _LW_ARRAY2D_HPP

#include <vector>
#include <array>

namespace LW {

template<class T>
class array2d
{
	private:
		std::vector<T> flat;
		std::array<size_t,2> n;
	
	public:
		array2d() {};
		array2d(std::array<size_t,2> _n) : flat(_n[0]*_n[1]), n(_n) {};
		array2d(size_t nx, size_t ny) : flat(nx*ny), n({nx, ny}) {};
		
		inline T& operator()       (size_t i, size_t j) noexcept       {return flat[n[1]*i+j];}
		inline T& at               (size_t i, size_t j)                {return flat.at(n[1]*i+j);}
		inline const T& operator() (size_t i, size_t j) const noexcept {return flat[n[1]*i+j];}
		inline const T& at         (size_t i, size_t j) const          {return flat.at(n[1]*i+j);}
		
		inline const std::array<size_t,2>& size() const noexcept {return n;}
		
		void resize(size_t nx, size_t ny) {flat.resize(nx*ny); n[0] = nx; n[1] = ny;}
		void resize(std::array<size_t,2> _n) {flat.resize(_n[0]*_n[1]); n = _n;}
		
		inline T* flat_begin() const {return flat.begin();}
		inline T* flat_end() const {return flat.end();}
};

}

#endif // _LW_ARRAY2D_HPP
