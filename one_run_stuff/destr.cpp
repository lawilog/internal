#include <iostream>
using namespace std;

class B
{
	private:
		int b;

	public:
		B(int bb) {b=bb; cout<<"B() "<<b<<endl;}
		B() {b=0; cout<<"B() "<<b<<endl;}
		~B() {cout<<"~B() "<<b<<endl;}
};

class A
{
	private:
		int a;
		class B myB;

	public:
		A(int aa) {a=aa; cout<<"A() "<<a<<endl;}
		~A() {cout<<"~A() "<<a<<endl;}
};

int main()
{
	A(1);
	return 0;
}

