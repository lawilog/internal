#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
  struct P {string partei; float prozent;};
  vector<P> umfragen = { // Thueringen 2019-03-26
    {"Union", 28},
    {"Linke", 24},
    {"AfD", 20},
    {"SPD", 11},
    {"Grüne", 8},
    {"FDP", 5}
  };
  float sum = 0;
  for(P& p: umfragen)
    sum += p.prozent;
  
  for(P& p: umfragen)
    p.prozent /= sum;
  
  for(size_t i = umfragen.size(); i --> 0;)
    if(umfragen[i].prozent < 0.05)
      umfragen.erase(umfragen.begin() + i);
  
  cout<<"Nach 5%-Huerde:"<<endl;
  for(size_t i = 0; i < umfragen.size(); ++i)
    cout<< (100 * umfragen[i].prozent) <<"%: "<< umfragen[i].partei <<"\n";
  
  cout<<"Rechnerisch moegliche Koaltionen:"<<endl;
  vector<bool> b(umfragen.size(), false);
  b[0] = true; // actually, dont try empty subset
  do
  {
    float sumpro = 0;
    for(size_t i = 0; i < umfragen.size(); ++i)
      if(b[i])
        sumpro += umfragen[i].prozent;
    
    if(sumpro >= 0.5)
    {
      bool every_needed = true;
      for(size_t i = 0; i < umfragen.size(); ++i)
        if(sumpro - umfragen[i].prozent >= 0.5)
        {
          every_needed = false;
          break;
        }
      
      if(every_needed)
      {
        cout<< (100 * sumpro) <<"%: ";
        bool first = true;
        for(size_t i = 0; i < umfragen.size(); ++i)
        {
          if(b[i])
          {
            if(first)
              first = false;
            else
              cout<<" + ";
            
            cout<< umfragen[i].partei;
          }
        }
        
        cout<<endl;
      }
    }
    
    // next combination:
    size_t i = 0;
    for(; i < b.size(); ++i)
    {
      if(b[i]) b[i] = false;
      else {b[i] = true; break;}
    }
    if(i == b.size())
      break;
    
  } while(true);
  
  return 0;
}
