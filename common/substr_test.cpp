#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s = " k-point   95 :   -0.45454545-0.27272727 0.00000000     weight = 0.00826446";
	string kx = s.substr(18, 11);
	string ky = s.substr(29, 11);
	string kz = s.substr(40, 11);
	cout<< kx <<endl;
	cout<< ky <<endl;
	cout<< kz <<endl;
	return 0;
}
