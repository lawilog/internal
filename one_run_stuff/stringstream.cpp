#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	string test="foo 42 bar";
	stringstream file(test);
	file<<"abc";
	cout<<file.str()<<endl;
	cout<<test<<endl;
	return 0;
}
