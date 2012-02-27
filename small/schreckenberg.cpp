#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

int compare(const void * a, const void * b) {return ( *(int*)a - *(int*)b );}
float frand() {return rand()/(float)RAND_MAX;}

int main(int argc, char** argv)
{
	if(argc!=6)
	{
		cout<<"usage: "<<argv[0]<<" road_len car_count max_rounds vel_max p"<<endl;
		return 1;
	}
	const char outfile[] = "schreckenberg.dat";
	const int road_len   = atoi(argv[1]);
	const int car_count  = atoi(argv[2]);
	const int max_rounds = atoi(argv[3]);
	const int vel_max    = atoi(argv[4]);
	const float p        = atof(argv[5]);
	/*cout<<"road_len   = "<<road_len<<"\n"
	      "car_count  = "<<car_count<<"\n"
	      "max_rounds = "<<max_rounds<<"\n"
	      "vel_max    = "<<vel_max<<"\n"
	      "p          = "<<p<<endl;
	*/
	int* car_pos = new int[car_count];
	int* car_round = new int[car_count];
	int* car_vel = new int[car_count];

	// create random start positions
	srand(time(0));
	int* temp = new int[road_len];
	for(int i=0; i<road_len; ++i) temp[i] = i;
	for(int i=0; i<road_len; ++i)
	{
		int r = i + rand() % (road_len-i);
		int t = temp[r]; temp[r] = temp[i]; temp[i] = t;
	}
	qsort(temp, car_count, sizeof(int), compare);
	for(int i=0; i<car_count; ++i)
	{
		car_round[i] = 0;
		car_vel[i] = 0;
		car_pos[i] = temp[i];
	}
	delete [] temp;
	
	// ofstream out(outfile);
	{
		// start the simulation
		int r=0;
		while(true)
		{
			//out<<r;
			//for(int i=0; i<car_count; ++i)
			//	out<<"\t"<<(car_round[i]*road_len+car_pos[i]);
			//out<<endl;
			
			if(++r >= max_rounds) break;
			
			// rules:
			// (a) accelerate
			for(int i=0; i<car_count; ++i)
				if(car_vel[i] < vel_max) ++car_vel[i];
			
			// (b) slowing down
			for(int i=0; i<car_count; ++i)
			{
				int free_space = (car_pos[(i+1)%car_count] - car_pos[i] + road_len - 1) % road_len;
				if(car_vel[i] > free_space) car_vel[i] = free_space;
			}
			
			// (c) randomization
			for(int i=0; i<car_count; ++i)
				if(car_vel[i]>0 && frand() <= p) --car_vel[i];
			
			// (d) motion
			for(int i=0; i<car_count; ++i)
			{
				car_pos[i] += car_vel[i];
				if(car_pos[i] >= road_len)
				{
					car_pos[i] -= road_len;
					++car_round[i];
				}
			}
		}
	}
	// out.close();
	
	double v_m=0.0;
	for(int i=0; i<car_count; ++i) v_m += (car_round[i]*road_len+car_pos[i])/(1.0*max_rounds);
	v_m /= (1.0 * car_count);
	cout<<(car_count*v_m)<<endl;
	
	delete [] car_vel;
	delete [] car_round;
	delete [] car_pos;
	
	// cout<<"Done. See file \""<<outfile<<"\"."<<endl;

	return 0;
}
