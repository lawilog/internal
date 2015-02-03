#include <iostream>
using namespace std;

void test(long long** p)
{
	long long* q = p[3];
	cout<< "q = " << q <<endl;
	cout<< "*q = " << *q <<endl;
}

int main()
{
	long long a[2][2] = {10, 20, 30, 40};
	cout<< "a[1][1] = " << a[1][1] <<endl;
	cout<< "a = " << a <<endl;
	cout<< "a[0] = " << a[0] <<endl;
	test((long long**)a);
	return 0;
}
