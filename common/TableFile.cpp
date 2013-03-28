#include "TableFile.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "LineArray.h"
using namespace std;
using namespace LW;

TableFileToRam::TableFileToRam(const char* filepath)
{
	// read in data to memory
	ifstream table_file(filepath);
	if(! table_file)
	{
		cerr<<"ERROR: Could not open file \""<<filepath<<"\" for reading."<<endl;
		throw;
	}
	table_file.seekg(0, ios::end);
	const unsigned file_size = table_file.tellg();
	table_file.seekg(0, ios::beg);
	data.resize(file_size + 2);
	table_file.read(& data[0], file_size);
	table_file.close();
	data[file_size] = '\n';
	data[file_size+1] = 0;
	
	unsigned lastlinestart = 0;
	for(unsigned i = 0; i < file_size+1; ++i)
	{
		if(data[i] == '\n')
		{
			data[i] = 0;
			lines.push_back(lastlinestart);
			lastlinestart = i+1;
		}
	}
}

const char* TableFileToRam::lineM(unsigned LN) const
{
	if(LN !=0 && LN <= lines.size())
		return &data[lines[LN-1]];
	else
	{
		cerr<<"ERROR: File does not have line number "<<LN<<endl;
		return & data.back();
	}
}

string TableFileToRam::line(unsigned LN)
{
	if(LN !=0 && LN <= lines.size())
		return (string)(&data[lines[LN-1]]);
	else
	{
		cerr<<"ERROR: File does not have line number "<<LN<<endl;
		return "";
	}
}

string TableFileToRam::line_col(unsigned LN, int column)
{
	return getColumnFromLine(lineM(LN), column);
}

unsigned TableFileToRam::line_count() const
{
	return lines.size();
}

/*****************************************************************************/

TableFileAsNeeded::TableFileAsNeeded(const char* filepath)
{
	// read in data once to get line start positions
	table_file.open(filepath);
	if(! table_file)
	{
		cerr<<"ERROR: Could not open file \""<<filepath<<"\" for reading."<<endl;
		throw;
	}
	streampos lastlinestart = ios::beg;
	while(table_file.good())
	{
		if(table_file.get() == '\n')
		{
			lines.push_back(lastlinestart);
			lastlinestart = table_file.tellg(); // here, get pointer is one after '\n'
		}
	}
}
		
std::string TableFileAsNeeded::line(unsigned LN)
{
	if(LN !=0 && LN <= lines.size())
	{
		unsigned line_len;
		if(LN == lines.size())
		{	// last line
			table_file.seekg(0, ios::end);
			line_len = table_file.tellg() - lines[LN-1];
		}
		else
			line_len = lines[LN] - lines[LN-1];
		
		string line_n;
		line_n.reserve(line_len+1);
		table_file.clear();
		table_file.seekg(lines[LN-1]);
		getline(table_file, line_n);
		return line_n;
	}
	else
	{
		cerr<<"ERROR: File does not have line number "<<LN<<endl;
		return "";
	}
	
}

string TableFileAsNeeded::line_col(unsigned LN, int column)
{
	return getColumnFromLine(this->line(LN).c_str(), column);
}

unsigned TableFileAsNeeded::line_count() const
{
	return lines.size();
}

