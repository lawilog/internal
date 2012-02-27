#include <iostream>
#include <cstring>
using namespace std;

class Folge
{
	private:
		int* data;
		unsigned len;
		
	public:
		Folge(int* src, unsigned length)
		{
			cout<<"construct from data"<<endl;
			len = length;
			data = new int[len];
			memcpy(data, src, sizeof(int)*len);
		}
		
		Folge(const Folge& orig)
		{
			cout<<"copy construct"<<endl;
			this->len = orig.len;
			this->data = new int[len];
			memcpy(data, orig.data, sizeof(int)*len);
		}
		
		~Folge()
		{
			delete [] data;
		}
		
		int& operator[](unsigned i)
		{
			return data[i];
		}
};

class FolgePtr
{
	private:
		Folge* ptr;
	public:
		FolgePtr(Folge* _ptr) : ptr(_ptr) {}
		int& operator[](unsigned i)
		{
			return (*ptr)[i];
		}
};

void that_would_be_stupid(Folge F)
{
	cout << "bad: data was copied" << endl;
	cout << "F[0] = " << F[0] << endl;
}

void we_are_smarter(Folge* F)
{
	cout << "better: use pointer" << endl;
	cout << "(*F)[0] = " << (*F)[0] << endl;
}

void trying_to_avoid_three_symbols(FolgePtr F)
{
	cout << "only pointer was copied" << endl;
	cout << "F[0] = " << F[0] << endl;
}

void even_better(Folge& F)
{
	cout << "C++ programmers would prefer this" << endl;
	cout << "F[0] = " << F[0] << endl;
}

int main()
{
	int test[5] = {10, 11, 12, 13, 14};
	Folge A(test, sizeof(test)/sizeof(int));
	that_would_be_stupid(A);
	we_are_smarter(& A);
	trying_to_avoid_three_symbols(&A);
	even_better(A);
	return 0;
}
