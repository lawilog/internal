#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

extern "C" {
	double libfunction(double (*f)(double)) { return f(0.3) + f(0.7);}
}

double myfunA(double x) { return sin(x + 1.0); }
double myfunB(double x) { return sin(x + 2.0); }

//This is a functor
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

template<int offset>
double myfunX(double x) { return sin(x + offset); }

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

double (*gimme())(double)
{
	return myfun;
}

int main()
{
	cout<<"libfunction(myfunA): "<< libfunction(myfunA) <<endl;
	cout<<"libfunction(myfunB): "<< libfunction(myfunB) <<endl;
	
	FunctionLikeObject myFunObjB(2.0);
	cout<<"myFunObjB(0.3) + myFunObjB(0.7): "<< myFunObjB(0.3) + myFunObjB(0.7) <<endl;
	
	cout<< myfunX<2>(0.3) + myfunX<2>(0.7) <<endl;
	
	function<double(double)> myFunObjBB(myfunB);
	double (*fpA)(double) = myfunA;
	double (*const* fpB)(double) = myFunObjBB.target<double(*)(double)>();
	cout<<"myFunObjBB.target_type().name(): "<< myFunObjBB.target_type().name() <<endl;
	cout<<"libfunction(fpA): "<< libfunction(fpA) <<endl;
	if(! fpB) cout<< "! fpB" <<endl;
	else cout<<"libfunction(fpB): "<< libfunction(*fpB) <<endl;
	
	// to following FAILS, because, unlike above, myFunObj_bind.target_type() is not double (*const*)(double)
	function<double(double)> myFunObj_bind = bind(&FunctionLikeObject::operator(), myFunObjB, std::placeholders::_1);
	double (*const* fp_bind)(double) = myFunObj_bind.target<double(*)(double)>();
	cout<<"myFunObj_bind.target_type().name(): "<< myFunObj_bind.target_type().name() <<endl;
	if(! fp_bind) cout<< "! fp_bind" <<endl;
	else cout<<"libfunction(*fp_bind): "<< libfunction(*fp_bind) <<endl;
	
	const char* test = myFunObj_bind.target_type().name();
	
	myfunctor<0,double,double>() = myFunObj_bind;
	cout<<"libfunction(*fp_bind): "<< libfunction(myfunctor_wrapper<0,double,double>) <<endl;
	
	return 0;
}
