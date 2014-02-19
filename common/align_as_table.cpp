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
	
	public:

	void read(istream& is)
	{
		while(is.good())
		{
			LineArray la(is);
			unsigned N = la.size();
			if(N > max_col_len.size())
				max_col_len.resize(N, 0);
			
			for(unsigned i = 0; i < N; ++i)
			{
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
			unsigned N = la.size();
			for(unsigned i = 0; i < N; ++i)
			{
				cout<< la[i];
				for(unsigned k = la[i].size(); k <= max_col_len[i]; ++k)
				{
					cout<<' ';
				}
				cout<<' ';
			}
			cout<<endl;
		}
	}
};

int main(int argc, char** argv)
{
	TableData data;
	if(argc <= 1)
	{
		data.read(cin);
	}
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
