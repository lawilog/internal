#include <iostream>
#include <valarray>
using namespace std;

int main()
{
	valarray<double> a = {1, 2, 3};
	valarray<double> b = {4, 5, 6};
	valarray<double> c = a + b;
	valarray<double> d(3);
	d = a - c + b;
	cout<<"c: ";
	for(size_t i=0; i<c.size(); ++i)
		cout<<c[i]<<" ";
	
	cout<<"\nd: ";
	for(size_t i=0; i<d.size(); ++i)
		cout<<d[i]<<" ";
	
	cout<<endl;
	return 0;
}
