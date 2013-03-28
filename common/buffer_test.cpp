#include <iostream>
#include <string>
#include <vector>
using namespace std;

template < class T, class Allocator = allocator<T> > class buffer : public vector <T, Allocator >
{
	public:
		void reset_size(size_t sz)
		{
			this->_M_impl._M_finish = this->_M_impl._M_start + sz;
		}
};

int main()
{
	const unsigned len = 11;
	char data[len]="0123456789";
	
	vector<char> v_buffer;
	v_buffer.reserve(len);
	copy(data, data+len, v_buffer);
	cout<< v_buffer.size() << endl;
	
	buffer<char> b_buffer;
	b_buffer.reserve(len);
	copy(data, data+len, v_buffer);
	b_buffer.reset_size(len);
	cout<< b_buffer.size() << endl;
	
	return 0;
}

