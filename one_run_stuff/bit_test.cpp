#include <iostream>
#include <cstring>
using namespace std;

// typedef short : 1 bit;

struct test
{
	unsigned bar : 1;
};

struct apfel
{
	unsigned b0 : 1;
	unsigned b1 : 1;
	unsigned b2 : 1;
	unsigned b3 : 1;
	unsigned b4 : 1;
	unsigned b5 : 1;
	unsigned b6 : 1;
	unsigned b7 : 1;
};

struct birne
{
	unsigned a : 1 [8];
};

int main()
{
	test foo[8];
	memset(&foo, 0, sizeof(foo));
	foo[0].bar = 1;
	foo[7].bar = 1;
	unsigned char* hammer = reinterpret_cast<unsigned char*>(foo);
	unsigned drauf = *hammer;
	cout << "array of structs = " << drauf << endl;
	
	/*bit sodum[8];
	sodum[0] = 1;
	sodum[7] = 1;
	hammer = reinterpret_cast<unsigned char*>(sodum);
	drauf = *hammer;
	cout << "array of typedef bits = " << drauf << endl;*/
	
	apfel torte;
	memset(&torte, 0, sizeof(apfel));
	torte.b0 = 1;
	torte.b7 = 1;
	hammer = reinterpret_cast<unsigned char*>(& torte);
	drauf = *hammer;
	cout << "struct with names = " << drauf << endl;
	
	return 0;
}
