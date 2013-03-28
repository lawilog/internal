#ifndef _LW_IMPLODE_EXPLODE_
#define _LW_IMPLODE_EXPLODE_

#include <vector>
#include <string>

std::string implode(const std::string& delim, const std::vector<std::string>& vstr);
std::vector<std::string> explode(const std::string& delim, const std::string& str);

#endif // _LW_IMPLODE_EXPLODE_
