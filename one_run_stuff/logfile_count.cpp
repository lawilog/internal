#include <fstream>
#include <pthread.h>
using namespace std;

int main()
{
	ofstream outfile("logfile.txt");
	for(int i=0; i<15; ++i)
	{
		outfile<< i <<endl;
		sleep(1);
	}
	outfile.close();
	return 0;
}

