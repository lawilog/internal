#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <codecvt>
#include <locale>
using namespace std;

// convert UTF-8 string to wstring
wstring utf8toWstr(const string& utf8_str)
{
  static wstring_convert<codecvt_utf8<wchar_t>> myconv;
  return myconv.from_bytes(utf8_str);
}

// convert wstring to UTF-8 string
string str2toUtf8(const wstring& wstr)
{
  static wstring_convert<codecvt_utf8<wchar_t>> myconv;
  return myconv.to_bytes(wstr);
}

void doCount(istream& utf8_is)
{
  char buffer[10240];
  wstring wbuf; wbuf.reserve(sizeof(buffer));
  const wstring allowed = L"abcdefghijklmnopqrstuvwxyzăâîșț" // official alphabet
    "-" // special allowed chars
    "ǎṣşţ" // misspelled, ǎ -> ă, ṣ -> ș, ş -> ș, ţ -> ț
    "áčçéèêëíóőöôšúü"; // forgein allowed
    // nope "àäãćìïťž"
  const wstring ALLOWED = L"ABCDEFGHIJKLMNOPQRSTUVWXYZĂÂÎȘȚ"
    "-"
    "ǍṢŞŢ" // misspelled, ǎ -> ă, ṣ -> ș, ş -> ș, ţ -> ț
    "ÁČÇÉÈÊËÍÓŐÖÔŠÚÜ";
  
  unordered_map<wstring,unsigned> count;
  size_t wordpos = 0, i = 0;
  while(utf8_is.good())
  {
    buffer[0] = 0;
    utf8_is.getline(buffer, sizeof(buffer));
    wbuf = utf8toWstr(buffer);
    wordpos = 0;
    for(i = 0; i < wbuf.length(); ++i)
    {
      wchar_t& c = wbuf[i];
      size_t pos = ALLOWED.find(c);
      if(pos != wstring::npos)
        c = allowed[pos]; // to lower
      else
        pos = allowed.find(c);
      
      if(pos == wstring::npos)
      {
        if(wordpos != 0)
          ++count[wbuf.substr(i-wordpos, wordpos)];
        
        wordpos = 0;
      }
      else
        ++wordpos;
    }
  }
  if(wordpos != 0)
    ++count[wbuf.substr(i-wordpos, wordpos)];
  
  typedef unordered_map<wstring,unsigned>::const_iterator it_type;
  vector<it_type> its;
  its.reserve(count.size());
  for(it_type it = count.cbegin(); it != count.cend(); ++it)
    its.push_back(it);
  
  sort(its.begin(), its.end(), [](const it_type& i, const it_type& j)
  {
    return i->second > j->second;
  });
  
  for(const auto& it: its)
    cout<< it->second <<' '<< str2toUtf8(it->first) <<"\n";
  
  cout<<flush;
}

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    cout<< argv[0] << " file\n"
      "Counts number of times each word occurs. Example, a file containing:\n"
      " Aa BB, AA.\n"
      "would output:\n"
      "2 aa\n"
      "1 bb"<<endl;
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
