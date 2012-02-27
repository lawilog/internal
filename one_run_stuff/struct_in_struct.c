#include <stdio.h>

struct a
{
	int foo;
	int bar;
};

struct b
{
	float hallo;
	struct a s;
};

struct b fun(struct a AA, float h)
{
	struct b y;
	y.hallo = h;
	y.s = AA;
}

int main()
{
	struct a aaa = {1, 2};
	struct b x = fun(aaa, 0.5);
	return 0;
}
