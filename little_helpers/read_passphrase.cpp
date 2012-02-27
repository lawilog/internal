#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <termios.h>
//#include <curses.h> 
using namespace std;

void deface_buffer(char* buffer, unsigned size)
{
	// overwrite buffer 100 times with random numbers
	for(short j = 0; j < 100; ++j)
		for(unsigned i = 0; i < size; ++i)
			buffer[i] = rand() % 256;
	// set buffer memory to zero
	memset(buffer, 0, sizeof(char)*size);
}

char hidden_getch()
{
	// like getch(), but disable output of typed-in chars
	struct termios old_term;
	struct termios new_term;
	char c;
	if(tcgetattr(0, &old_term) == -1) return -1;
	new_term = old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	if(tcsetattr(0, TCSANOW, &new_term) == -1) return -1;
	c = getchar();
	(void) tcsetattr(0, TCSANOW, &old_term);
	return c;
}

int main()
{
	// init. random number generator
	srand(time(0));
	
	// allocate 8 byte buffer firstly, still empty
	unsigned n = 8, filled = 0;
	char* passphrase = new char[n];
	
	cout<<"Enter passphrase: "<<flush;
	
	// read user input (single keystrokes)
	char c;
	while(c = hidden_getch())
	{
		// if we have not enough memory to save this keystorke, then double memory buffer
		if(filled + 1 >= n)
		{
			// create new buffer
			char* new_buffer = new char[2*n];
			// copy old contents to new buffer
			memcpy(new_buffer, passphrase, sizeof(char)*n);
			// deface and delete old buffer
			deface_buffer(passphrase, n);
			delete [] passphrase;
			// remember new buffer
			passphrase = new_buffer;
			n *= 2;
		}
		// save keystroke
		passphrase[filled] = c;
		++filled;
		// new lines marks end
		if(c == '\n') break;
	}
	cout<<endl;
	
	
	// add terminating \0
	if(filled < n) // this should always be true, since we have left one extra char above
	{
		passphrase[filled] = '\0';
		const char cmd_proto[] = "echo \"%s\" | cryptsetup luksOpen /dev/sda marx "
		                      "&& echo \"%s\" | cryptsetup luksOpen /dev/sdb engels "
		                      "&& echo \"%s\" | cryptsetup luksOpen /dev/sdc luxemburg "
		                      "&& echo \"%s\" | cryptsetup luksOpen /dev/sdd liebknecht "
		                      "&& mount /dev/mapper/marx /mnt/marx "
		                      "&& mount /dev/mapper/engels /mnt/engels "
		                      "&& mount /dev/mapper/luxemburg /mnt/luxemburg "
		                      "&& mount /dev/mapper/liebknecht /mnt/liebknecht ";
		// if you change the cmd_proto, you have to change the following line as well not to risk buffer overflows
		unsigned cmd_len = sizeof(cmd_proto)/sizeof(char) + 4*filled;
		char* cmd = new char[cmd_len];
		sprintf(cmd, cmd_proto, passphrase, passphrase, passphrase, passphrase);
		system(cmd);
		deface_buffer(cmd, cmd_len);
		delete [] cmd;
	}
	else return 1;
	deface_buffer(passphrase, n);
	delete [] passphrase;
	return 0;
}
