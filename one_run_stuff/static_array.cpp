#include <iostream>
using namespace std;

int main()
{
	int a;
	cin >> a;
	// int* b = new int[a];
	int b[a];
	for(int i = 0; i < a; i++) b[i] = i;
	cout << "a = " << a << endl;
	for(int i = 0; i < a; i++) cout << b[i] << endl;
	// delete [] b;
	return 0;
}
