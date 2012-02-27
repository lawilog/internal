#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

/*                ___---|     + h = 0.2
       ___...--'''      |     |
Source -----------------|     0

<------- z = 1 --------->
*/

int main()
{
	// compare: real simulation, I/r^2 only, cos-corrected
	const double h = 0.5;
	const double rand_max = (double)RAND_MAX;
	const unsigned bin_count = 100;
	const unsigned simluation_runs = 10000;
	unsigned bins[bin_count];
	for(unsigned i = 0; i < bin_count; ++i) bins[i] = 0;
	const double rand_f = atan(h) / rand_max;
	
	for(unsigned i = 0; i < simluation_runs; ++i)
	{
		double alpha = rand_f * rand();
		//cout << alpha << endl;
		double x_hit = tan(alpha);
		if(x_hit < h)
		{
			// cout << "bin " << (unsigned)(bin_count*x_hit/h) << endl;
			++bins[(unsigned)(bin_count*x_hit/h)];
		}
	}
	ofstream dat("martin_cos_test.dat");
	for(unsigned i = 0; i < bin_count; ++i) dat << i << '\t' << bins[i] << endl;
	dat.close();
	cout<<endl;
	return 0;
}
