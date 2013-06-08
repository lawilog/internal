#ifndef _LW_PRINTFPP_
#define _LW_PRINTFPP_

#include <fstream>
#include <string>

namespace LW {

template<typename... Args>
std::string strprintf(const char* format, const Args&... args)
{
	const int static_len = 1024;
	char static_buffer[static_len]; // in static memory
	int len = snprintf(static_buffer, static_len, format, args...);
	if(len < 0) return std::string(); // on error, return empty string
	if(len >= static_len) // we need more space
	{
		char* buffer = new char[len]; // allocate on heap
		sprintf(buffer, format, args...);
		std::string str(buffer, len);
		delete [] buffer;
		return str;
	}
	else return std::string(static_buffer, len); // everything went fine
}

template<typename... Args>
void fprintf(std::ostream& out_stream, const char* format, const Args&... args)
{
	std::string buffer = strprintf(format, args...);
	out_stream.write(buffer.c_str(), buffer.length());
}

}

#endif // _LW_PRINTFPP_
