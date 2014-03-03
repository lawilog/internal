#include <Eigen/Dense>
#include <Eigen/QR>

// C++ helpers of common Matlab/Octave stuff using Eigen library

namespace Eigen {

typedef Matrix<bool, Dynamic, 1> VectorXb;

// Matlab:  ind = find(x > 0)
// C++:     VectorXi ind = find(x.array() > 0);
VectorXi find(const VectorXb& b)
{
	unsigned n = 0;
	for(unsigned i = 0; i < b.size(); ++i)
		if(b(i))
			++n;
	
	VectorXi ind(n);
	
	for(unsigned i = 0, k = 0; i < b.size(); ++i)
		if(b(i))
			ind(k++) = i;
	
	return ind;
}


// Matlab:  y = x(ind);
// C++:     VectorXd y = pick(x, ind);
template <typename T>
Matrix<T, Dynamic, 1> pick(const Matrix<T, Dynamic, 1>& x, const VectorXi& ind)
{
	Matrix<T, Dynamic, 1> y(ind.size());
	for(unsigned i = 0; i < ind.size(); ++i)
		y(i) = x(ind(i));
	
	return y;
}

// Matlab:  y = x;  y(ind) = [];
// C++:     VectorXd y = remove(x, ind);
template <typename T>
Matrix<T, Dynamic, 1> remove(const Matrix<T, Dynamic, 1>& x, const VectorXi& ind) // ind must be sorted and unique
{
	if(x.size() <= ind.size())
		return Matrix<T, Dynamic, 1>();
	
	if(ind.size() == 0)
		return x;
	
	Matrix<T, Dynamic, 1> y(x.size() - ind.size());
	for(unsigned i = 0, k = 0;  i < y.size();  ++i)
	{
		while(k < ind.size()  &&  i+k == ind(k))
			++k;
		
		y(i) = x(i+k);
	}
	return y;
}

}
