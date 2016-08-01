#ifndef _LW_VOUT_
#define _LW_VOUT_

#include <iostream>
#include <valarray>

namespace LW {

template<class T>
void vout(std::ostream& os, const std::valarray<T>& v, const std::string& seperator=" ")
{
	if(v.size() > 0)
	{
		os<< v[0];
		for(size_t i = 1; i < v.size(); ++i)
			os << seperator << v[i];
	}
}

template<class T> std::ostream& operator<<(std::ostream& os, const std::valarray<T>& v)
{
	if(v.size() > 0)
	{
		os<< v[0];
		for(size_t i = 1; i < v.size(); ++i)
			os << ' ' << v[i];
	}
	// os << '\n';
	return os;
}

/*
valarray<int> v = {42, 23, 1, 7};
cout<<"[ "; vout(cout, v); cout<<" ]"<<endl;
vout(cout, v, ", "); cout<<endl;
cout<< v <<endl;
*/

}

#endif // _LW_VOUT_
