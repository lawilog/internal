#include <map>
#include <string>
#include <fstream>
namespace LW {

enum interpol_method {closest, linear, quadratic};

// xtype and ytype could be double or float
template<interpol_method method, typename xtype=double, typename ytype=double>
class FunInterpolTable
{
	typedef typename std::map<xtype,ytype>::iterator point_iter;
	
	private:
		std::map<xtype,ytype> points; // store actually calculated (not interpolated) points
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
		
		void save(const std::string& filename)
		{
			std::ofstream f(filename.c_str());
			if(! f)
				throw "ERROR: Could not open file \""+filename+"\" for writing.";
			
			for(point_iter p = points.begin(); p != points.end(); ++p)
			{
				f<< p->first <<" "<< p-> second <<"\n";
			}
		}
		
		void load(const std::string& filename, bool clear=false) // clear=true means delete existing data
		{
			std::ifstream f(filename.c_str());
			if(! f)
				throw "ERROR: Could not open file \""+filename+"\" for reading.";
			
			if(clear)
				points.clear();
			
			xtype x; ytype y;
			while(f.good())
			{
				f >> x;
				if(! f.good()) break;
				f >> y;
				points.insert( std::pair<xtype,ytype>(x, y) );
			}
		}
		
		ytype eval(const xtype& x)
		{
			++eval_count;
			ytype y = fun(x);
			points.insert( std::pair<xtype,ytype>(x, y) );
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
				points.insert( std::pair<xtype,ytype>(x, fun(x)) );
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
		
		const std::map<xtype,ytype>& getPoints() const {return points;}
		const unsigned getCallCount() const {return call_count;}
		const unsigned getEvalCount() const {return eval_count;}
};

}
