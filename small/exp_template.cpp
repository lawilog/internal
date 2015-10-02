#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::cin;
using std::endl;

//d=x+y-z+w; (1)
//d, y, x, z are compounds (e.g. vectors or matrices)
//we want to write (1) as c++ code and have no overhead,
//no temporaries, e.t.c...

//abstract class defining what an expression is
template<typename T>
struct expr
{
  //expressions return values, the content of the expression doesn't change
  //if we ask for the value --> const
  virtual T operator[](size_t i) const = 0;
  //expressions have a size
  //the content does still not change
  virtual size_t size() const = 0;
};
//add is an expression
template<typename T>
struct add : public expr<T>
{
  const expr<T>& _opa;
  const expr<T>& _opb;
  add(const expr<T>& opa, const expr<T>& opb) : _opa(opa), _opb(opb) {};
  //the rule is: its value at index i is left[i]+right[i]
  T operator[](size_t i) const {cout<<"ADD"<<endl; return _opa[i]+_opb[i];};
  //its lentgh is the length of the left operand
  size_t size() const {return this->_opa.size();};
};
//define an operator for add
template<typename T>
add<T> operator+(const expr<T>& left, const expr<T>& right)
{
  return add<T>(left,right);
};
//same for diff
template<typename T>
struct diff : public expr<T>
{ const expr<T>& _opa;
  const expr<T>& _opb;
  diff( const expr<T>& opa, const expr<T>& opb) : _opa(opa), _opb(opb) {};
  //the rule is: its value at index i is left[i]-right[i]
  T operator[](size_t i) const {cout<<"DIFF"<<endl; return _opa[i]-_opb[i];};
  size_t size() const {return this->_opa.size();};
};
template<typename T>
diff<T> operator-(const expr<T>& left,const expr<T>& right)
{
  return diff<T>(left,right);
};
//now we know what expressions are:
//note few is known about details: they might be
//scalars, matrices, strings (possibly containing symbolic math), ...
//fancy type is a vector. It is also an expression in itself 
//such as the x in eq. 1
//thus we inherit expr
template<typename T>
class fancy_type : public expr<T>
{
  //fancy type has some data
  vector<T> data;
public:
  //overload virtual stuff to make it an expression.
  T operator[](size_t i) const {return data[i];}
  size_t size() const {return data.size();}
  //just a standard ctor;
  //an operator to access elements (read+write)
  T& operator[](size_t i){return data[i];}
   //just a standard ctor;
  fancy_type(size_t n) : data(n) {
    cout<<"ctor\n";
  }
  //construct from expression such as d in
  //fancy_type d = x+y-z+w
  fancy_type(expr<T>&& other) noexcept : data(other.size())
  {
    cout<<"ctor from expression\n";
    for(int i=0;i<data.size();++i) {
  	data[i]=other[i];
      };
  }
  //assign from expression such as d in
  //d = x+y-z+w
  fancy_type& operator=(expr<T>&& other) noexcept
  {
    cout<<"assign from expression\n";
    for(int i=0;i<data.size();++i)
      {
  	data[i]=other[i];
      };
    return *this;
  }
  //a convenient ctor to construct from std::vector<double>;
  //particularly initializer lists
  fancy_type(const vector<double>& other) : data(other) {
    cout<<"ctor from vector\n";
  }
};
int main()
{
  fancy_type<double> a({1.0,2.0,3.0});
  fancy_type<double> b({4.0,5.0,6.0});
  cout<<"A"<<endl;
  fancy_type<double> c=a+b;
  cout<<"B"<<endl;
  fancy_type<double> d(3);
  cout<<"C"<<endl;
  d=a-c+b;
  cout<<"c: ";
  for(size_t i=0;i<d.size();++i)
    {
      cout<<c[i]<<" ";
    };
  cout<<"\nd: ";
  for(size_t i=0;i<d.size();++i)
    {
      cout<<d[i]<<" ";
    };
  cout<<"\n";
  
  int i;
  cout<<"c[i] = x;"<<endl;
  cout<<"i = "; cin>>i;
  cout<<"x = "; cin>>c[i];
  cout<<"i = "; cin>>i;
  cout<<"d[i] = "<< d[i] <<endl;
  cout<<"i = "; cin>>i;
  cout<<"d[i] = "<< d[i] <<endl;
};
