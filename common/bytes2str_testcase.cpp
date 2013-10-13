#include <iostream>
#include "bytes2str.hpp"
using namespace std;
using namespace LW;

int main()
{
	const unsigned long long sizes[] = {42, 1000, 1024, 1000000, 1048576, 9876543, 3400000000, 56000000000000, 7890000000000000};
	for(auto s: sizes)
		cout<< s << " bytes are \""<< bytes2str(s) <<"\""<<endl;

	return 0;
}
