#include "implode_explode.h"
using namespace std;

namespace LW {

string implode(const string& delim, const vector<string>& vstr)
{
	if(vstr.empty())
		return string();
	
	const unsigned len = vstr.size();
	size_t req_size = (len - 1) * delim.length();
	for(const string& elem: vstr)
		req_size += elem.length();
	
	string s;
	s.reserve(req_size);
	s.assign(vstr.front());
	for(unsigned i = 1; i < len; ++i)
	{
		s.append(delim);
		s.append(vstr[i]);
	}
	
	return s;
}

vector<string> explode(const string& delim, const string& str)
{
	vector<string> v;
	size_t pos_beg = 0, pos_end;
	while(pos_beg < str.length())
	{
		pos_end = str.find(delim, pos_beg);
		v.push_back(str.substr(pos_beg, pos_end - pos_beg));
		if(pos_end == string::npos) break;
		else pos_beg = pos_end + delim.length();
	}
	return v;
}

}
