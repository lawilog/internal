#include <iostream>
using namespace std;

int main()
{
	char s16[]="0123456789ABCDEF";
	char sCmd[]="echo -n \"XX .\";echo XX | hex2bin;echo \".\"";
	for(short i=0; i<16; ++i)
	{
		for(short j=0; j<16; ++j)
		{
			sCmd[9]=s16[i];  sCmd[20]=s16[i];
			sCmd[10]=s16[j]; sCmd[21]=s16[j];
			system(sCmd);
		}
	}
	return 0;
}
/*18
1A
20..7E
A1..FF
*/
