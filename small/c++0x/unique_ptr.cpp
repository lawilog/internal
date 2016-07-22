#include <iostream>
#include <memory>
using namespace std;

class Base
{
	public:
	int x;
	virtual void hello() = 0;
	Base(int _x) : x(_x) {};
};

class A : public Base
{
	public:
	int a;
	void hello() {cout<<"Hello A "<< x << " "<< a <<endl;}
	A(int _x, int _a): Base(_x), a(_a) {};
};

class B : public Base
{
	public:
	int b;
	void hello() {cout<<"Hello B "<< x << " "<< b <<endl;}
	B(int _x, int _b): Base(_x), b(_b) {};
};

int main()
{
	unique_ptr<Base> p;
	int c; cin >> c;
	if(c==1) p = unique_ptr<Base>(new A(2, 3));
	else     p = unique_ptr<Base>(new B(5, 7));
	p->hello();
	return 0;
}
