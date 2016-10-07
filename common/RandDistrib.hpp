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
		
		// per default we seed from random dev. use reseed() only if you want a particular seed:
		void reseed(unsigned new_seed) {generator.seed(new_seed);}
		
		number_type operator() ()
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

}

#endif // _LW_RANDDISTRIB_
