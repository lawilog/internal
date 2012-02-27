#include <iostream>
using namespace std;

class parent
{
	public:
	virtual void helper() {cout<<"parent helper"<<endl;}
	void big_function() {cout<<"parent big_function"<<endl; helper();}
	void other_functionallity();
};

class child : public parent
{
	public:
	void helper() {cout<<"child helper"<<endl;}
};

int main()
{
	child c;
	c.big_function();
	return 0;
}
