#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

extern "C" {
	double libfunction(double (*f)(double)) { return f(0.3) + f(0.7);}
}

double myfun(double x) { return sin(x + 1.0); }

class FunctionLikeObject
{
	private:
		double hidden_data;
	
	public:
		FunctionLikeObject(double d) : hidden_data(d) {}
		
		double operator()(double x) const
		{
			return sin(x + hidden_data);
		}
};

template<unsigned ID, typename result_type, typename argument_type>
function<result_type(argument_type)>& myfunctor()
{
	static function<result_type(argument_type)> local_storage;
	return local_storage;
}

template<unsigned ID, typename result_type, typename argument_type>
result_type myfunctor_wrapper(argument_type x)
{
	return myfunctor<ID,result_type,argument_type>()(x);
}

template<unsigned ID, typename result_type, typename argument_type>
result_type (*magic_wrapper(const function<result_type(argument_type)>& functor))(argument_type)
{
	myfunctor<ID,result_type,argument_type>() = functor;
	return myfunctor_wrapper<ID,result_type,argument_type>;
}

/*
problem:
   the result of lambdas and bind()s, etc. is an object that (in general) contains a state
   obj(x) is actually obj.operator(x), similar to a c-function class::operator(obj, x)
   this object can be transfered into a std::function, but (in general) not back to
   a c-style function pointer, which expects only x and does not know about obj
solution:
   the trick here is to reserve a space for a each required function on compile time (label them by ID)
   we can get a c-style pointer to such a function on compile time (based on it's ID)
   but what this function does is evaluating obj(x), where obj can be assigned on runtime
*/

int main()
{
	cout<<"libfunction(myfun): "<< libfunction(myfun) <<endl;
	
	function<double(double)> myFunObj_simple(myfun);
	cout<<"libfunction(*fp_simple): "<< libfunction(*myFunObj_simple.target<double(*)(double)>()) <<endl;
	
	FunctionLikeObject myFunObj(1.0);
	cout<<"myFunObj(0.3) + myFunObj(0.7): "<< myFunObj(0.3) + myFunObj(0.7) <<endl;
	
	myfunctor<0,double,double>() = bind(&FunctionLikeObject::operator(), myFunObj, std::placeholders::_1);
	cout<<"libfunction(myfunctor_wrapper<0>): "<< libfunction(myfunctor_wrapper<0,double,double>) <<endl;
	
	myfunctor<1,double,double>() = [] (double x) {return sin(x + 1.0);}; // check out this working lambda example
	cout<<"libfunction(myfunctor_wrapper<1>): "<< libfunction(myfunctor_wrapper<1,double>) <<endl; // argument_type deduced
	
	// top class: one liners
	cout<<"libfunction(magic_wrapper<2>): "<< libfunction( magic_wrapper<2,double,double>(bind(&FunctionLikeObject::operator(), myFunObj, std::placeholders::_1)) ) <<endl;
	
	cout<<"libfunction(magic_wrapper<3>): "<< libfunction( magic_wrapper<3,double,double>( [] (double x) {return sin(x + 1.0);} ) ) <<endl;
	
	return 0;
}
