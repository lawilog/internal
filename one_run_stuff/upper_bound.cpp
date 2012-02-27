#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
	const int n=10;
	const int m=64;
	int** array=new int*[n];
	for(int i=0; i<n; ++i) if(i%3==0) array[i]=new int[m];
	for(int i=0; i<n; ++i) if(i%3==1) array[i]=new int[m];
	for(int i=0; i<n; ++i) if(i%3==2) array[i]=new int[m];
	for(int i=0; i<n; ++i) printf("%p\t%li\n", array[i], array[i]-(int*)array);
	
	// preperation {
	vector<int*> v(array, array+n); // O(n)
	vector<int*>::iterator vi;
	sort(v.begin(), v.end());    // O(n*log n)
	map<int*, int> indices;
	map<int*, int>::iterator mi;
	for(int i=0; i<n; ++i) indices.insert(pair<int*, int>(array[i], i)); // O(n*log n)
	
	// }
	
	// example {
	const int a=8;
	const int b=11;
	int* guess_what = array[a] + b;
	printf("guess_what = %p\t%li\n", guess_what, guess_what-(int*)array);
	// }
	
	
	// solution {
	vi = upper_bound(v.begin(), v.end(), guess_what); // O(log n)
	--vi;
	
	printf("upper_bound = %p\t%li\n", *vi, *vi-(int*)array);
	
	mi = indices.find(*vi); // O(log n)
	// assert(mi != m.end())
	int a_result = mi->second; // O(1)
	int b_result = guess_what - array[a_result];
	
	printf(" a = %i \n b = %i \n a_result = %i \n b_result = %i \n", a, b, a_result, b_result);
	// }
	
	for(int i=0; i<n; ++i) delete [] array[i];
	delete [] array;
	return 0;
}

//p = v.begin(); printf("{"); while(p != v.end()) {printf(" %li ", *p-(int*)array); ++p; } printf("}\n");
