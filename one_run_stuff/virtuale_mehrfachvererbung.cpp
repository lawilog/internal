#include <iostream>

using namespace std;

class baseA
{
	public:
		virtual void out() {cout<<"A"<<endl;}
};

class baseB
{
	public:
		virtual void out() {cout<<"B"<<endl;}
};

class derivedC : public baseA
{
	public:
		void out() {baseA::out(); cout<<"C"<<endl;}
};

class derivedD : public baseA, public baseB
{
	public:
		void out() {baseA::out(); baseB::out(); cout<<"D"<<endl;}
};


int main()
{
	baseA A;
	derivedC C;
	derivedD D;
	
	cout << "-A-" << endl;
	C.out();
	
	cout << "-C-" << endl;
	C.out();
	
	cout << "-D-" << endl;
	D.out();
	
	return 0;
}
