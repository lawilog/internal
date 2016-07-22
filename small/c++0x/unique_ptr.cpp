#include <iostream>
#include <memory>
using namespace std;

class Base
{
	public:
	int x;
	virtual void hello() = 0;
	Base(int _x) : x(_x) {};
	virtual ~Base() {cout<<"~Base()"<<endl;}
};

class A : public Base
{
	public:
	int a;
	void hello() {cout<<"Hello A "<< x << " "<< a <<endl;}
	A(int _x, int _a): Base(_x), a(_a) {}
	~A() {cout<<"~A()"<<endl;}
};

class B : public Base
{
	public:
	int b;
	void hello() {cout<<"Hello B "<< x << " "<< b <<endl;}
	void onlyB() {cout<<"only B can do this"<<endl;}
	B(int _x, int _b): Base(_x), b(_b) {}
	~B() {cout<<"~B()"<<endl;}
};

int main()
{
	unique_ptr<Base> p;
	cout<<"1? "; int c; cin >> c;
	if(c==1) p = unique_ptr<Base>(new A(2, 3));
	else
	{
		B* pb = new B(5, 7);
		pb -> onlyB();
		p = unique_ptr<B>(pb);
		// p = move(unique_ptr<B>(pb));
	}
	p->hello();
	return 0;
}
