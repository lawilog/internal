#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

void doCount(istream& is)
{
  char buffer[10240];
  unordered_map<string,unsigned> count;
  while(is.good())
  {
    buffer[0] = 0;
    is.getline(buffer, sizeof(buffer));
    if(buffer[0] != 0)
      ++count[buffer];
  }
  typedef unordered_map<string,unsigned>::const_iterator it_type;
  vector<it_type> its;
  its.reserve(count.size());
  for(it_type it = count.cbegin(); it != count.cend(); ++it)
    its.push_back(it);
  
  sort(its.begin(), its.end(), [](const it_type& i, const it_type& j)
  {
    return i->second > j->second;
  });
  
  for(const auto& it: its)
    cout<< it->second <<' '<< it->first <<"\n";
  
  cout<<flush;
}

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    cout<< argv[0] << " file\n"
      "Counts number of times each line occurs. Example, a file containing:\n"
      " AA\n"
      " BB\n"
      " AA\n"
      "would output:\n"
      "2 AA\n"
      "1 BB"<<endl;
    return 0;
  }
  const char* filename = argv[1];
  if(filename == string("-"))
    doCount(cin);
  else
  {
    ifstream f(filename);
    if(! f)
    {
      cerr<<"Could not open file \""<< filename <<"\" for reading."<<endl;
      return 1;
    }
    doCount(f);
  }
  return 0;
}
