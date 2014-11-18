void foo(int& x)
{
	++x;
	return;
	++x;
}

int main()
{
	int x = 41;
	foo(x);
	return x;
}
