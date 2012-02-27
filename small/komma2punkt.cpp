#include <fstream>
#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char** argv)
{
	if(argc<=1)
	{
		cout<<"Datei auf Programm draggen & droppen. [Enter druecken]"<<endl;
		getchar();
		return 1;
	}
	fstream datei(argv[1]);
	if(! datei)
	{
		cerr<<"Datei \""<<argv[1]<<"\" nicht gefunden. [Enter druecken]"<<endl;
		getchar();
		return 1;
	}
	while(! datei.eof())
	{
		char c = datei.get();
		if(c == ',')
		{
			datei.seekp(datei.tellg() - (streamoff)1);
			datei.put('.');
			datei.seekp(0);
		}
	}
	datei.close();
	return 0;
}
