#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	char s16[]="0123456789ABCDEF";
	unsigned short i=0;
	while(i<64)
	{
		int r=rand()%256;
		if((32<=r && r<=126) || (161<=r && r<=255))
		{
			cout<<s16[r/16]<<s16[r%16]<<' ';
			++i;
		}
	}
	cout<<endl;
	return 0;
}
