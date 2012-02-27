#include <iostream>
using namespace std;

int main()
{
	int a = 0, b = 1;
	for(int i = 0; i < 32; ++i)
	{
		if(i % 3 == 0)
			++a;
		if(i % 5 == 0)
			b += a;
	}
	return 0;
}
