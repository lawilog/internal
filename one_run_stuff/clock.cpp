#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	/*
	for(int n=0, i=0; i<100000; ++i) n+=i;
	const double clocks_per_sec = CLOCKS_PER_SEC;
	clock_t cpu_exec_start_time = clock();
	cout<<"cpu_exec_start_time = " << cpu_exec_start_time << endl;
	for(int n=0, i=0; i<100000; ++i) n+=i;
	double cpu_exec_time = (clock() - cpu_exec_start_time) / clocks_per_sec;
	cout<<"cpu_exec_time = " << cpu_exec_time << "s" << endl;
	*/
	
	time_t t_start, t_end;
	time(& t_start);
	int n; cout<<"n = "; cin>>n;
	time(& t_end);
	double t_diff = difftime(t_end, t_start);
	cout<<"t_diff = " << t_diff << endl;
	
	return 0;
}
