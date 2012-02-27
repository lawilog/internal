#include <iostream>
using namespace std;

class foo
{
	private:
	int x;

	public:
	foo(int i) {cout<<"construct "<<i<<endl; x=i;}
	~foo() {cout<<"deconstruct "<<x<<endl;}
};

int main()
{
	foo** bar;
	const int n=10;
	bar = new foo*[n];
	foo magic(42);
	for(int i=0; i<n; ++i)
	{
		(*bar[i])(&magic);
	}
	cout<<"foobar"<<endl;
	for(int i=0; i<n; ++i)
	{
		delete bar[i];
	}
	return 0;
}
