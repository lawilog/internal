#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> foo(string s)
{
	vector<string> u;
	for(unsigned i = 0; i < 500; ++i)
		u.push_back(s);
	
	vector<string> v;
	for(unsigned i = 0; i < 100*s.length(); ++i)
		v.push_back(s);
	
	return (s.length() < 5 ? u : v);
}

void bar(string s, vector<string>& w)
{
	vector<string> u;
	for(unsigned i = 0; i < 500; ++i)
		u.push_back(s);
	
	vector<string> v;
	for(unsigned i = 0; i < 100*s.length(); ++i)
		v.push_back(s);
	
	w = (s.length() < 5 ? u : v);
}

int main()
{
	string s; cin>>s;
	//vector<string> w = foo(s);
	vector<string> w; bar(s, w);
	cout<< w.size() << endl;
	return 0;
}
