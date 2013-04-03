#ifndef _LW_RANDDISTRIB_
#define _LW_RANDDISTRIB_

#include <random>
#include <functional>

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
		
		number_type operator() ()
		{
			return F(generator);
		}
};

}

#endif // _LW_RANDDISTRIB_
