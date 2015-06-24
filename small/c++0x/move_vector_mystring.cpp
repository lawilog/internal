#include <iostream>
#include <vector>
using namespace std;

class mystring
{
	private:
		unsigned len;
		char* str;
	
	public:
		mystring() : len(0), str(NULL) {}
		
		mystring(const char* s)
		{
			len = 0; while(s[len++] != 0);
			str = new char[len];
			for(unsigned i = 0; i < len; ++i)
				str[i] = s[i];
		}
		
		mystring(const mystring& w) : len(0), str(NULL)
		{
			*this = w;
		}
		
		mystring& operator=(const mystring& w)
		{
			if(&w != this) // do not assign object to itself
			{
				if(w.len != len)
				{
					// delete existing memory
					delete [] str;
					
					len = w.len;
					str = (len? new char[len] : NULL);
				}
				for(unsigned i = 0; i < len; ++i)
					str[i] = w.str[i];
			}
			return *this;
		}
		
		mystring(mystring&& w) noexcept : len(0), str(NULL)
		{
			*this = std::move(w);
		}
		
		mystring& operator=(mystring&& w) noexcept
		{
			if(&w != this) // do not assign object to itself
			{
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
		
		~mystring()
		{
			delete [] str;
		}
};

void swap_them(mystring& a, mystring& b)
{
	mystring tmp = move(a);
	a = move(b);
	b = move(tmp);
}

int main()
{
	cout<<"# move demo"<<endl;
	mystring foo  = "bar";
	mystring test = "Test";
	swap_them(foo, test);
	
	cout<<"# need for 5 copies. not more"<<endl;
	vector<mystring> v;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	
	cout<<"# another thing"<<endl;
	vector<mystring> w = {test, test, test};
	
	return 0;
}
