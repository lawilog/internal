#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<typename... Args>
string strprintf(const char* format, const Args&... args)
{
	const int static_len = 1024;
	char static_buffer[static_len]; // in static memory
	char* buffer = & static_buffer[0];
	int len = snprintf(buffer, static_len, format, args...);
	if(len < 0) return string(); // on error, return empty string
	if(len >= static_len) // we need more space
	{
		buffer = new char[len]; // allocate on heap
		sprintf(buffer, format, args...);
		string str(buffer, len);
		delete [] buffer;
		return str;
	}
	else return string(buffer, len); // everything went fine
}

template<typename... Args>
int fprintf(ostream& out_stream, const char* format, const Args&... args)
{
	string buffer = strprintf(format, args...);
	out_stream.write(buffer.c_str(), buffer.length());
}

void wout() {}

template<typename T, typename... Args>
void wout(T value, Args... args)
{
	std::cout<< value;
	wout(args...);
}

void woutn()
{
	std::cout<<std::endl;
}

template<typename T, typename... Args>
void woutn(T value, Args... args)
{
	std::cout<< value;
	woutn(args...);
}

int main()
{
	string test = strprintf("%5.2f\n", 1.234567);
	cout<< test <<endl;
	
	ofstream fp("foobar.txt");
	fprintf(fp, "%5.2f\n", 1.234567);
	fp.close();
	
	wout("Hello ", 42, " world", '!', '\n');
	woutn("another", " test: ", 1.234567);
	
	return 0;
}
