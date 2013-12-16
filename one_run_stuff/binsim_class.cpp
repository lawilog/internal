#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class pateq
{
	private:
		unsigned nbits;
		unsigned len;
		unsigned cut;
		vector<bool> ok;
		
	public:
		pateq(unsigned _nbits) : nbits(_nbits)
		{
			len = 1<<nbits;
			ok = vector<bool>(len, true);
			cut = ((unsigned)(-1)) >> (8*sizeof(unsigned)-nbits);
		}
		
		void output(unsigned bitpat)
		{
			for(unsigned k = 0; k < nbits; ++k)
			{
				cout<< (bitpat%2?'1':'0');
				bitpat /= 2;
			}
			cout<<endl;
		}
		
		unsigned rot(unsigned bitpat, unsigned shift)
		{
			unsigned r = 0;
			for(unsigned k = 0; k < nbits; ++k)
			{
				r |= (bitpat%2) << ((k+shift)%nbits);
				bitpat /= 2;
			}
			return r;
		}
		
		unsigned rot2(unsigned bitpat, unsigned shift)
		{
			return ( (bitpat<<shift) | (bitpat>>(nbits-shift)) ) & cut;
		}
		
		unsigned rev(unsigned bitpat)
		{
			unsigned r = 0;
			for(unsigned k = 0; k < nbits; ++k)
			{
				r |= (bitpat%2) << (nbits-1-k);
				bitpat /= 2;
			}
			return r;
		}
		
		void filter()
		{
			for(unsigned i = 0; i < len; ++i)
			{
				if(ok[i])
				{
					unsigned r = rev(i);
					if(r > i) ok[r] = false;
					
					for(unsigned s = 1; s < nbits; ++s)
					{
						unsigned j = ( (i<<s) | (i>>(nbits-s)) ) & cut; // rot2(i,s)
						if(j > i) ok[j] = false;
						
						unsigned k = ( (r<<s) | (r>>(nbits-s)) ) & cut; // rot2(r, s)
						if(k > i) ok[k] = false;
					}
				}
			}
		}
		
		void output_all()
		{
			for(unsigned i = 0; i < len; ++i)
			{
				if(ok[i])
				{
					// output(i);
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
		}
};

int main(int argc, char** argv)
{
	pateq eq(argc>1?atoi(argv[1]):3);
	eq.filter();
	eq.output_all();
	return 0;
}
