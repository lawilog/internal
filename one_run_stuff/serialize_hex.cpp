#include <iostream>
#include <sstream>
using namespace std;

struct unsignedCoord
{
	unsigned x;
	unsigned y;
};

int main()
{
	unsignedCoord cord[3];
	cord[0].x = 16 * 1 + 2;
	cord[0].y = 16 * 3 + 4;
	cord[1].x = 16 * 5 + 6;
	cord[1].y = 16 * 7 + 8;
	cord[2].x = 16*16*16*9 + 16*16*10 + 16 * 11 + 12;
	cord[2].y = 16*16*13 + 16 * 14 + 15;
	
	// 21000000 43000000 65000000 87000000 cba90000 fed00000
	
	stringstream shex;
	unsigned char* p = reinterpret_cast<unsigned char*>(&cord[0]);
	
	struct lohibyte
	{
		unsigned hi : 4;
		unsigned lo : 4;
	};
	
	for(unsigned n = 0; n < 3; ++n)
	{
		for(unsigned short b = 0; b < sizeof(unsignedCoord); ++b)
		{
			lohibyte* c = reinterpret_cast<lohibyte*>(p++);
			shex << hex << c->hi;
			shex << hex << c->lo;
		}
	}	
	cout << shex.str() << endl;
	return 0;
}
