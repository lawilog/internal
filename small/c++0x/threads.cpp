#include <iostream>
#include <thread>
#include <vector>
using namespace std;

int main()
{
	vector<thread> threads;
	for(int i = 0; i < 5; ++i)
	{
		threads.push_back(thread([](){
			cout << "Hello from thread " << this_thread::get_id() << endl;
		}));
	}

	for(auto& thread: threads)
		thread.join();

	return 0;
}
