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
		char* p = new char[42];
		*p = 23;
		delete [] p;
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
		char* p = new char[42];
		*p = 23;
	}
	
	// use pointer itself after free => crash or memory corruption
	{
		char* p = new char[42];
		*p = 23;
		delete [] p;
		*p = 7;
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
		char* p = new char[42];
		char* r = p + 1;
		delete [] p;
		*r = 7;
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
		char* p = new char[42];
		++p;
		delete [] p;
	}

	// no bound check => crash or memory corruption
	{
		char* p = new char[42];
		p[99] = 0;
	}
	
	return 0;
}
