#include <iostream>
#include <cstring>
using namespace std;

class Wort
{
	private:
		unsigned len;
		char* str;
	
	public:
		Wort(const char* s)
		{
			len = strlen(s);
			str = new char[len+1];
			unsigned i = 0;
			for(; i < len; ++i)
				str[i] = s[i];
			str[i] = 0;
		}
		
		Wort(const Wort& w)
		{
			cout<< "COPY" <<endl;
			len = w.len;
			str = new char[len+1];
			unsigned i = 0;
			for(; i < len; ++i)
				str[i] = w.str[i];
			str[i] = 0;
		}
		
		~Wort()
		{
			delete [] str;
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
		
		Wort operator+(const Wort& add)
		{
			const char* add_str = add.c_str();
			const unsigned add_len = add.length();
			char* sum = new char[len + add_len + 2];
			unsigned i;
			for(i = 0; i < len; ++i)
				sum[i] = str[i];
			sum[i++] = ' ';
			for(unsigned j = 0; j < add_len; ++j, ++i)
				sum[i] = add_str[j];
			sum[i] = 0;
			
			Wort sum_wort(sum);
			return sum_wort;
		}
};

class Person
{
	private:
		Wort vorname;
		Wort nachname;
	
	public:
		Person(const Wort& _vorname, const Wort& _nachname) : vorname(_vorname), nachname(_nachname) {cout<<"Constructed."<<endl;}
		Wort getFullName()
		{
			return vorname + nachname;
		}
		
		Wort getName(bool last_first)
		{
			Wort sorum = nachname + vorname;
			Wort andersrum = vorname + nachname;
			return last_first ? sorum : andersrum;
		}
};

int main()
{
	Wort e = "echo";
	e.ausgabe();
	
	Wort f = e;
	f.ausgabe();
	
	Person p("Peter", "Muster");
	Wort name1 = p.getFullName(),
		name2 = p.getName(true);
	name1.ausgabe();
	name2.ausgabe();
	
	return 0;
}
