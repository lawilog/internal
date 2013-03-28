#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "LineArray.h"
using namespace std;
using namespace LW;

void process_input(istream& input, const unsigned colA, const unsigned colB, set<unsigned>& rows)
{
	unsigned l = 0;
	bool in_order = true;
	while(input.good())
	{
		++l;
		if(rows.find(l) != rows.end())
			in_order = !in_order;
		
		string buffer;
		getline(input, buffer);
		if(in_order)
			cout<<buffer<<endl;
		else
		{
			LineArray la = buffer;
			const unsigned N = la.size();
			if(colA >= N || colB >= N)
				cout<<buffer<<endl;
			else
				for(unsigned c = 0; c < N; ++c)
					cout<<' '<<la[(c != colA && c != colB) ? c : (c==colA?colB:colA)];
			cout<<endl;
		}
	}
};

int main(int argc, char* argv[])
{
	if(argc <= 4)
	{
		cout<<"usage: "<<argv[0]<<" filepath columnA coulmnB crossRowA crossRowB crossRowC...\n"
			"example: \""<<argv[0]<<" eg.dat 8 9  10 20 30\" will let data in the 9th and 10th column cross at 10th, 20th and 30th data point.\n"
			"filepath can - for standard input"<<endl;
		return 1;
	}
	const char* infilepath = argv[1];
	const unsigned colA = atoi(argv[2]);
	const unsigned colB = atoi(argv[3]);
	set<unsigned> rows;
	for(unsigned i = 4; i < argc; ++i)
		rows.insert(atoi(argv[i]));
	
	if(string(infilepath) == "-")
		process_input(cin, colA, colB, rows);
	else
	{
		ifstream infile(infilepath);
		process_input(infile, colA, colB, rows);
	}
	
	return 0;
}