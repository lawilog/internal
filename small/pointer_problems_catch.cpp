#include <iostream>
// #include "../common/ThrowMemoryAccessViolations.hpp"
#include <csignal>
#include <exception>
using namespace std;

class memory_access_violation : public exception
{
	public:
	virtual const char* what() const throw()
	{
		return "Memory access violation";
	}
};

class ThrowMemoryAccessViolations
{
	private:
		void (*prev_handler)(int);
		
	public:
		ThrowMemoryAccessViolations()
		{
			prev_handler = signal(SIGSEGV, ThrowMemoryAccessViolations::SignalHandler);
			cout<< "prev_handler = " << prev_handler <<endl;
		}
		
		~ThrowMemoryAccessViolations()
		{
			cout<<"resetting handler to "<< prev_handler <<endl;
			signal(SIGSEGV, prev_handler);
		}
		
		static void SignalHandler(int signal)
		{
			cout<<"handling signal "<< signal <<endl;
			throw memory_access_violation();
		}
};

void MySignalHandler(int signal)
{
	cout<<"got signal "<< signal <<endl;
}

int main()
{
	ThrowMemoryAccessViolations now;
	cout<<"SIG_ERR = "<< SIG_ERR <<endl;
	/*void (*prev_handler)(int);
	prev_handler = signal(SIGSEGV, MySignalHandler);
	cout<<"prev_handler = "<< prev_handler <<endl;
	//raise(SIGSEGV);
	//raise(SIGSEGV);*/
	int* p = 0;
	*p = 1;
	//*p = 2;
	
	/*prev_handler = signal(SIGSEGV, prev_handler);
	cout<<"prev_handler = "<< prev_handler <<endl;
	//raise(SIGSEGV);
	
	prev_handler = signal(SIGSEGV, MySignalHandler);
	cout<<"prev_handler = "<< prev_handler <<endl;
	raise(SIGSEGV);*/
	
	return 0;
	
	try
	{
		cout<<"point to variable"<<endl;
		int n;
		int* q = &n;
		*q = 5;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	try
	{
		cout<<"point to array"<<endl;
		char* p = new char[42];
		*p = 23;
		delete [] p;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	// problems:
	
	try
	{
		cout<<"use null pointer => undefined (usually crash)"<<endl;
		int* q = 0;
		*q = 23;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	//ThrowMemoryAccessViolations too;
	
	try
	{
		cout<<"use null pointer => undefined (usually crash)"<<endl;
		int* q = 0;
		*q = 42;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	try
	{
		cout<<"use wild pointer (or set pointer to random adress) => crash or memory corruption"<<endl;
		int* q;
		*q = 23;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	try
	{
		cout<<"forget to free (or don't know when) => memory leak"<<endl;
		char* p = new char[42];
		*p = 23;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	try
	{
		cout<<"use pointer itself after free => crash or memory corruption"<<endl;
		char* p = new char[42];
		*p = 23;
		delete [] p;
		*p = 7;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	try
	{
		cout<<"use pointer itself after end of scope => crash or memory corruption"<<endl;
		int* q;
		{
			int n;
			q = &n;
		}
		*q = 5;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	try
	{
		/*cout<<"use dependend pointer after free => crash or memory corruption"<<endl;
		char* p = new char[42];
		char* r = p + 1;
		delete [] p;
		*r = 7;
		cout<<"worked"<<endl;*/
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	try
	{
		cout<<"invalid use of modified pointer => crash or memory corruption"<<endl;
		int n;
		int* q = &n;
		++q;
		*q = 5;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}

	try
	{
		/*cout<<"unable to free modified pointer => crash or stack corruption"<<endl;
		char* p = new char[42];
		++p;
		delete [] p;
		cout<<"worked"<<endl;*/
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}

	try
	{
		cout<<"no bound check => crash or memory corruption"<<endl;
		char* p = new char[42];
		p[99] = 0;
		cout<<"worked"<<endl;
	}
	catch(memory_access_violation& e)
	{
		cerr<<"Oops: "<< e.what() <<endl;
	}
	
	return 0;
}
