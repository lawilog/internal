#include <iostream>
using namespace std;

class A
{
	public:
		A() {cout << "A()" << endl;}
		A(int a) {cout << "A(" << a << ")" << endl;}
		~A() {cout << "~A()" << endl;}
};

class B : public A
{
	public:
		B(int a, int b=7) : A(a) {cout << "B(" << b << ")" << endl;}
		~B() {cout << "~B()" << endl;}
};

class C : public A
{
	public:
		C(int c, int d) {cout << "C(" << c << ", " << d << ")" << endl;}
		~C() {cout << "~C()" << endl;}
};

int main()
{
	// A a(3);
	B b(2);
	C(5, 7);
	return 0;
}
