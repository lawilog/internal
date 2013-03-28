#include "LineArray.h"
#include <cstring>
#include <iostream>
using namespace std;
using namespace LW;

LineArray::LineArray(const string& cline) : line(cline)
{
	init();
}

LineArray::LineArray(istream& in_stream)
{
	getline(in_stream, line);
	init();
}

void LineArray::init()
{
	bool in_white_space = true;
	const unsigned len = line.length();
	for(unsigned i = 0; i < len; ++i)
	{
		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		{
			line[i] = 0;
			in_white_space = true;
		}
		else if(in_white_space)
		{	// first non-white space
			in_white_space = false;
			columns.push_back(i);
		}
	}
}

string LineArray::col(int column) const
{
	const int ncol = columns.size();
	if(column < -ncol || column >= ncol)
		return "";
	
	return &line[columns[column >= 0 ? column : ncol + column]];
}

std::ostream& LW::operator<<(std::ostream& os, const LineArray& la)
{
	const unsigned N = la.size();
	if(N > 0)
	{
		os<< la[0];
		for(unsigned i = 1; i < N; ++i)
			os<<" "<< la[i];
	}
	return os;
}

/*****************************************************************************/

string LW::getColumnFromLine(const char* line, int wanted_column)
{
	char *start, *end;
	if(wanted_column >= 0)
	{
		int cur_colmn = 0;
		char* pos = const_cast<char*>(line);
		start = end = pos;
		bool in_white_space = true;
		while(*pos != 0)
		{
			if(*pos == ' ' || *pos == '\t' || *pos == '\n')
			{
				if(! in_white_space)
				{	// this is the first white space
					in_white_space = true;
					if(cur_colmn == wanted_column)
					{	// the first whitespace after the column we want, so finish here
						end = pos;
						break;
					}
					++cur_colmn;
				}
				
				if(cur_colmn == wanted_column) // white space, column we want is coming up. probably starting at next char
					start = pos + 1;
			}
			else // no longer in white space
				in_white_space = false;
			
			++pos;
		}
		
		if(end == line)
		{	// we hit the end of the line without terminating white space
			end = pos; // so copy till the end
			
			if(cur_colmn != wanted_column) // column was not found
				start = end; // so return empty string
		}
	}
	else
	{
		int cur_colmn = -1;
		bool in_white_space = true;
		
		char* pos = const_cast<char*>(line);
		start = pos;
		while(*pos != 0 && *pos != '\n')
			++pos; // go to the end of the line
		
		end = pos;
		
		while(pos >= line)
		{
			if(*pos == ' ' || *pos == '\t' || *pos == '\n')
			{
				if(! in_white_space)
				{	// this is the first white space
					in_white_space = true;
					if(cur_colmn == wanted_column)
					{	// the first whitespace before the column we want, so finish here
						start = pos+1;
						break;
					}
					--cur_colmn;
				}
				
				if(cur_colmn == wanted_column) // white space after the column we want. probably ending at this char
					end = pos;
			}
			else // no longer in white space
				in_white_space = false;
			
			--pos;
		}
		
		if(pos <= line && cur_colmn != wanted_column) // column was not found
			end = start; // so return empty string
	}
	
	string r(start, end);
	return r;
}
