#include <iostream>
using namespace std;

int main()
{
	const unsigned n = 100;
	bool xs = false;
	do
	{
		bool ys = false;
		do
		{
			bool zs = false;
			do
			{
				cout << (xs?1:0) << (ys?1:0) << (zs?1:0) << ": ";
				unsigned counter = 0;
				
				for(unsigned x = 0; x < n; x += 1)
				{
					for(unsigned y = 0; y < n; y += 1)
					{
						for(unsigned z = 0; z < n; z += 1)
						{
							double avg = (x+y+z)/3.0;
							if(xs == x>avg && ys == y>avg && zs == z>avg)
								++counter;
							//	cout << "  ("<<x<<" "<<y<<" "<<z<<")";
						}
					}
				}
				
				cout << counter;
				cout << endl;
				
				if(zs) break;
				else zs = true;
			}  while(true);
			
			
			if(ys) break;
			else ys = true;
		} while(true);
		
		if(xs) break;
		else xs = true;
	} while(true);
	return 0;
}
