#include <iostream>
using namespace std;

bool bPlusOne(bool* x, unsigned n, unsigned iPos)
{
	if(iPos<0 || iPos>=n) return false;
	if(x[iPos]==false)
	{
		x[iPos]=true;
		return true;
	}
	else
	{
		x[iPos]=false;
		return bPlusOne(x, n, iPos+1);
	}
}

int main()
{
	unsigned n;
	// cout<<"How many vars?"<<endl; cin>>n;
	n=4;
	bool* x=new bool[n];
	for(unsigned i=0; i<n; ++i) x[i]=false;
	do
	{
		for(unsigned i=0; i<n; ++i) cout<<' '<<(x[i]?'1':'0');
		cout<<'\t'<<( ! (x[3] && (x[1] || x[0]) && !(x[2] && (x[1] || x[0]))));
		cout<<'\t'<<( !x[3] || x[2] || (!x[0] && !x[1]));
		cout<<'\t'<<( (!x[0] || x[2] || !x[3]) && (!x[1] || x[2] || !x[3]) );
		cout<<'\t'<<( !x[3] || (!x[1] && !x[0]) || (x[1] && x[2]) || (x[0] && x[2]) );
		cout<<endl;
	} while(bPlusOne(x, n, 0));
	delete [] x;
	return 0;
}
