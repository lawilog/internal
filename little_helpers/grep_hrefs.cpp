#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void process_input(istream& input)
{
	const string href="href", HREF="HREF";
	string link;
	int state = 0; // start in state 0
	char term_char='"';
	while(input.good())
	{
		char c = input.get();
		if(0 <= state && state < 4) // search (case-insensitive) for "href" -> afterwards: state = 4
		{
			if(c==href[state] || c==HREF[state]) ++state;
			else state = 0;
		}
		else if(state == 4) // wait for next '=', but '>' resets
		{
			if(c=='=') ++state;
			else if(c=='>') state = 0;
		}
		else if(state == 5) // wait for next '"', but '>' resets
		{
			if(c=='"')
			{
				++state;
				link = "";
			}
			else if(c=='>') state = 0;
		}
		else if(state == 6)
		{
			if(c == term_char)
			{
				cout<< link <<endl;
				state = 0;
			}
			else link += c;
		}
	}
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		ifstream f(argv[1]);
		process_input(f);
	}
	else
		process_input(cin);
	
	return 0;
}
