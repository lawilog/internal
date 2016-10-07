#ifndef _LW_RANDDISTRIB_
#define _LW_RANDDISTRIB_

#include <random>
#include <functional>
#include <valarray>

namespace LW {

template<typename number_type, template <typename> class distribution_type>
class RandDistrib
{
	private:
		std::random_device rand_dev;
		std::default_random_engine generator;
		
	public:
		distribution_type<number_type> F;
		
		template<typename... Params>
		RandDistrib(Params... parameters) : rand_dev(), generator(rand_dev()), F(parameters...) {}
		
		inline number_type operator() ()
		{
			return F(generator);
		}
		
		std::valarray<number_type> operator() (std::size_t n)
		{
			std::valarray<number_type> v(n);
			for(std::size_t i = 0; i < n; ++i)
				v[i] = F(generator);
			
			return v;
		}
};

template<typename number_type, template <typename> class distribution_type>
class RandDistrib_Seed
{
	private:
		std::default_random_engine generator;
		
	public:
		distribution_type<number_type> F;
		
		template<typename... Params>
		RandDistrib_Seed(unsigned seed, Params... parameters) : generator(seed), F(parameters...) {}
		
		inline number_type operator() ()
		{
			return F(generator);
		}
		
		std::valarray<number_type> operator() (std::size_t n)
		{
			std::valarray<number_type> v(n);
			for(std::size_t i = 0; i < n; ++i)
				v[i] = F(generator);
			
			return v;
		}
};

// TODO: make virtual base class (interface) and derive normal and _Seed class from it

}

#endif // _LW_RANDDISTRIB_
