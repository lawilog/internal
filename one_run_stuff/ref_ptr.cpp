#include <iostream>
using namespace std;

int* foo;

int main()
{
	foo = new int;
	*foo = 7;
	int* temp = foo;
	int& foo = *temp;
	foo = 3;
	cout << "foo = " << foo << endl;
//	cout << "bar = " << bar << endl;
	delete temp;
	return 0;
}
