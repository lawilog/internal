#include <iostream>
#include <string>
#include "LineArray.h"
using namespace std;
using namespace LW;

int main()
{
	LineArray la("zero one two three four five sex seven");
	for(int i = -9; i < 9; ++i)
		cout<<"la["<<i<<"] = \""<< la[i] <<"\""<<endl;
	
	LineArray la2("  ZERO ONE   TWO  THREE \n");
	for(int i = -5; i < 5; ++i)
		cout<<"la2["<<i<<"] = \""<< la2[i] <<"\""<<endl;
	
	LineArray la3("");
	for(int i = -2; i < 2; ++i)
		cout<<"la3["<<i<<"] = \""<< la3[i] <<"\""<<endl;
	
	LineArray la4(" ");
	for(int i = -2; i < 2; ++i)
		cout<<"la4["<<i<<"] = \""<< la4[i] <<"\""<<endl;
	
	for(int i = -4; i < 4; ++i)
		cout<<i<<" \""<<getColumnFromLine("aa bb cc", i)<<"\""<<endl;
	
	for(int i = -4; i < 4; ++i)
		cout<<i<<" \""<<getColumnFromLine("a b c\n", i)<<"\""<<endl;
	
	for(int i = -4; i < 4; ++i)
		cout<<i<<" \""<<getColumnFromLine("aa\t bb   \t   cc", i)<<"\""<<endl;
	
	for(int i = -4; i < 4; ++i)
		cout<<i<<" \""<<getColumnFromLine("  x    yyy  z", i)<<"\""<<endl;
	
	for(int i = -2; i < 2; ++i)
		cout<<i<<" \""<<getColumnFromLine("", i)<<"\""<<endl;
	
	for(int i = -2; i < 2; ++i)
		cout<<i<<" \""<<getColumnFromLine(" ", i)<<"\""<<endl;
	
	
	LineArray la5("  1  2.3   foo bar	4.567  8e-1");
	for(int i = 0; i < 7; ++i)
		cout<<"string(la5["<<i<<"]) = \""<< la5.col<string>(i) <<"\""<<endl;
	
	for(int i = 0; i < 7; ++i)
		cout<<"double(la5["<<i<<"]) = "<< la5.col<double>(i) <<endl;
	
	return 0;
}
