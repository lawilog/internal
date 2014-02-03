#include <iostream>
#include <cstdio>
using namespace std;

/*int call_printf(char* format, ...)
{
	printf(format, args);
}*/

template<typename... Args>
void call_printf(const char* format, const Args&... args)
{
	printf(format, args...);
}

template<class...A> void func(A...args)
{
    const int size = sizeof...(args) +5;
    printf("size %d\n", size);
    int res[sizeof...(args)+5]={99,98,args...,97,96,95};
    //printarray(res,size);
}

int main()
{
	printf("%i + %f\n", (int)2.3, (float)42);
	printf("%i + %f\n", 2.3, 42);
	call_printf("%i + %f\n", 2.3, 42);
	return 1;
}
