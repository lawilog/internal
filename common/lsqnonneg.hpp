#ifndef _LW_LSQNONNEG_
#define _LW_LSQNONNEG_

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/QR>
#include "EigenOctave.hpp"

/*
 * C++ implementation of Matlab/Octave function lsqnonneg
 * The implementation follows the Octave version closely,
 * but please note that all inidices will be off by 1 (C++ arrays start with 0).
 * Octave says they used the following reference:
 * Lawson and Hanson's 1973 algorithm on page 161 of Solving Least Squares Problems.
 * Because this is derived work from Octave, the GNU General Public License applies.
 * See http://www.gnu.org/licenses/ and the original lsqnonneq.m Octave file.
 */

namespace Eigen {

VectorXd lsqnonneg(const MatrixXd& C, const VectorXd& d, const VectorXd& x0)
{
	//std::cout<<"C = [\n"<< C <<"\n];"<<std::endl;
	//std::cout<<"d = [\n"<< d <<"\n];"<<std::endl;
	//std::cout<<"x0 = [\n"<< x0 <<"\n];"<<std::endl;
	
	// Lawson-Hanson Step 1 (LH1): initialize the variables.
	const unsigned m = C.rows();
	const unsigned n = C.cols();
	
	if(d.size() != m || x0.size() != n)
	{
		std::cerr<<"error: dimension mismatch. If C is a m by n matrix, then d must have length m and x must have length n."<<std::endl;
		return x0;
	}
	
	bool useqr = m >= n;
	const unsigned max_iter = 1e5;
	
	VectorXd x(n), xx(n);
	VectorXi p;
	MatrixXd Cp;//, q, r;
	HouseholderQR<MatrixXd> qr;
	
	for(unsigned i = 0; i < n; ++i)
		x(i) = (x0(i) >= 0 ? x0(i) : 0);
	
	p = find(x.array() > 0);
	Cp = pick_col(C, p);
	
	if(useqr)
	{
		qr = HouseholderQR<MatrixXd>(Cp); // .matrixQ(), .matrixR()
		/* q = qr.householderQ();
		 * r = qr.matrixQR().triangularView<Upper>(); */
	}
	
	unsigned iter = 0;
	// LH3: test for completion.
	while(iter < max_iter)
	{
		while(iter < max_iter)
		{
			iter++;
			
			if(p.size() == 0)
			{
				x.fill(0);
				break;
			}
			
			// LH6: compute the positive matrix and find the min norm solution
			// of the positive problem.
			VectorXd xtmp;
			if(useqr)
				xtmp = qr.solve(d);
			else
				xtmp = Cp.jacobiSvd(ComputeThinU | ComputeThinV).solve( d );
			
			VectorXi idx = find(xtmp.array() < 0);
			if(idx.size() == 0)
			{
				// LH7: tmp solution found, iterate.
				x.fill(0);
				set_ind(x, p, xtmp);
				break;
			}
			else
			{
				// LH8, LH9: find the scaling factor.
				VectorXi pidx = pick(p, idx);
				VectorXd xpidx = pick(x, pidx);
				VectorXd sf = xpidx.array() / ( xpidx.array() - pick(xtmp, idx).array() );
				double alpha = sf.minCoeff();
				// LH10: adjust X.
				xx.fill(0);
				set_ind(xx, p, xtmp);
				
				x += alpha*(xx - x);
				// LH11: move from P to Z all X == 0.
				// This corresponds to those indices where minimum of sf is attained.
				idx = pick(idx, find(sf.array() == alpha) );
				p = remove(p, idx);
				
				// p has changed, so update c(:,p)
				Cp = pick_col(C, p);
				
				if(useqr)
				{
					// update the QR factorization.
					// [q, r] = qrdelete (q, r, idx);
					// TODO. for the moment, just re-compute QR-factorization from scratch
					
					qr = HouseholderQR<MatrixXd>(Cp);
				}
			}
		}
		
		// compute the gradient.
		VectorXd w = C.transpose() * (d - C*x);
		w = remove(w, p);
		
		bool allw_leq0 = true;
		for(unsigned i = 0; i < w.size(); ++i)
		{
			if(w(i) > 0)
			{
				allw_leq0 = false;
				break;
			}
		}
		if(allw_leq0)
		{
			if(useqr)
			{
				// verify the solution achieved using qr updating.
				// in the best case, this should only take a single step.
				useqr = false;
				continue;
			}
			else
				// we're finished.
				break;
		}

		// find the maximum gradient.
		unsigned idx = 0;
		unsigned nidx = 1;
		for(unsigned i = 1; i < w.size(); ++i)
		{
			if(w(i) > w(idx))
			{
				idx = i;
				nidx = 1;
			}
			else if(w(i) == w(idx))
				++nidx;
		}
		if(nidx > 1)
			std::cerr<<"warning: lsqnonneg:nonunique: A non-unique solution may be returned due to equal gradients"<<std::endl;
		
		unsigned zidx = idx;
		for(unsigned i = 0; i < p.size(); ++i)
		{
			if(p(i) <= zidx)
				++zidx;
			else
				break;
		}
		unsigned jdx = zidx - idx;
		
		VectorXi p2(p.size()+1);
		for(unsigned i = 0; i < jdx; ++i)
			p2(i) = p(i);
		
		p2(jdx) = zidx;
		
		for(unsigned i = jdx+1; i <= p.size(); ++i)
			p2(i) = p(i-1);
		
		p = p2;
		
		// p has changed, so update c(:,p)
		Cp = pick_col(C, p);
		
		if(useqr)
		{
			// insert the column into the QR factorization.
			// [q, r] = qrinsert (q, r, jdx, c(:,zidx));
			// TODO. for the moment, just re-compute QR-factorization from scratch
			
			qr = HouseholderQR<MatrixXd>(Cp);
		}
	}
	// LH12: complete.
	return x;
}

VectorXd lsqnonneg(const MatrixXd& C, const VectorXd& d)
{
	return lsqnonneg(C, d, VectorXd::Zero(C.cols()));
}

}

#endif // _LW_LSQNONNEG_
