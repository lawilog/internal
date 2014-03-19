#include <iostream>
#include <string>
using namespace std;

int SQL(constexpr string& s);

int main()
{
	SQL("foo");
	string bar;
	cin>>bar;
	SQL(bar);
	return 0;
}
