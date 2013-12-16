#include <iostream>
#include <vector>
using namespace std;

void output(const unsigned nbits, unsigned bitpat)
{
	for(unsigned k = 0; k < nbits; ++k)
	{
		cout<< (bitpat%2?'1':'0');
		bitpat /= 2;
	}
	cout<<endl;
}

unsigned rot(const unsigned nbits, unsigned bitpat, unsigned shift)
{
    return (bitpat << shift) | (bitpat >> (sizeof(bitpat) * nbits - shift));
}

unsigned rev(const unsigned nbits, unsigned bitpat)
{
	unsigned r = 0;
	for(unsigned k = 0; k < nbits; ++k)
	{
		r |= (bitpat%2) << (nbits-1-k);
		bitpat /= 2;
	}
	
	return r;
}

int main()
{
	const unsigned nbits = 3;
	unsigned len = 1;
	for(unsigned k = 0; k < nbits; ++k) len *= 2;
	vector<bool> ok(len);
	for(unsigned i = 0; i < len; ++i)
		ok[i] = true;
	
	for(unsigned i = 0; i < len; ++i)
	{
		if(ok[i])
		{
			cout<<"# "; output(nbits, i);
			
			unsigned r = rev(nbits, i);
			cout<<"R "; output(nbits, r);
			if(r > i) ok[r] = false;
			
			for(unsigned s = 1; s < nbits; ++s)
			{
				unsigned j = rot(nbits, i, s);
				cout<<"S "; output(nbits, j);
				if(j > i) ok[j] = false;
			}
		}
	}
	
	for(unsigned i = 0; i < len; ++i)
		if(ok[i]) output(nbits, i);
	
	return 0;
}
