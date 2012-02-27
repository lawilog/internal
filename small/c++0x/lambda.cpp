#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Shoe
{
	unsigned article_id;
	float size;
};

bool vergleich(const Shoe& x, const Shoe& y)
{
	return x.size < y.size;
}

auto summe(int a, int b) -> int { return a + b; }

int main()
{
	[](int x) { return x + 1; } ;
	
	auto square_function = [](int x) { return x * x; } ;
	cout<< square_function(7) <<endl;
	
	int daten[8] = {-1, 9, 4, -5, 3, 0, 2, 8};
	sort(daten, daten+8, [](int x, int y) {return (x<y);} );
	
	for(int& x : daten)
		cout<< " " << x;
	cout<<endl;
	
	Shoe schuhe[4] = { {3, 42}, {1, 44.5}, {7, 37}, {2, 40.5} };
	sort(schuhe, schuhe+4, [](const Shoe& x, const Shoe& y) {return x.size < y.size;} );
	sort(schuhe, schuhe+4, vergleich );
	
	for(Shoe& s : schuhe)
		cout<< s.article_id << " : " << s.size << endl;
	
	vector<int> some_list;
	int total = 0;
	for_each(daten, daten+8, [&total](int x) {
		total += x;
	});
	cout<<"total = "<< total << endl;
	
	int n = 100, m = 30;
	auto test = [&, n](int x) -> int {return n + m + x;} ;
	cout<<"test(5) = "<< test(5) <<endl;
	n = 200;
	cout<<"test(5) = "<< test(5) <<endl;
	m = 50;
	cout<<"test(5) = "<< test(5) <<endl;
	
	cout<<"5 + 3 = "<< summe(5, 3) <<endl;
	
	return 0;
}
