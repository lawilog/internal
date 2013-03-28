#ifndef _LW_TABLEFILE_
#define _LW_TABLEFILE_

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "parse.hpp"

// LN is line number, starting from 1 !
// but column is starting from 0

class TableFile
{
	public:
		TableFile() {}
		virtual ~TableFile() {}
		TableFile(const TableFile& nocopy) = delete;
		TableFile& operator=(const TableFile& noasignment) = delete;
		
		virtual unsigned line_count() const = 0;
		virtual std::string line(unsigned LN) = 0;
		virtual std::string line_col(unsigned LN, int column) = 0;
};

class TableFileToRam : public TableFile
{
	private:
		std::vector<char> data;
		std::vector<unsigned> lines;
		
	public:
		TableFileToRam(const char* filepath);
		
		unsigned line_count() const;
		std::string line(unsigned LN);
		const char* lineM(unsigned LN) const;
		std::string line_col(unsigned LN, int column);
		
		template<class T> inline
		T line_col(unsigned LN, int column) {
			return LW::parse<T>(line_col(LN, column));
		}
};

class TableFileAsNeeded : public TableFile
{
	private:
		std::ifstream table_file;
		std::vector<std::streampos> lines;
		
	public:
		TableFileAsNeeded(const char* filepath);
		
		unsigned line_count() const;
		std::string line(unsigned LN);
		std::string line_col(unsigned LN, int column);
		
		template<class T> inline
		T line_col(unsigned LN, int column) {
			return LW::parse<T>(line_col(LN, column));
		}
};

#endif // _LW_TABLEFILE_

