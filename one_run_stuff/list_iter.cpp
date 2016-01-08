#include <iostream>
#include <list>
using namespace std;

int main() {
list<int> L = {10, 20, 30, 40};
for(auto i = L.begin(); i!=L.end(); ++i) {
auto j = i; for(++j; j!=L.end(); ++j) {
cout<< *i <<","<< *j <<endl;
}
}
return  0;
}
