#include <iostream>
#include <fstream>
using namespace std;

template<typename... Args>
int fprintf(ostream& out_stream, const char* format, const Args&... args)
{
	const int default_len = 1024;
	char* buffer = new char[default_len];
	int len = snprintf(buffer, default_len, format, args...);
	do
	{
		if(len < 0) break; // on error, dont write anything
		if(len >= default_len) // we need more space
		{
			delete [] buffer; // reallocate
			buffer = new char[len];
			sprintf(buffer, format, args...); // and write again
		}
		out_stream.write(buffer, len);
	} while(false);
	delete [] buffer;
	return len;
}

int main()
{
	ofstream fp("foobar.txt");
	fprintf(fp, "%5.2\n", 1.234567);
	fp.close();
	return 0;
}
