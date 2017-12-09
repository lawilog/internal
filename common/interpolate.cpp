#include <iostream>
#include <fstream>
#include "FunInterpolTable.hpp"
using namespace std;
using namespace LW;

double fail(double)
{
  throw "Not enough points for chosen interpolation method.";
}

int main(int argc, char** argv)
{
  if(argc <= 2)
  {
    cerr<<"usage: "<< argv[0]<<" inputpath.dat x1 [x2 ...]"<<endl;
    return 1;
  }
  string inputpath = argv[1];
  
  FunInterpolTable<quadratic> f(fail, 0);
  f.load(inputpath);
  
  for(int i = 2; i < argc; ++i)
  {
    const double x = atof(argv[i]);
    cout<< x <<" "<< f(x) <<endl;
  }
  return 0;
}
