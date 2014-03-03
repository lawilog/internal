#include <Eigen/Dense>
#include <Eigen/QR>
#include <stdexcept>

// C++ helpers of common Matlab/Octave stuff using Eigen library
// Important: contrary to Matlab/Octave, the first index of a C++ vector has index 0

namespace Eigen {

// Matlab:  ind = find(x > 0)
// C++:     VectorXi ind = find(x.array() > 0);
VectorXi find(const Matrix<bool, Dynamic, 1>& b)
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


// Matlab:  N = M(:, ind);
// C++:     MatrixXd y = pick_col(M, ind);
template <typename T>
Matrix<T, Dynamic, Dynamic> pick_col(const Matrix<T, Dynamic, Dynamic>& M, const VectorXi& ind)
{
	Matrix<T, Dynamic, Dynamic> N(M.rows(), ind.size());
	for(unsigned i = 0; i < ind.size(); ++i)
		N.col(i) = M.col(ind(i));
	
	return N;
}


// Matlab:  N = M(ind, :);
// C++:     MatrixXd y = pick_row(M, ind);
template <typename T>
Matrix<T, Dynamic, Dynamic> pick_row(const Matrix<T, Dynamic, Dynamic>& M, const VectorXi& ind)
{
	Matrix<T, Dynamic, Dynamic> N(ind.size(), M.cols());
	for(unsigned i = 0; i < ind.size(); ++i)
		N.row(i) = M.row(ind(i));
	
	return N;
}


// Matlab:  y = x;  y(ind) = [];
// C++:     VectorXd y = remove(x, ind);
// ind must be sorted and unique - an expection is thrown otherwise
template <typename T>
Matrix<T, Dynamic, 1> remove(const Matrix<T, Dynamic, 1>& x, const VectorXi& ind)
{
	if(ind.size() == 0)
		return x;
	
	for(unsigned i = 0;  i < ind.size();  ++i)
		if(ind(i) < 0 || ind(i) >= x.size())
			throw std::range_error("EigenOctave: remove: error: each index must be within range of 0 <= ind(i) < x.size()");
	
	for(unsigned i = 1;  i < ind.size();  ++i)
		if(ind(i) <= ind(i-1))
			throw std::invalid_argument("EigenOctave: remove: error: ind must be sorted and without duplicate entries");
	
	if(x.size() <= ind.size())
		return Matrix<T, Dynamic, 1>();
	
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
