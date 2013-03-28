#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Interval
{
	double min;
	double max;
	string descr;
};

typedef vector<Interval> IntervalList;

IntervalList combineIntervals(const IntervalList& intervals)
{
	if(intervals.size() <= 1) return intervals;
	
	IntervalList sorted_intervals = intervals;
	sort(sorted_intervals.begin(), sorted_intervals.end(),
		 [](const Interval& a, const Interval& b) {return a.min < b.min;}
	);
	IntervalList regions = {sorted_intervals.front()};
	for(auto reg = sorted_intervals.begin() + 1; reg != sorted_intervals.end(); ++reg)
	{
		Interval& last_reg = regions.back();
		if(reg->min > last_reg.max) // new interval starts after old region ends
			regions.push_back(*reg); // so create own new region
		else // new interval overlaps
		{
			if(reg->max > last_reg.max) last_reg.max = reg->max;
			
			if(last_reg.descr.empty()) last_reg.descr = reg->descr;
			else last_reg.descr += reg->descr;
		}
	}
	
	return regions;
}

void process_input(istream& input)
{
	IntervalList intervals;
	bool go_on = true;
	while(go_on)
	{
		Interval inv;
		input >> inv.min >> inv.max;
		go_on = input.good();
		getline(input, inv.descr);
		if(go_on) intervals.push_back(inv);
	}
	
	const IntervalList regions = combineIntervals(intervals);
	for(const Interval& reg: regions)
		cout<< reg.min <<' '<< reg.max <<'\t'<< reg.descr << endl;
};

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		ifstream f(argv[1]);
		process_input(f);
	}
	else
		process_input(cin);
	
	return 0;
}
