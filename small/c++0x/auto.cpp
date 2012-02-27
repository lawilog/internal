#include <iostream>
#include <vector>
using namespace std;

int main()
{
	/* c++98
	vector<string> vec;
	vec.push_back("this");
	vec.push_back("is");
	vec.push_back("a");
	vec.push_back("test");
	for(vector<string>::iterator p = vec.begin(); p != vec.end(); ++p)
		cout<< *p <<endl;
	*/
	
	vector<string> vec = {"this", "is", "a", "test"};
	for(auto p = vec.begin(); p != vec.end(); ++p)
		cout<< *p <<endl;
	
	struct punkt {double x; double y;};
	punkt p = {1.0, 2.5};
	auto a = 5, b = p;
	cout<< "a = "<< a << " b = ("<< b.x <<", "<< b.y <<")"<<endl;
	
	int n = 3;
	decltype(n) m = n-1;
	cout<< (1/m) <<endl;
	
	return 0;
}
