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
			cout<<"default constructing "<< (s ? s : "<empty string>") <<endl;
			len = 0; while(s[len++] != 0);
			str = new char[len];
			for(unsigned i = 0; i < len; ++i)
				str[i] = s[i];
		}
		
		mystring(const mystring& w) : len(0), str(NULL)
		{
			cout<<"copy constructing "<< (w.str ? w.str : "<empty string>") <<" using "<<flush;
			*this = w;
		}
		
		mystring& operator=(const mystring& w)
		{
			if(&w != this) // do not assign object to itself
			{
				cout<<"copy assigning "<< (w.str ? w.str : "<empty string>") <<endl;
				
				// delete existing memory
				delete [] str;
				
				len = w.len;
				str = (len? new char[len] : NULL);
				for(unsigned i = 0; i < len; ++i)
					str[i] = w.str[i];
			}
			return *this;
		}
		
		mystring(mystring&& w) noexcept : len(0), str(NULL)
		{
			cout<<"move constructing "<< (w.str ? w.str : "<empty string>") <<" using "<<flush;
			*this = std::move(w);
		}
		
		mystring& operator=(mystring&& w) noexcept
		{
			if(&w != this) // do not assign object to itself
			{
				cout<<"move assigning "<< (w.str ? w.str : "<empty string>") <<endl;
				
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
		
		void print() const
		{
			if(str!=NULL) cout<< str <<endl;
		}
};

void swap_them(mystring& a, mystring& b)
{
	mystring tmp = move(a);
	a = move(b);
	b = move(tmp);
}

//vector<mystring> gimme(mystring w, bool b)
vector<mystring> gimme(const mystring& w, bool b)
{
	cout<<"# v"<<endl;
	vector<mystring> v;
	v.push_back(w);
	
	cout<<"# u"<<endl;
	vector<mystring> u(3);// = {w, w, w};
	// u.reserve(3);
	u[0] = w; u[1] = w; u[2] = w;
	// u.push_back(w); u.push_back(w); u.push_back(w);
	
	cout<<"# return"<<endl;
	return move(b ? u : v);
	// return b ? u : v;
}

int main()
{
	cout<<"# construct"<<endl;
	mystring test = "Test";
	mystring foo  = "Foo";
	
	cout<<"# move demo"<<endl;
	swap_them(test, foo);
	
	cout<<"# go"<<endl;
	vector<mystring> x = gimme(test, true);

	cout<<"# ausgabe:"<<endl;
	for(mystring& w: x)
		w.print();
	
	cout<<"# need for 5 copies. not more"<<endl;
	vector<mystring> v;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	v.push_back(foo); cout<< v.size() <<" : "<< v.capacity() <<endl;
	
	cout<<"# another thing"<<endl;
	vector<mystring> z = {test, test, test};
	
	cout<<"# clean up"<<endl;
	
	return 0;
}
