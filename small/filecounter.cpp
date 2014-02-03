#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
using namespace std;

class LW_dirstat
{
	public:
	string dirname;           // name, not path
	unsigned long nfiles;     // number of files directly in it
	unsigned long nfiles_sum; // number of files including all subdirs
	vector<class LW_dirstat> subdirs;
	
	LW_dirstat(const string& _basepath, const string& _dirname="");
	void fullout(const string& basepath);
	void outmorethan(const string& basepath, const unsigned long& min_count);
};

LW_dirstat::LW_dirstat(const string& basepath, const string& _dirname)
{
	dirname = _dirname;
	nfiles = 0;
	nfiles_sum = 0;
	
	const string& path = (dirname=="" ? basepath : basepath + "/" + dirname);
	DIR *dp = opendir(path.c_str());
	if(dp == NULL)
	{
		cerr<<"Could not open directory \""<< dirname <<"\"."<<endl;
		return;
	}
	
	struct dirent* ep;
	while( (ep = readdir(dp)) )
	{
		string fname = ep->d_name;
		if(fname=="." || fname=="..")
			continue;
		
		if(ep->d_type & DT_DIR)
		{
			LW_dirstat subdirstat(path, fname);
			subdirs.push_back(subdirstat);
			nfiles_sum += subdirstat.nfiles_sum;
		}
		else // if(ep->d_type & DT_REG)
			++nfiles;
	}
	nfiles_sum += nfiles; // own files plus those in subdirs
	
	closedir(dp);
}

void LW_dirstat::fullout(const string& basepath)
{
	string path = (dirname=="" ? basepath : basepath+"/"+dirname);
	cout<< nfiles <<"\t"<< nfiles_sum <<"\t"<< path <<endl;
	for(auto subdir: subdirs) subdir.fullout(path);
}

void LW_dirstat::outmorethan(const string& basepath, const unsigned long& min_count)
{
	if(nfiles_sum >= min_count)
	{
		string path = (dirname=="" ? basepath : basepath+"/"+dirname);
		cout<< nfiles_sum <<"\t"<< path <<endl;
		for(auto subdir: subdirs) subdir.outmorethan(path, min_count);
	}
}

int main(int argc, char** argv)
{
	if(argc <= 1)
	{
		cout<<"usage: "<< argv[0] <<" /path/to/dir \n"
		"will output all dirs containing more than 1% of total number the files in /path/to/dir"<<endl;
		return 1;
	}
	const string basepath = argv[1];
	LW_dirstat basedirstat(basepath);
	// basedirstat.fullout(basepath);
	// cout<<"--"<<endl;
	basedirstat.outmorethan(basepath, basedirstat.nfiles_sum / 100);
	
	return 0;
}
