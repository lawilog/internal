#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include "RandDistrib.hpp"
using namespace std;
using namespace LW;

enum interpol_method {closest, linear, quadratic};

// xtype and ytype could be double or float
template<interpol_method method, typename xtype=double, typename ytype=double>
class FunInterpolTable
{
	typedef typename map<xtype,ytype>::iterator point_iter;
	
	private:
		map<xtype,ytype> points; // store actually calculated (not interpolated) points
		ytype(*fun)(xtype); // pointer to expansive function
		xtype xperc;
		//ytype yperc;
		unsigned call_count;
		unsigned eval_count;
		
		double dist(const xtype& x0, const xtype& x1) const
		{
			double d = x1 - x0;
			return (d<0?-d:d);
		}
		
		ytype interpol_linear(const xtype& x0, const ytype& y0, const xtype& x1, const ytype& y1, const xtype& xi) const
		{
			return y1 + (xi - x1) * (y1 - y0) / (x1 - x0);
		}
		
		ytype interpol_quadratic(const xtype& x0, const ytype& y0, const xtype& x1, const ytype& y1, const xtype& x2, const ytype& y2, const xtype& xi) const
		{
			// Lagrange interpolation
			return y0 * (xi-x1)*(xi-x2)/( (x0-x1)*(x0-x2) )  +  y1 * (xi-x0)*(xi-x2)/( (x1-x0)*(x1-x2) )  +  y2 * (xi-x0)*(xi-x1)/( (x2-x0)*(x2-x1) );
		}
		
	public:
		FunInterpolTable( ytype(*_fun)(xtype))
		{
			fun = _fun;
			xperc = 1e-1;
			//yperc = 0;
			call_count = 0;
			eval_count = 0;
		}
		
		ytype eval(const xtype& x)
		{
			++eval_count;
			ytype y = fun(x);
			points.insert( pair<xtype,ytype>(x, y) );
			return y;
		}
		
		void precompute(xtype start, xtype end, unsigned npoints)
		{
			if(npoints < 2) npoints = 2;
			eval_count += npoints;
			call_count += npoints;
			for(unsigned i = 0; i < npoints; ++i)
			{
				xtype x = static_cast<xtype>(start + (end - start) * i * 1.0 / (npoints-1));
				points.insert( pair<xtype,ytype>(x, fun(x)) );
			}
		}
		
		// set x percision:
		// calculate new value if neighbor positions are farer apart than xperc
		// if xperc is 0, always interpolate -> usefull in conjunction with precompute()
		// you may also switch off evaulation at any time with setXPerc(0)
		void setXPerc(xtype xperc)
		{
			this->xperc = xperc;
		}
		
		ytype operator() (const xtype& x)
		{
			++call_count;
			
			unsigned points_needed;
			switch(method)
			{
				case closest: points_needed = 1; break;
				case linear:  points_needed = 2; break;
				case quadratic: points_needed = 3; break;
			}
			static_assert(method==closest || method==linear || method==quadratic, "Interpolation method not yet implemented.");
			
			// search points for the first position which is equal or greater than x
			point_iter geq = points.lower_bound(x);
			
			// if the exact same position was already calculated, then return the value
			if(geq != points.end() && geq->first == x)
				return geq->second;
			
			// now: interpolate or eval?
			
			// eval, if not yet enough points to interpolate
			if( points.size() < points_needed )
				return eval(x);
			
			switch(method)
			{
				case closest:
				{
					point_iter closest_point;
					if(geq == points.end()) // x is greater than all previously calculated positions
					{
						closest_point = points.end();
						--closest_point;
					}
					else if(geq == points.begin()) // x is smaller than all previously calculated positions
						closest_point = points.begin();
					else // x is somewhere in the middle
					{
						point_iter low = geq;
						--low; // geq is on right, get next point on the left
						closest_point = (dist(x, low->first) < dist(x, geq->first)) ? low : geq; // choose closer point
					}
					if(	xperc == 0 // asked to always interpolate
						||
						dist(x, closest_point->first) <= xperc // closest point is close enough
					) 
						return closest_point->second;
					// else eval
					break;
				}
				
				case linear:
				{
					point_iter p0, p1;
					if(geq == points.end()) // x is greater than all previously calculated positions
					{
						p0 = points.end(); --p0;
						p1 = p0--;
					}
					else if(geq == points.begin()) // x is smaller than all previously calculated positions
					{
						p1 = points.begin();
						p0 = p1++;
					}
					else // x is somewhere in the middle
					{
						p0 = geq;
						p1 = p0--;
					}
					if(	xperc == 0 // asked to always interpolate
						||
						(dist(x, p0->first) <= xperc && dist(x, p1->first) <= xperc) // both closest points are close enough
					)
						return interpol_linear(p0->first, p0->second, p1->first, p1->second, x);
					break;
				}
				
				case quadratic:
				{
					point_iter p0, p1, p2;
					if(geq == points.end()) // x is greater than all previously calculated positions
					{
						p0 = points.end(); --p0; // sorting afterwards: p0==last x
						p2 = p0--; // sorting afterwards: p0 p2==last x
						p1 = p0--; // sorting afterwards: p0 p1 p2==last x
					}
					else if(geq == points.begin()) // x is smaller than all previously calculated positions
					{
						p2 = points.begin(); // sorting afterwards: x p2==begin
						p0 = p2++; // sorting afterwards: x p0==begin p2
						p1 = p2++; // sorting afterwards: x p0==begin p1 p2
					}
					else // x is somewhere in the middle
					{
						p0 = geq;  // sorting afterwards: x p0
						p2 = p0--; // sorting afterwards: p0 x p2
						if(p0 == points.begin())
							p1 = p2++; // sorting afterwards: p0==begin x p1 p2
						else
						{
							p1 = p0--; // sorting afterwards: p0 p1 x p2
							point_iter m = p2++; // sorting afterwards: p0 p1 x m p2
							if( p2 == points.end() || dist(p0->first, p1->first) < dist(m->first, p2->first) ) // p0 is closer to [p1, m] interval
								p2 = m;
							else // p2 is closer to [p1, m] interval
							{
								p0 = p1;
								p1 = m;
							}
						}
					}
					if(	xperc == 0 // asked to always interpolate
						||
						(dist(x, p0->first) <= xperc && dist(x, p1->first) <= xperc && dist(x, p2->first) <= xperc) // all three closest points are close enough
					)
						return interpol_quadratic(p0->first, p0->second, p1->first, p1->second, p2->first, p2->second, x);
					break;
				}
				
				// default: static_assert(false, "Interpolation method not yet implemented.");
			}
			
			return eval(x);
		}
		
		const map<xtype,ytype>& getPoints() const {return points;}
		const unsigned getCallCount() const {return call_count;}
		const unsigned getEvalCount() const {return eval_count;}
};

int main()
{
	RandDistrib<double,uniform_real_distribution> randuni(0, 2*M_PI);
	RandDistrib<int,uniform_int_distribution> randi(0, 6);
	ofstream d0("function_interpolation_table_f0.dat"); if(! d0) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d1("function_interpolation_table_f1.dat"); if(! d1) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d2("function_interpolation_table_f2.dat"); if(! d2) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d3("function_interpolation_table_f3.dat"); if(! d3) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d4("function_interpolation_table_f4.dat"); if(! d4) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d5("function_interpolation_table_f5.dat"); if(! d4) {cerr<<"Could not write file."<<endl; return 1;}
	
	// closest
	FunInterpolTable<closest> f0(sin);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d0<< x <<"\t"<< f0(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f0, random, closest: "<< f0.getCallCount() <<" calls, "<< f0.getEvalCount() <<" evals"<<endl;
	
	// linear
	FunInterpolTable<linear> f1(sin);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d1<< x <<"\t"<< f1(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f1, random, linear: "<< f1.getCallCount() <<" calls, "<< f1.getEvalCount() <<" evals"<<endl;
	
	// precompute closest
	FunInterpolTable<closest> f2(sin);
	f2.precompute(0, 2*M_PI, 50);
	f2.setXPerc(0);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d2<< x <<"\t"<< f2(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f2, random, closest, precomputes: "<< f2.getCallCount() <<" calls, "<< f2.getEvalCount() <<" evals"<<endl;
	
	// precompute linear
	FunInterpolTable<linear> f3(sin);
	f3.precompute(0, 2*M_PI, 50);
	f3.setXPerc(0);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d3<< x <<"\t"<< f3(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f3, random, linear, precomputes: "<< f3.getCallCount() <<" calls, "<< f3.getEvalCount() <<" evals"<<endl;
	
	// cache 0 <= n <= 6 with integer n
	FunInterpolTable<closest,float,float> f4(sin);
	// f4.setXPerc(1);
	for(unsigned i = 0; i < 1000; ++i)
	{
		int x = randi();
		d4<< x <<"\t"<< f4(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f4, cache: "<< f4.getCallCount() <<" calls, "<< f4.getEvalCount() <<" evals"<<endl;
	
	
	// quadratic
	FunInterpolTable<quadratic> f5(sin);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d5<< x <<"\t"<< f5(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f5, random, quadratic: "<< f5.getCallCount() <<" calls, "<< f5.getEvalCount() <<" evals"<<endl;
	
	return 0;
}
