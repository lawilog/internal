#include <iostream>
using namespace std;

class Wort
{
	private:
		unsigned len;
		char* str;
	
	public:
		Wort(const char* s)
		{
			cout<<"default constructing "<< s <<endl;
			len = 0; while(s[len++] != 0);
			str = new char[len];
			for(unsigned i = 0; i < len; ++i)
				str[i] = s[i];
		}
		
		Wort(const Wort& w) : len(0), str(NULL)
		{
			cout<<"copy constructing "<< w.str <<endl;
			*this = w;
		}
		
		Wort& operator=(const Wort& w)
		{
			if(&w != this) // do not assign object to itself
			{
				cout<<"copy assigning "<< w.str <<endl;
				
				// delete existing memory
				delete [] str;
				
				len = w.len;
				str = new char[len];
				for(unsigned i = 0; i < len; ++i)
					str[i] = w.str[i];
			}
			return *this;
		}
		
		Wort(Wort&& w) : len(0), str(NULL)
		{
			cout<<"move constructing "<< w.str <<endl;
			*this = std::move(w);
		}
		
		Wort& operator=(Wort&& w)
		{
			if(&w != this) // do not assign object to itself
			{
				cout<<"move assigning "<< w.str <<endl;
				
				// delete existing memory
				delete [] str;
				
				// move
				len = w.len;
				str = w.str;
				
				// prevent w's destrcutor to delete memory
				w.len = 0;
				w.str = NULL;
			}
			return *this;
		}
		
		~Wort()
		{
			if(str != NULL)
			{
				cout<<"deleting "<< str <<endl;
				delete [] str;
			}
		}
		
		const char* c_str() const
		{
			return str;
		}
		
		unsigned length() const
		{
			return len;
		}
		
		void ausgabe() const
		{
			cout<< str <<endl;
		}
};

void vertrausche(Wort& a, Wort& b)
{
	Wort tmp = a;
	a = b;
	b = tmp;
}

void vertrausche_move(Wort& a, Wort& b)
{
	Wort tmp = move(a);
	a = move(b);
	b = move(tmp);
}

int main()
{
	Wort e = "echo";
	Wort h = "hallo";
	cout<<"e = "; e.ausgabe();
	
	vertrausche(e, h);
	cout<<"e = "; e.ausgabe();
	
	vertrausche_move(e, h);
	cout<<"e = "; e.ausgabe();
	
	return 0;
}
