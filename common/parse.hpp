#ifndef _LW_PARSE_
#define _LW_PARSE_

#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

namespace LW {

template<class T> T parse(const std::string& str)
{
	if(str.length() == 0)
		return T();
	else
	{
		T output;
		std::stringstream ss(str, std::stringstream::in);
		ss >> output;
		return output;
	}
}

template<class T> T parse(const char* str)
{
	if(str == NULL || str[0] == 0)
		return T();
	else
	{
		T output;
		std::stringstream ss(str, std::stringstream::in);
		ss >> output;
		return output;
	}
}

template <> inline
double parse<double>(const char* str)
{
	return atof(str);
}

template <> inline
int parse<int>(const char* str)
{
	return atoi(str);
}

template <> inline
long parse<long>(const char* str)
{
	return atol(str);
}


template<class T> std::vector<T> parse(const std::vector<char*>& vstr)
{
	std::vector<T> v;
	v.reserve(vstr.size());
	for(char* const& str: vstr)
		v.push_back(parse<T>(str));
	return v;
}

template<class T> std::vector<T> parse(const std::vector<std::string>& vstr)
{
	std::vector<T> v;
	v.reserve(vstr.size());
	for(const std::string& str: vstr)
		v.push_back(parse<T>(str));
	return v;
}

}

#endif // _LW_PARSE_

