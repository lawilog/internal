#ifndef _LW_VOUT_
#define _LW_VOUT_

#include <iostream>
#include <vector>
#include <array>

namespace LW {

template<class T>
void vout(std::ostream& os, const std::vector<T>& v, const std::string& seperator=" ")
{
	if(! v.empty())
	{
		os<< v.front();
		for(typename std::vector<T>::const_iterator p = v.begin() + 1; p != v.end(); ++p)
			os << seperator << *p;
	}
}

template<class T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	if(! v.empty())
	{
		os<< v.front();
		for(typename std::vector<T>::const_iterator p = v.begin() + 1; p != v.end(); ++p)
			os << ' ' << *p;
	}
	// os << '\n';
	return os;
}

template<class T, std::size_t N >
void vout(std::ostream& os, const std::array<T,N>& v, const std::string& seperator=" ")
{
	if(! v.empty())
	{
		os<< v.front();
		for(typename std::array<T,N>::const_iterator p = v.begin() + 1; p != v.end(); ++p)
			os << seperator << *p;
	}
}

template<class T, std::size_t N >
std::ostream& operator<<(std::ostream& os, const std::array<T,N>& v)
{
	if(! v.empty())
	{
		os<< v.front();
		for(typename std::array<T,N>::const_iterator p = v.begin() + 1; p != v.end(); ++p)
			os << ' ' << *p;
	}
	// os << '\n';
	return os;
}

/*
vector<int> v = {42, 23, 1, 7};
cout<<"[ "; vout(cout, v); cout<<" ]"<<endl;
vout(cout, v, ", "); cout<<endl;
cout<< v <<endl;
*/

}

#endif // _LW_VOUT_
