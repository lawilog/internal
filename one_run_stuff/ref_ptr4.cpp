#include <iostream>
using namespace std;

class FolgenPtr
{
	private:
		int* ptr;
	public:
		FolgenPtr() {}
		FolgenPtr(int* _ptr, unsigned len) : ptr(_ptr) {}
		int* get() {return ptr;}
		void set(int* _ptr) {ptr = _ptr;}
		int& operator[](unsigned i)
		{
			// TODO: maybe check if i<len
			return ptr[i];
		}
};

class SammelKlasse
{
	private:
		int dummy;
		FolgenPtr a;
		FolgenPtr b;
	public:
		SammelKlasse(int dumm, FolgenPtr aa, FolgenPtr bb)
		{
			dummy = dumm;
			a.set(aa.get());
			b.set(bb.get());
		}
		void do_something()
		{
			cout << "a[0] = " << a[0] << endl;
			cout << "b[0] = " << b[0] << endl;
		}
};

int main()
{
	int real_data_A[5] = {10, 11, 12, 13, 14}; // stored only once, here.
	int real_data_B[5] = {20, 21, 22, 23, 24}; // stored only once, here.
	FolgenPtr A(real_data_A, 5);
	FolgenPtr B(real_data_B, 5);
	SammelKlasse S(42, A, B);
	S.do_something();
	return 0;
}
