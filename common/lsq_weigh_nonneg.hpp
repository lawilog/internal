#ifndef _LW_LSQ_WEIGH_NONNEG_
#define _LW_LSQ_WEIGH_NONNEG_

#include <iostream>
#include <stdexcept>
#include <Eigen/Dense>
#include <Eigen/QR>
#include "EigenOctave.hpp"
#include "lscov.hpp"

/*
 * (C) Lars Winterfeld
 * GNU General Public License, http://www.gnu.org/licenses/
 * C++ implementation of weighted non-negative linear least squares (maybe "WNNLS"?)
 * for given m x n matrix A, m-component vectors b and weights w,
 * it finds the n-component vector x that minimizes
 * sum over i of w_i * ((A*x - b)_i)^2  with the restrain that each component of x >= 0
 * Reference: Franc, V. C.; Hlaváč, V. C.; Navara, M. (2005). "Sequential Coordinate-Wise Algorithm for the Non-negative Least Squares Problem". Computer Analysis of Images and Patterns. Lecture Notes in Computer Science 3691. p. 407. doi:10.1007/11556121_50. ISBN 978-3-540-28969-2, http://cmp.felk.cvut.cz/ftp/articles/franc/Franc-TR-2005-06.pdf
 * improvement on reference:
 *  allow weights and
 *  as final step do more preicse update of all x_i > 0 using QR decomposition
 */

namespace Eigen {

VectorXd lsq_weigh_nonneg(const MatrixXd& A, const VectorXd& b, const VectorXd& w)
{
	const unsigned m = A.rows();
	const unsigned n = A.cols();
	if(b.size() != m || w.size() != m || n < 1 || m < 1)
	{
		std::cerr<<"#error in lsq_weigh_nonneg: If A is a m by n matrix, then b and w must have length m. We also want n >= 1 and m >= 1. A is "<< m <<" by "<< n <<", b has length "<< b.size() <<" and w has length "<< w.size() <<"."<<std::endl;
		throw std::invalid_argument("lsq_weigh_nonneg: dimension mismatch");
	}
	
	// initialization
	const MatrixXd H = A.transpose() * w.asDiagonal() * A;
	const VectorXd f = - A.transpose() * w.asDiagonal() * b;
	VectorXd x = VectorXd::Zero(n), mu = f;
	
	// iterate
	double relerr;
	do
	{
		for(unsigned k = 0; k < n; ++k)
		{
			const double xtmp = x(k);
			x(k) -= mu(k) / H(k,k);
			if(x(k) < 0) x(k) = 0;
			const double d = x(k) - xtmp;
			if(d != 0) mu += d * H.col(k);
		}
		
		relerr = 0;
		for(unsigned k = 0; k < n; ++k)
		{
			if(x(k) != 0)
			{
				double err = mu(k) / x(k);
				if(err < 0) err = -err;
				if(err > relerr) relerr = err;
			}
		}
	}
	while(relerr >= 1e-2);
	
	// update non-zero columns with more costly, but also more precise calculation
	const VectorXi p = find(x.array() > 0);
	const VectorXd xp = lscov(pick_col(A, p), b, w);
	if(find(xp.array() >= 0).all()) set_ind(x, p, xp);
	
	return x;
}

VectorXd lsq_weigh_nonneg(const MatrixXd& A, const VectorXd& b)
{
	return lsq_weigh_nonneg(A, b, VectorXd::Ones(A.rows()));
}

double lsq_weigh_nonneg_err(const MatrixXd& A, const VectorXd& b, const VectorXd& x)
{
	VectorXd r = A * x - b;
	//return r.transpose() * r;
	return r.array().square().sum();
}

double lsq_weigh_nonneg_err(const MatrixXd& A, const VectorXd& b, const VectorXd& w, const VectorXd& x)
{
	VectorXd r = A * x - b;
	// return r.transpose() * w.asDiagonal() * r;
	return ( r.array().square() * w.array() ).sum();
}

}

#endif // _LW_LSQ_WEIGH_NONNEG_
