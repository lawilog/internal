#include <iostream>
using namespace std;

void removeLinebreaksFromStr(char* src, char* dst)
{
	for(; *src != 0; ++src) if(*src != '\n') *(dst++) = *src;
	*dst = 0;
}

int main()
{
	char foo[]="Das \nist \nein Test\n.";
	char bar[64];
	cout<<"foo = "<<foo<<endl;
	removeLinebreaksFromStr(foo, bar);
	cout<<"bar = "<<bar<<endl;
	removeLinebreaksFromStr(foo, foo);
	cout<<"foo = "<<foo<<endl;
	return 0;
}
