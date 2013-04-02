#ifndef _LW_RANDDISTRIB_
#define _LW_RANDDISTRIB_

#include <random>
#include <functional>

namespace LW {

template<typename numbertype, template <typename> class distribution>
class RandDistrib
{
	private:
		std::random_device rand_dev;
		std::default_random_engine generator;
		distribution<numbertype> distrib;
		
	public:
		template<typename... Params>
		RandDistrib(Params... parameters) : rand_dev(), generator(rand_dev()), distrib(parameters...) {}
		
		numbertype operator() ()
		{
			return distrib(generator);
		}
};

}

#endif // _LW_RANDDISTRIB_
