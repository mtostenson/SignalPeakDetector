//---------------------------------------------------------
// PeakDetector.h
//---------------------------------------------------------

#ifndef _PEAKDETECTOR_H_
#define _PEAKDETECTOR_H_

#include <stdio.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class PeakDetector
{	
public:
	PeakDetector(char*&);
	void analyze();
	void print(std::vector<double>&);
private:	
	class Spike
	{
	public:
		Spike(double p1_in, double p2_in, double p3_in)
		: p1(p1_in)
		, p2(p2_in)
		, p3(p3_in){}
		double length(){ return (p2 - p1) + (p2 - p3); }
		double p1, p2, p3;
	};
	std::ifstream fs;
	std::vector<double> values;
	std::vector<Spike*> spikes;
	std::vector<double> peaks;
	std::vector<double>::iterator iter;
};

int main(int argc, char* argv[])
{
	if(argc > 1)
		PeakDetector PeakDetector(argv[1]);
	else
		fprintf(stderr, "Please give data source filename as first parameter.\n");
	return 0;
}

#endif // _PEAKDETECTOR_H_