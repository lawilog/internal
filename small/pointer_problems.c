#include <stdlib.h>

int main()
{
	// correct: point to variable
	{
		int n;
		int* q = &n;
		*q = 5;
	}

	// correct: point to array
	{
		char* p = malloc(42);
		if(!p) exit(EXIT_FAILURE);
		*p = 'X';
		free(p);
	}
	
	// problems:
	
	// use wild pointer (or set pointer to random adress) => crash or memory corruption
	{
		int* q;
		*q = 23;
	}
	
	// use null pointer => undefined (usually crash)
	{
		int* q = 0;
		*q = 23;
	}
	
	// forget to free (or don't know when) => memory leak
	{
		char* p = malloc(42);
		if(!p) exit(EXIT_FAILURE);
		*p = 'X';
	}
	
	// use pointer itself after free => crash or memory corruption
	{
		char* p = malloc(42);
		if(!p) exit(EXIT_FAILURE);
		*p = 'X';
		free(p);
		*p = 'Y';
	}
	
	// use pointer itself after end of scope => crash or memory corruption
	{
		int* q;
		{
			int n;
			q = &n;
		}
		*q = 5;
	}
	
	// use dependend pointer after free => crash or memory corruption
	{
		char* p = malloc(42);
		//if(!p) exit(EXIT_FAILURE);
		char* r = p + 1;
		free(p);
		*r = 'X';
	}
	
	// invalid use of modified pointer => crash or memory corruption
	{
		int n;
		int* q = &n;
		++q;
		*q = 5;
	}

	// unable to free modified pointer => crash or stack corruption
	{
		char* p = malloc(42);
		if(!p) exit(EXIT_FAILURE);
		++p;
		free(p);
	}

	// no bound check => crash or memory corruption
	{
		char* p = malloc(42);
		if(!p) exit(EXIT_FAILURE);
		p[99] = 'X';
		free(p);
	}
	
	return 0;
}
