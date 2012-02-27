#include <iostream>
#include <string>
using namespace std;

class test
{
	private:
	int a;
	int b;
	int c;
	public:
	test(int a, int b);
	int sum();
};

test::test(int a, int b)
{
	this -> a = a;
	this -> b = b;
}

int test::sum()
{
	return a+b;
}

int main()
{
	test foo(3,4);
	cout << "sum = " << foo.sum() << endl;
	cout << "sizeof(foo) = " << sizeof(foo) << endl;
	cout << "sizeof(string) = " << sizeof(string) << endl;
	return 0;
}