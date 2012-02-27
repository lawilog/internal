#include <iostream>
using namespace std;

int main()
{
	unsigned short c = 130;
	for(unsigned short i = 0; i < 9; ++i)
	{
		cout << (c ^ (1<<i) ) << endl;
	}
	return 0;
}
