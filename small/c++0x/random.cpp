#include <iostream>
#include <random>
#include <functional>
using namespace std;

int main()
{
	/*
	uniform_int_distribution<int> distribution(0, 99);
	mt19937 engine; // Mersenne twister MT19937
	auto generator = bind(distribution, engine);
	int random = generator();  // Generate a uniform integral variate between 0 and 99.
	int random2 = distribution(engine); // Generate another sample directly using the distribution and the engine objects.
	*/
	
	normal_distribution<double> N(0, 1);
	mt19937 mersenne_twister;
	auto randn = bind(N, mersenne_twister);
	
	const unsigned n_boxes = 20;
	unsigned histogram[n_boxes];
	for(unsigned& x: histogram) x = 0;
	
	const double box_width = 0.3;
	const double cutoff = box_width*( (n_boxes-1)/2 );
	for(unsigned i = 0; i < 10000; ++i)
	{
		double r = randn();
		if( r < -cutoff )
			++histogram[0];
		else if( r > cutoff )
			++histogram[n_boxes-1];
		else
			++histogram[(unsigned)(r/box_width + n_boxes/2)]; // MAYBE NONSENSE !!
	}
	
	for(unsigned& x: histogram)
		cout<<' '<<x;
	cout<<endl;
	
	return 0;
}
