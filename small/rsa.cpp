#include <iostream>
//#include <cmath>
using namespace std;

struct dst3
{
	int d;
	int s;
	int t;
};

dst3 ext_eucl(int a, int b)
{
	if(b == 0)
	{
		dst3 dst = {a, 1, 0};
		return dst;
	}
	else
	{
		dst3 dst = ext_eucl(b, a % b);
		int temp_s = dst.s;
		dst.s = dst.t;
		dst.t = temp_s - dst.t * ((int)(a/b));
		return dst;
	}
}

int main()
{
	int p = 11, q = 13;
	int phi = (p-1) * (q-1);
	dst3 dst = ext_eucl(23, 120);
	cout << "d = " << dst.d << ", s = " << dst.s << ", t = " << dst.t << endl;
	return 0;
}
