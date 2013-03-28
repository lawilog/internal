#ifndef _LW_LINEARRAY_
#define _LW_LINEARRAY_

#include <string>
#include <vector>
#include <iostream>
#include "parse.hpp"

namespace LW {

// Use this stand-alone C-style function when you only need one column.
// Only the wanted column will be extracted and written to a new string.
std::string getColumnFromLine(const char* line, int wanted_column);


// Use this class when you need multiple columns from one line.
// (will duplicate line to own memory)
class LineArray
{
	private:
		std::string line; 
		std::vector<unsigned> columns;
		void init();
		
	public:
		LineArray(const std::string& cline);
		LineArray(std::istream& in_stream); // construct from next line
		
		// column < 0 means from the end. [-1] is last element
		
		std::string col(int column) const;
		
		std::string operator[](int column) const {
			return col(column);
		}
		
		template<class T> T col(int column) const {
			return parse<T>(col(column));
		}
		
		unsigned size() const {
			return columns.size();
		}
		
		// enable cast to vector<string>
		operator std::vector<std::string>() const
		{
			const unsigned N = columns.size();
			std::vector<std::string> vs;
			vs.reserve(N);
			for(unsigned i = 0; i < N; ++i)
				vs.push_back(col(i));
			
			return vs;
		}
};

// enable cout etc.
std::ostream& operator<<(std::ostream& os, const LineArray& LA);

}

#endif // _LW_LINEARRAY_
