#include <fstream>
using namespace std;

int main()
{
	ofstream hDatei("datei.bin");
	for(unsigned long j=0; j<1024; j++) for(unsigned long i=0; i<100*1024; i++) hDatei<<((char)0);
	for(unsigned long j=0; j<1024; j++) for(unsigned long i=0; i<100*1024; i++) hDatei<<((char)255);
	for(unsigned long j=0; j<1024; j++) for(unsigned long i=0; i<100*1024; i++) hDatei<<((char)170);
	for(unsigned long j=0; j<1024; j++) for(unsigned long i=0; i<100*1024; i++) hDatei<<((char)0);
	for(unsigned long j=0; j<1024; j++) for(unsigned long i=0; i<100*1024; i++) hDatei<<((char)255);
	for(unsigned long j=0; j<1024; j++) for(unsigned long i=0; i<50*1024; i++) hDatei<<((char)0)<<((char)255);
	for(unsigned long j=0; j<1024; j++) for(unsigned long i=0; i<100*1024; i++) hDatei<<((char)210);
	hDatei.close();
	return 0;
}
