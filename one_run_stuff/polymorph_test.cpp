#include <iostream>
using namespace std;

class Data
{
	public:
		virtual ~Data() {}
		int x;
};

class Verifier
{
	public:
		virtual bool verify(Data* d) = 0;
		// LAME! for every special data type:
		virtual bool verify(class specialData* d) {}
};

class specialData : public Data
{
	public:
		int y;
};

class specialVerifierA : public Verifier
{
	public:
		bool verify(Data* d)
		{
			cout << ":-/ specialVerifierA "<< d->x <<" >= 0 ?"<<endl;
			return (d -> x >= 0);
		}
		bool verify(specialData* s)
		{
			cout << ":-) specialVerifierA "<< s->x <<" >= 0 && " << s->y << " >= 0 ?"<<endl;
			return (s -> x >= 0 && s -> y >= 0);
		}
};

class specialVerifierB : public Verifier
{
	public:
		bool verify(Data* d)
		{
			cout << ":-/ specialVerifierB "<< d->x <<" < 100 ?"<<endl;
			return (d -> x < 100);
		}
		bool verify(specialData* s)
		{
			cout << ":-) specialVerifierB "<< s->x <<" < 100 && " << s->y << " < 100 ?"<<endl;
			return (s -> x < 100 && s -> y < 100);
		}
};

class Checker
{
	private:
		Verifier* v;
		Verifier* w;
	
	public:
		Checker(Verifier* vv, Verifier* ww) {v = vv; w = ww;}
		bool check(Data* d)
		{
			specialData* s = dynamic_cast<specialData*>(d);
			if(s)
			{
				cout << "checking specialData" << endl;
				return (v -> verify(s) && w -> verify(s));
			}
			else
			{
				cout << "checking Data" << endl;
				return (v -> verify(d) && w -> verify(d));
			}
		}
};

int main()
{
	specialVerifierA A;
	specialVerifierB B;
	
	Checker C(&A, &B);
	specialData S;
	S.x = 23;
	S.y = 42;
	cout << ( C.check(&S) ? "jo" : "ne" ) << endl;
	
	Data* d = & S;
	specialData* s = dynamic_cast<specialData*>(d);
	
	return 0;
}
