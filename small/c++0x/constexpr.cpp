#include <iostream>
using namespace std;

constexpr unsigned bytecount(unsigned bits)
{
	return (bits % 8 == 0 ? bits/8 : 1 + bits/8);
}

constexpr unsigned fak(unsigned n)
{
	return (n == 0 ? 1 : n * fak(n-1));
}

// constexpr unsigned index(unsigned n, unsigned i, unsigned j)
// {
// 	return 100 + (n * i + j);
// }
// 
// unsigned index(unsigned n, unsigned i, unsigned j)
// {
// 	return (n * i + j);
// }

int main()
{
	const unsigned my_bits = 42;
	int array[bytecount(my_bits)];
	cout<< bytecount(my_bits) <<endl;
	
	int bad_idea[bytecount(0)];
	
	cout << "5 ! = " << fak(5) << endl;
	
// 	unsigned j = 2;
// 	cout << index(10, 4, j) << endl;
// 	cin >> j;
// 	cout << index(10, 4, j) << endl;
	
	return 0;
}
