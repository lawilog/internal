#include <iostream>
#include <cstdlib>
#include <vector>
#include <valarray>
#include <ctime>

int main()
{
	unsigned length = 2e6;
	double* array_a = (double*)malloc( length * sizeof(double) );
	double* array_b = (double*)malloc( length * sizeof(double) );
	double* array_c = (double*)malloc( length * sizeof(double) );
	double*__restrict__ end_a = array_a + length;
	double*__restrict__ end_c = array_c + length;
	
	std::vector<double> vektor_a(length);
	std::vector<double> vektor_b(length);
	std::vector<double> vektor_c(length);
	
	std::valarray<double> vA(length);
	std::valarray<double> vB(length);
	std::valarray<double> vC(length);
	
	for( unsigned i=0; i < vektor_a.size(); i++ )
	{
		vektor_a[i] = rand() / RAND_MAX;
		vektor_b[i] = rand() / RAND_MAX;
		vektor_c[i] = rand() / RAND_MAX;
	}
	
	for( double* p_a = array_a, *p_b = array_b, *p_c = array_c; p_a < end_a; p_a++, p_b++, p_c++  )
	{
		*p_a = rand() / RAND_MAX;
		*p_b = rand() / RAND_MAX;
		*p_c = rand() / RAND_MAX;
	}
	
	for(size_t i = 0; i < length; ++i)
	{
		vA[i] = rand() / RAND_MAX;
		vB[i] = rand() / RAND_MAX;
		vC[i] = rand() / RAND_MAX;
	}
	
	clock_t t = 0, t_1 = 0, t_2 = 0, t_3 = 0, t_4 = 0, t_5 = 0;
	
	for( int iterations = 0; iterations < 10; iterations++ )
	{
		int scal_prod;
		t = clock();
		
		for( int i = 0; i < 10; i++ )
		{
			scal_prod = 0;
			for( double* __restrict__ p_a = array_a, * __restrict__ p_b = array_b; p_a < end_a; p_a++, p_b++ )
				scal_prod += *(p_a) * *(p_b);
			
			for( double* __restrict__ p_c = array_c; p_c < end_c; *p_c++ += scal_prod );
		}
		
		t_1 += clock() - t;
		t = clock();
		
		for( unsigned i = 0; i < 10; i++ )
		{
			scal_prod = 0;
			for( unsigned i = 0; i < length; i++ )
				scal_prod += array_a[i] * array_b[i];
			
			for( unsigned i = 0; i < length; i++)
				array_c[i] *= scal_prod;
		}
		
		t_4 += clock() - t;
		t = clock();
		
		for( unsigned i = 0; i < 10; i++ )
		{
			scal_prod = 0;
			for( unsigned j = 0; j < vektor_a.size(); j++ )
				scal_prod += vektor_a[j] * vektor_b[j];
			
			for( unsigned j = 0; j < vektor_c.size(); vektor_c[j++] += scal_prod );
		}
		
		t_2 += clock() - t;
		t = clock();
		
		for( unsigned i = 0; i < 10; i++ )
		{
			scal_prod = 0;
			for( std::vector<double>::iterator it_a = vektor_a.begin(), it_b = vektor_b.begin(); it_a != vektor_a.end(); ++it_a, ++it_b )
				scal_prod += *it_a * *it_b ;
			
			for( std::vector<double>::iterator it_c = vektor_c.begin(); it_c != vektor_c.end(); *it_c++ += scal_prod );
		}
		t_3 += clock() - t;
		t = clock();
		
		for( unsigned i = 0; i < 10; i++ )
		{
			scal_prod = (vA*vB).sum();
			vC += scal_prod;
		}
		t_5 += clock() - t;
	}

	std::cout<<"using C Arrays + Pointer : "<<((long long)t_1) / 10<<std::endl
		<<"using plain C Arrays : "<<((long long)t_4) / 10<<std::endl
		<<"using C++ Vektors : "<<((long long)t_2) / 10<<std::endl
		<<"using C++ Vektors + iterators : "<<((long long)t_3) / 10<<std::endl
		<<"using C++ valarrays : "<<((long long)t_5) / 10<<std::endl;
	
	free(array_a);
	free(array_b);
	free(array_c);
	
	return 0;
}

