#include <iostream>
#include <cstring>
using namespace std;

class C
{
	private:
		char* myName;
	
	public:
		C(const char* name) {cout<<"C() "<<name<<endl; myName=new char[strlen(name)+1]; strcat(myName, name); cout<<"done C()"<<endl;}
		~C() {cout<<"~C() "<<flush; cout<<myName<<endl; delete [] myName; cout<<"done ~C()"<<endl;}
		char* getPrivateMem() {return myName;}
};


class D
{
	private:
		class C* c;
	public:
		D() {cout<<"D()"<<endl; c = new C("test");}
		~D() {cout<<"~D()"<<endl;}
		class C* getMyC() {return c;}
};

int main()
{
	cout<<"0 here we go"<<endl;
	{
		C ccc("foo");
		char* n = ccc.getPrivateMem();
		// delete [] n; WOULD CAUSE LATER CRASH on ccc.~C()
	}
	cout<<"1 here we go"<<endl;

	cout<<"2 here we go"<<endl;
	{
		D ddd;
		C* dsc = ddd.getMyC();
		char* nn = dsc -> getPrivateMem();
		delete [] nn;
	}
	cout<<"3 here we go"<<endl;
	return 0;
}
