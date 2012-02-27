#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	const unsigned n = 1000000;
	short* a = new short[n];
	int s = 0;
	for(unsigned i = 0; i < n; ++i)
		s += a[i] = rand() % 9 - 4;
	double m = s * 1.0 / n;
	double stddev = 0.0;
	for(unsigned i = 0; i < n; ++i)
	{
		double d = a[i] - m;
		stddev += d * d;
	}
	stddev /= (n-1);
	cout << "m = " << m << endl;
	cout << "stddev = " << stddev << endl;
	delete [] a;
	return 0;
}
