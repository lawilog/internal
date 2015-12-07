#include <iostream>
#include <vector>
using namespace std;

class X
{
	private:
		vector<int> v;

	public:
	X()
	{
		unsigned n; cin >> n;
		v = vector<int>(n);
	}

	void outsize() {cout<< v.size() <<endl;}
};

int main()
{
	X x;
	x.outsize();
	return 0;
}
