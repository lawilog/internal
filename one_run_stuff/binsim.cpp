#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv)
{
	unsigned nbits = argc>1?atoi(argv[1]):3;
	unsigned len = 1<<nbits;
	unsigned cut = ((unsigned)(-1)) >> (8*sizeof(unsigned)-nbits);
	vector<bool> ok(len, true);
	
	for(unsigned i = 0; i < len; ++i)
	{
		if(ok[i])
		{
			unsigned ii = i;
			unsigned r = 0;
			for(unsigned k = 0; k < nbits; ++k)
			{
				r |= (ii%2) << (nbits-1-k);
				ii /= 2;
			}
			if(r > i) ok[r] = false;
			
			for(unsigned s = 1; s < nbits; ++s)
			{
				unsigned j = ( (i<<s) | (i>>(nbits-s)) ) & cut;
				if(j > i) ok[j] = false;
				
				unsigned k = ( (r<<s) | (r>>(nbits-s)) ) & cut;
				if(k > i) ok[k] = false;
			}
		}
	}
	
	for(unsigned i = 0; i < len; ++i)
	{
		if(ok[i])
		{
			unsigned ii = i;
			for(unsigned k = 0; k < nbits; ++k)
			{
				cout<< (ii%2?'1':'0');
				ii /= 2;
			}
			cout<<'\n';
		}
	}
	cout<<flush;
	return 0;
}
