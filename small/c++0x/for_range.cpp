#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void ausgabe(int& x)
{
	cout<< x << endl;
}

int main()
{
	int array[] = {7, 23, 42, 1337};
	/* c++98
	const unsigned len = sizeof(array) / sizeof(int);
	for(int i = 0; i < len; ++i)
		cout<< array[i] <<endl;
	
	for_each(array, array+4, ausgabe);
	*/
	
	for(int& x : array)
		cout<< x <<endl;
	
	vector<int> vec = {7, 23, 42, 1337};
	for(int& x : vec)
		cout<< x <<endl;
	
	for_each(vec.begin(), vec.end(), ausgabe);
	
	return 0;
}
