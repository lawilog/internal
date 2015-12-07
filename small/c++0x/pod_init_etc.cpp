#include <iostream>
using namespace std;

struct Punkt
{
	double x;
	double y;
	double z;
};

void printPunkt(Punkt p)
{
	cout << "( " << p.x << " , " << p.y << " , " << p.z << ")" << endl;
}

void aufDenSchirm(initializer_list<int> L)
{
	cout << L.size() << endl;
	for(auto x : L)
		cout << x << endl;
}

int main()
{
	printPunkt( {0, 1, 2} );
	
	Punkt* A = new Punkt {4, 5, 6};
	
	aufDenSchirm( {10, 20, 30} );
	
	int* array = new int[3] {10, 20, 30};
	
	delete [] array;
	delete A;

	int n {42};
	int m {2.3};
	
	return 0;
}
