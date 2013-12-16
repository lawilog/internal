#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class pateq
{
	private:
		unsigned nbits;
		unsigned len;
		vector<bool> ok;
		
	public:
		pateq(unsigned _nbits) : nbits(_nbits)
		{
			len = 1;
			for(unsigned k = 0; k < nbits; ++k) len *= 2;
			
			ok.resize(len);
			for(unsigned i = 0; i < len; ++i)
				ok[i] = true;
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
					//cout<<"# "; output(i);
					unsigned r = rev(i);
					if(r > i)
					{
						//cout<<"R "; output(r);
						ok[r] = false;
					}
					
					for(unsigned s = 1; s < nbits; ++s)
					{
						unsigned j = rot(i, s);
						if(j > i)
						{
							//cout<<"S "; output(j);
							ok[j] = false;
						}
						
						unsigned k = rot(r, s);
						if(k > i)
						{
							//cout<<"T "; output(j);
							ok[k] = false;
						}
					}
				}
			}
		}
		
		void output_all()
		{
			for(unsigned i = 0; i < len; ++i)
				if(ok[i]) output(i);
		}
};

int main(int argc, char** argv)
{
	pateq eq(argc>1?atoi(argv[1]):3);
	eq.filter();
	eq.output_all();
	return 0;
}
