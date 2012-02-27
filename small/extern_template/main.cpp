#include <iostream>
#include "rect.h"
using namespace std;

int main()
{
	Rect<int> r(1, 2, 3, 4);
	cout << r.area() << endl;
	return 0;
}
