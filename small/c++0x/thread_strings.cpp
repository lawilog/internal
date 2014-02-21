#include <iostream>
#include <thread>
#include <vector>
#include <string>
using namespace std;

int main()
{
	const unsigned N = 100;
	string s = "F00";
	string a[N];
	for(int i = 0; i < N; ++i)
		a[i] = s;
	
	for(int i = 0; i < N; ++i)
		cout<< (unsigned*)(a[i].c_str()) <<endl;
	
	vector<thread> threads;
	for(int i = 0; i < N; ++i)
	{
		threads.push_back(thread([&a, i](){
			if(++a[i][2] != '1')
				cout<<"gotcha"<<endl;
			//cout << "Hello from thread " << this_thread::get_id() << ", my string say "<< a[i] << endl;
		}));
	}

	for(auto& thread: threads)
		thread.join();
	
	for(int i = 0; i < N; ++i)
		cout<< (unsigned*)(a[i].c_str()) <<endl;

	return 0;
}
