#include <iostream>
using namespace std;

void f(char* s) {cout<< s <<endl;}

int main()
{
	f(NULL);
	cout.clear();
	cout<<"ok"<<endl;
	return 0;
}
