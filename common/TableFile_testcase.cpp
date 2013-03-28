#include <iostream>
#include "TableFile.h"
using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout<<"usage: "<<argv[0]<<" table.dat"<<endl;
		return 1;
	}
	const char* infilepath  = argv[1];
	
	TableFileAsNeeded tab(infilepath);
	const unsigned linecount = tab.line_count();
	
	cout<<endl;
	for(unsigned ln = 1; ln <= linecount; ++ln)
	{
		cout<< ln <<" > \""<< tab.line(ln) <<"\""<<endl;
	}
	
	cout<<endl;
	for(unsigned ln = 1; ln <= linecount; ++ln)
	{
		//cout<< ln <<" > \""<< tab.lineM(ln) <<"\""<<endl;
	}
	
	cout<<endl;
	for(unsigned ln = 1; ln <= linecount; ++ln)
	{
		cout<< ln <<"[0] = \""<< tab.line_col(ln, 0) <<"\""<<endl;
	}
	
	cout<<endl;
	for(unsigned ln = 1; ln <= linecount; ++ln)
	{
		cout<<"double("<< ln <<"[0]) = "<< tab.line_col<double>(ln, 0) <<endl;
	}
	
	// TableFileToRam forbidden_copy = tab; // provokes wanted compile error
	
	
	TableFileAsNeeded tab2(infilepath);
	const unsigned linecount2 = tab2.line_count();
	
	cout<<endl;
	for(unsigned ln = 1; ln <= linecount2; ++ln)
	{
		cout<< ln <<" > \""<< tab2.line(ln) <<"\""<<endl;
	}
	
	cout<<endl;
	for(unsigned ln = 1; ln <= linecount2; ++ln)
	{
		cout<< ln <<"[0] = \""<< tab2.line_col(ln, 0) <<"\""<<endl;
	}
	
	cout<<endl;
	for(unsigned ln = 1; ln <= linecount2; ++ln)
	{
		cout<<"double("<< ln <<"[0]) = "<< tab2.line_col<double>(ln, 0) <<endl;
	}
	
	return 0;
}

