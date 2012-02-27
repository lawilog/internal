#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char** argv)
{
	srand(time(0));
	
	bool verbose = false;
	unsigned offset_a = 0;
	unsigned offset_b = 0;
	unsigned n_err_prop_rounds = 100; // error propability less than 1/2^100, which is less than 10^-31
	
	if(argc < 3)
	{
		cout << "usage: " << argv[0] << "[options] file_a file_b\n"
			"options:\n"
			"\t-ao N ... starting offset for file_a (i.e. skip first N bytes)\n"
			"\t-bo N ... starting offset for file_b (i.e. skip first N bytes)\n"
			"\t-r  N ... test N rounds, error propability will be less than 10^-(N/3.33)\n"
			"\t-c  N ... compare only first N bytes (after offset)\n"
			"\t-v    ... verbose mode (enable to get a written answer)\n"
			<< endl;
		return 1;
	}
	char* filename_a = argv[argc - 2];
	char* filename_b = argv[argc - 1];
	// TODO: parse options
	
	ifstream file_a(filename_a, ios::binary);
	if(! file_a)
	{
		cerr << "Could not open \"" << file_a << "\" for reading." << endl;
		return 1;
	}
	
	ifstream file_b(filename_a, ios::binary);
	if(! file_b)
	{
		cerr << "Could not open \"" << file_a << "\" for reading." << endl;
		return 1;
	}
	
	unsigned n_bytes = 1; // TODO: if option > file size then shrink, if no option: file size - offset (respecting both files)
	unsigned n_rounds = ceil(2*(ld(n_bytes) + n_err_prop_rounds));
	
	if(verbose)
	{
		;// TODO: repeat options
	}
	
	unsigned* comp_bytes_id = new unsigned[n_rounds];
	for(unsigned i = 0; i < n_rounds; ++i) comp_bytes_id[i] = (RAND_MAX * rand() + rand()) % n_bytes;
	for(unsigned i = 0; i < n_rounds; ++i)
	{
		unsigned smallest = i;
		for(unsigned j = i + 1; j < n_rounds; ++j) if(comp_bytes_id[j] < comp_bytes_id[smallest]) j = smallest;
		if(smallest != i)
		{
			unsigned temp = comp_bytes_id[smallest];
			comp_bytes_id[smallest] = comp_bytes_id[i];
			comp_bytes_id[i] = temp;
		}
	}
	
	for(unsigned i = 0; i < n_rounds; ++i)
	{
		file_a.seekg(offset_a + comp_bytes_id[i]);
		char a = file_a.get();
		
		file_b.seekg(offset_b + comp_bytes_id[i]);
		char b = file_b.get();
		
		if(a != b)
		{
			if(verbose) cout << "Files are definitely not identical." << endl;
			return 1;
		}
	}
	
	delete [] comp_bytes_id;
	
	file_b.close();
	file_a.close();
	
	if(verbose) cout << "I guess the files are identical." << endl;
	return 0;
}
