#include <iostream>
#include <fstream>
#include "TableFile.h"
#include "parse.hpp"
using namespace std;
using namespace LW;

int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		cout<<"usage: "<<argv[0]<<" in_blockdata.xy N out_block_N.nxy [nli]\n"
		      "\twill extract block N from in_blockdata.xy and write it to out_block_N.nxy\n"
		      "\tfirst block has N = 1\n"
		      "\tif nli is supplied, these number of lines (at the start) will be ignored"<<endl;
		return 1;
	}
	const char* in_filepath  = argv[1];
	const unsigned N         = parse<unsigned>(argv[2]);
	const char* out_filepath = argv[3];
	const unsigned nli       = (argc > 4 ? parse<unsigned>(argv[4]) : 0);
	
	TableFileAsNeeded in_file(in_filepath);
	const unsigned nlines = in_file.line_count();
	unsigned l = nli + 1;
	while(l <= nlines && in_file.line_col(l, 0) != "") ++l; // find first empty line
	const unsigned lines_per_block = l - nli;
	const unsigned start_line = nli + lines_per_block * (N-1) + 1;
	const unsigned end_line   = nli + lines_per_block * N - 1;
	
	/*cout<<"nlines = "<< nlines <<endl;
	cout<<"l = "<< l <<endl;
	cout<<"nli = "<< nli <<endl;
	cout<<"lines_per_block = "<< lines_per_block <<endl;
	cout<<"start_line = "<< start_line <<endl;
	cout<<"end_line = "<< end_line <<endl;*/
	
	if(end_line > nlines)
	{
		cerr<<"ERROR: There is no block "<< N <<". "
		      "(Found "<< lines_per_block <<" lines per block.) "
			  "It would end at "<< end_line <<", but file has only "<< nlines <<" lines."<<endl;
		return 1;
	}
	ofstream out_file(out_filepath);
	if(! out_file)
	{
		cerr<<"ERROR: Could not open file \""<<out_filepath<<"\" for reading."<<endl;
		return 1;
	}
	for(l = start_line; l <= end_line; ++l)
		out_file << in_file.line(l) << "\n";
	
	out_file.close();
	
	return 0;
}
