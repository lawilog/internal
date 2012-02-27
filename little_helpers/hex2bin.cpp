#include <iostream>
using namespace std;

int main()
{
	char i=0;
	char sBuf[2]={0,0};
	while(cin.good())
	{
		char c=cin.get();
		if(c=='\n') break;
		if('0'<=c&&c<='9') sBuf[i]=c-'0';
		else if('A'<=c&&c<='F') sBuf[i]=10+c-'A';
		else if('a'<=c&&c<='f') sBuf[i]=10+c-'a';
		else continue;
		if(i==1)
		{
			i=0;
			cout<<((char)(16*sBuf[0]+sBuf[1]));
			sBuf[0]=0; sBuf[1]=0;
		}
		else i=1;
	}
	return 0;
}
