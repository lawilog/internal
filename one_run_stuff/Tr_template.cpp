#include <iostream>
#include <cmath>
using namespace std;

template<class T>
class Tr
{
	private:
	T (*f)(T);
	T x;
	
	public:
	Tr(T (*_f)(T), T _x) : f(_f), x(_x) {};
	T operator() (T y) {return f(x+y);}
};

int main()
{
	Tr<double> mycos(sin, M_PI/2);
	cout<< mycos(0) <<endl;
	return 0;
}
