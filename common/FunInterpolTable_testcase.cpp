#include <iostream>
#include <fstream>
#include <cmath>
#include "RandDistrib.hpp"
#include "FunInterpolTable.hpp"
using namespace std;
using namespace LW;

int main()
{
	RandDistrib<double,uniform_real_distribution> randuni(0, 2*M_PI);
	RandDistrib<double,uniform_real_distribution> randuni2(-3, 3);
	RandDistrib<int,uniform_int_distribution> randi(0, 6);
	ofstream d0("function_interpolation_table_f0.dat"); if(! d0) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d1("function_interpolation_table_f1.dat"); if(! d1) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d2("function_interpolation_table_f2.dat"); if(! d2) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d3("function_interpolation_table_f3.dat"); if(! d3) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d4("function_interpolation_table_f4.dat"); if(! d4) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d5("function_interpolation_table_f5.dat"); if(! d5) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d6("function_interpolation_table_f6.dat"); if(! d6) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d7("function_interpolation_table_F7.dat"); if(! d7) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d8("function_interpolation_table_F8.dat"); if(! d8) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream d9("function_interpolation_table_F9.dat"); if(! d9) {cerr<<"Could not write file."<<endl; return 1;}
	ofstream dA("function_interpolation_table_fA.dat"); if(! dA) {cerr<<"Could not write file."<<endl; return 1;}
	
	// closest
	FunInterpolTable<closest> f0(sin, 0.1);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d0<< x <<"\t"<< f0(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f0, random, closest: "<< f0.getCallCount() <<" calls, "<< f0.getEvalCount() <<" evals"<<endl;
	
	// linear
	FunInterpolTable<linear> f1(sin, 0.1);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d1<< x <<"\t"<< f1(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f1, random, linear: "<< f1.getCallCount() <<" calls, "<< f1.getEvalCount() <<" evals"<<endl;
	
	// precompute closest
	FunInterpolTable<closest> f2(sin, 0);
	f2.precompute(0, 2*M_PI, 10);
	// f2.setXPerc(0);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d2<< x <<"\t"<< f2(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f2, random, closest, precomputes: "<< f2.getCallCount() <<" calls, "<< f2.getEvalCount() <<" evals"<<endl;
	
	// precompute linear
	FunInterpolTable<linear> f3(sin, 0);
	f3.precompute(0, 2*M_PI, 10);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d3<< x <<"\t"<< f3(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f3, random, linear, precomputes: "<< f3.getCallCount() <<" calls, "<< f3.getEvalCount() <<" evals"<<endl;
	
	// cache 0 <= n <= 6 with integer n
	FunInterpolTable<closest,float,float> f4(sin, 1);
	// f4.setXPerc(1);
	for(unsigned i = 0; i < 1000; ++i)
	{
		int x = randi();
		d4<< x <<"\t"<< f4(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f4, cache: "<< f4.getCallCount() <<" calls, "<< f4.getEvalCount() <<" evals"<<endl;
	
	// quadratic
	FunInterpolTable<quadratic> f5(sin, 0.1);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d5<< x <<"\t"<< f5(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f5, random, quadratic: "<< f5.getCallCount() <<" calls, "<< f5.getEvalCount() <<" evals"<<endl;
	
	// precompute quadratic
	FunInterpolTable<quadratic> f6(sin, 0);
	f6.precompute(0, 2*M_PI, 10);
	// f6.setXPerc(0);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		d6<< x <<"\t"<< f6(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"f3, random, quadratic, precomputes: "<< f6.getCallCount() <<" calls, "<< f6.getEvalCount() <<" evals"<<endl;
	
	f6.save("function_interpolation_table_f6.saved.dat");
	f5.load("function_interpolation_table_f6.saved.dat", true);
	f5.save("function_interpolation_table_f5.saved.dat");
	
	// gnuplot: plot "function_interpolation_table_f0.dat" w p title "random, closest", "function_interpolation_table_f1.dat" w p title "random, linear", "function_interpolation_table_f2.dat" w p title "random, closest, precomputes", "function_interpolation_table_f3.dat" w p title "random, linear, precomputes", "function_interpolation_table_f5.dat" w p title "random, quadratic", "function_interpolation_table_f6.dat" w p title "random, quadratic, precomputes", sin(x)
	
	// exp, precompute linear
	FunInterpolTable<linear> f7(exp, 0);
	f7.precompute(-3, 3, 10);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni2();
		d7<< x <<"\t"<< f7(x) <<"\t"<< exp(x) <<endl;
	}
	cout<<"F7, random, linear, precomputes: "<< f7.getCallCount() <<" calls, "<< f7.getEvalCount() <<" evals"<<endl;
	
	FunInterpolTable<log_linear> f8(exp, 0);
	f8.precompute(-3, 3, 10);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni2();
		d8<< x <<"\t"<< f8(x) <<"\t"<< exp(x) <<endl;
	}
	cout<<"F8, random, log_linear, precomputes: "<< f8.getCallCount() <<" calls, "<< f8.getEvalCount() <<" evals"<<endl;
	
	FunInterpolTable<log_quadratic> f9(exp, 1);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni2();
		d9<< x <<"\t"<< f9(x) <<"\t"<< exp(x) <<endl;
	}
	cout<<"F9, random, log_quadratic: "<< f9.getCallCount() <<" calls, "<< f9.getEvalCount() <<" evals"<<endl;
	
	// log_quadratic
	FunInterpolTable<log_quadratic> fA(sin, 2);
	for(unsigned i = 0; i < 1000; ++i)
	{
		double x = randuni();
		dA<< x <<"\t"<< fA(x) <<"\t"<< sin(x) <<endl;
	}
	cout<<"fA, random, quadratic, precomputes: "<< fA.getCallCount() <<" calls, "<< fA.getEvalCount() <<" evals"<<endl;
	
	return 0;
}
