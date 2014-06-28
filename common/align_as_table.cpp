#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "LineArray.h"
using namespace std;
using namespace LW;

class TableData
{
	private:
	vector<LineArray> lines;
	vector<unsigned> max_col_len;
	vector<bool> numbers_only;
	
	public:

	void read(istream& is)
	{
		while(is.good())
		{
			LineArray la(is);
			unsigned N = la.size();
			
			if(N == 0 && !is.good()) // do not interpret final line break as empty line
				break;
			
			if(N > max_col_len.size())
			{
				max_col_len.resize(N, 0);
				numbers_only.resize(N, true);
			}
			
			for(unsigned i = 0; i < N; ++i)
			{
				if(la[i].find_first_not_of("9876543210+-.,") != string::npos) // not perfect (e.g. also matches 1+,3 as number), but okay
					numbers_only[i] = false;
				
				if(la[i].length() > max_col_len[i])
					max_col_len[i] = la[i].length();
			}
			lines.push_back( la );
		}
	}
	
	void write()
	{
		for(LineArray& la : lines)
		{
			for(unsigned i = 0; i < la.size(); ++i)
			{
				if(numbers_only[i])
					cout<< string(max_col_len[i] - la[i].size(), ' ') << la[i] <<"  ";
				else
					cout<< la[i] << string(max_col_len[i] - la[i].size() + 2, ' ');
			}
			cout<<endl;
		}
	}
};

int main(int argc, char** argv)
{
	TableData data;
	if(argc <= 1)
		data.read(cin);
	else
	{
		ifstream fin(argv[1]);
		if(! fin)
		{
			cerr<<"Error: Could not open file \""<< argv[1] << "\" for reading."<<endl;
			return 1;
		}
		data.read(fin);
	}
	
	data.write();
	
	return 0;
}
