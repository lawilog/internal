#include <iostream>
#include <vector>
using namespace std;

template<class T>
void vout(ostream& os, const vector<T>& v, const string& seperator=" ")
{
	if(! v.empty())
	{
		os<< v.front();
		for(auto p = v.begin() + 1; p != v.end(); ++p)
			os << seperator << *p;
	}
}

template<class T> ostream& operator<<(ostream& os, const vector<T>& v)
{
	if(! v.empty())
	{
		os<< v.front();
		for(auto p = v.begin() + 1; p != v.end(); ++p)
			os << ' ' << *p;
	}
	os << '\n';
	return os;
}

int main()
{
	vector<int> v = {42, 23, 1, 7};
	cout<<"[ "; vout(cout, v); cout<<" ]"<<endl;
	vout(cout, v, ", "); cout<<endl;
	cout<< v <<endl;
	return 0;
}
