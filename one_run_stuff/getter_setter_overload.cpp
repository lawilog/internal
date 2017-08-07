#include <iostream>
#include <string>
using namespace std;

template<class T>
class var
{
  private:
    T value;
  
  public:
    var() : value() {}
    var(const T& _value) : value(_value) {}
    inline T& operator=(const T& newval) { value = newval; }
    inline operator const T&() const { return value; }
    inline const T& operator()() const { return value; }
};

template<class T>
ostream& operator<<(ostream& os, const var<T>& x)
{
  os<< T(x);
  return os;
}

/* This aproach with var<T> allows getting and setting of variables.
Allows for type-dependent template specializations of var<>.
However, variables-dependet specializations are not possible so easily - for
that, maybe we could use   void my_int_setter(int& i) {...}, etc.
and a function pointer (defaulted to nullptr) as template parameter.
This, in turn, allows for everything that is possible independet of the objects
in which var lives - e.g., it would not be possible to update something else in
the parent object upon updating a var<T> variable. For that, we would need
different constructors of var (and additional memory for storing reference to
the parent object).
Also, neither d.myint += 7; nor d.myint() += 7 would work here (not without
further work).

So: this approac is only useful for specific contexts.
*/

struct data
{
  var<int> myint;
  var<string> mystring;
};

int main()
{
  data d;
  d.myint = 42;
  d.mystring = "magic";
  // int& x = d.myint;   does not compile (no bypassing allowed)
  const int& x = d.myint; // okay
  cout<<" d is : "<< d.myint <<", "<< d.mystring <<endl;
  string test = "foo " + d.mystring(); // need "()" here
  cout<< test <<endl;
  return 0;
}
