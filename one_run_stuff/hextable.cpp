#include <iostream>
using namespace std;

int main()
{
	for(unsigned short x = 0; x < 16; ++x)
	{
		for(unsigned short y = 0; y < 16; ++y)
		{
			cout<<' '; cout<<hex<<(x*y);
		}
		cout<<endl;
	}
	return 0;
}
