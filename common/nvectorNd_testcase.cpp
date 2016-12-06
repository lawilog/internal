#include <vector>
#include <array>
#include "nvectorNd.hpp"
using namespace std;
using namespace LW;

int main()
{
	nvectorNd<double,3> v({5, 7, 8});
	v[1][2][3] = 4.0;
	std::vector<std::vector<double> >& y = v[0];
	
	v[2].at(999)[1] = 2.3;
	return 0;
}
