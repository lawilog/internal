#ifndef _LW_PRINTFPP_
#define _LW_PRINTFPP_

#include <fstream>
#include <string>
using namespace std;

template<typename... Args>
std::string strprintf(const char* format, const Args&... args)
{
	const int static_len = 1024;
	char static_buffer[static_len]; // in static memory
	char* buffer = & static_buffer[0];
	int len = snprintf(buffer, static_len, format, args...);
	if(len < 0) return string(); // on error, return empty string
	if(len >= static_len) // we need more space
	{
		buffer = new char[len]; // allocate on heap
		sprintf(buffer, format, args...);
		std::string str(buffer, len);
		delete [] buffer;
		return str;
	}
	else return std::string(buffer, len); // everything went fine
}

template<typename... Args>
void fprintf(std::ostream& out_stream, const char* format, const Args&... args)
{
	std::string buffer = strprintf(format, args...);
	out_stream.write(buffer.c_str(), buffer.length());
}

#endif // _LW_PRINTFPP_
