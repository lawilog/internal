#ifndef _LW_LSCOV_
#define _LW_LSCOV_

#include <iostream>
#include <stdexcept>
#include <Eigen/Dense>
#include <Eigen/QR>
#include <Eigen/LU>

/*
 * C++ implementation of Matlab/Octave function lscov
 * LSCOV(A,b,V) returns the vector that minimizes
 * (A*X-b)'*inv(V)*(A*X-b) for the case in which length(b) > length(X)
 * identical to: x = inv(A'*inv(V)*A)*A'*inv(V)*b, but here with QR
 * Reference: G. Strang, "Introduction to Applied Mathematics", Wellesley-Cambridge, p. 398, 1986.
 */

namespace Eigen {

VectorXd lscov(const MatrixXd& A, const VectorXd& b, const MatrixXd& V)
{
	const unsigned m = A.rows();
	const unsigned n = A.cols();
	if(m <= n)
		throw std::invalid_argument("lscov: Problem must be over-determined.");
	
	if(b.size() != m || V.rows() != m || V.cols() != m)
		throw std::invalid_argument("lscov: dimension mismatch");
	
	HouseholderQR<MatrixXd> qr(A);
	const MatrixXd q = qr.householderQ(); // m x m
	const MatrixXd r = qr.matrixQR().triangularView<Upper>(); // m x n
	const MatrixXd efg = q.transpose() * V * q; // m x m
	const MatrixXd cd = q.transpose() * b; // m x 1
	
	return r.topLeftCorner(n, n).lu().solve(cd.topRows(n)-efg.topRightCorner(n, m-n)*(efg.bottomRightCorner(m-n, m-n).lu().solve(cd.bottomRows(m-n))));
}

VectorXd lscov(const MatrixXd& A, const VectorXd& b, const VectorXd& w)
{
	return lscov(A, b, MatrixXd(w.cwiseInverse().asDiagonal()));
}

}

#endif // _LW_LSCOV_
