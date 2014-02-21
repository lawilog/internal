#include <iostream>
#include <vector>
#include <string>
using namespace std;

void swap_them(string& a, string& b)
{
	string tmp = move(a);
	a = move(b);
	b = move(tmp);
}

int main()
{
	cout<<"# move demo"<<endl;
	string foo  = "bar";
	string test = "Test";
	swap_them(foo, test);
	
	cout<<"# need for 5 copies. not more"<<endl;
	vector<string> v;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	
	cout<<"# another thing"<<endl;
	vector<string> w = {test, test, test};
	
	return 0;
}
