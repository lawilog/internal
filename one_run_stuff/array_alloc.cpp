#include <iostream>
using namespace std;

int main()
{
	float*** a = new float**[10];
	for(int i = 0; i < 10; i++)
	{
		a[i] = new float*[20];
		for(int j = 0; j < 10; j++)
		{
			a[i][j] = new float[30];
			for(int k = 0; k < 10; k++)
			{
				a[i][j][k] = i + j + k;
			}
		}
	}
	cout << "noch da" << endl;
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			delete [] a[i][j];
		}
		delete [] a[i];
	}
	delete [] a;
	cout << "over and out" << endl;
	return 0;
}
