#include <iostream>
#include <random>
#include <functional>
using namespace std;

template<typename numbertype, template <typename> class distribution>
class Rand
{
	private:
		random_device rand_dev;
		default_random_engine generator;
		distribution<numbertype> distrib;
		
	public:
		template<typename... Params>
		Rand(Params... parameters) : rand_dev(), generator(rand_dev()), distrib(parameters...) {}
		
		numbertype operator() ()
		{
			return distrib(generator);
		}
};

int main()
{
	Rand<double, uniform_real_distribution> myrand(4, 7);
	cout<< myrand() << endl;
	return 0;
}
