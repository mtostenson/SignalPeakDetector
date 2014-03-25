#include "PeakDetector.h"
using namespace std;

PeakDetector::PeakDetector(char*& filename)
{
	fs.open(filename);
	if(fs.is_open())
		analyze();
	else
		fprintf(stderr, "File \'%s\' not opened.\n", filename);
}

void PeakDetector::analyze()
{
	double buffer;
	while(!fs.eof())
	{
		fs >> buffer;
		values.push_back(buffer);
	}

	// Gathering all slopes
	double p1, p2, slope_sum;
	for(iter = values.begin(); iter < values.end(); iter++)
	{
		p2 = *iter;
		slopes.push_back(p2 - p1);
		slope_sum += (p2 - p1);
		p1 = p2;
	}
	print(slopes);

	// Gathering rising edges
	for(iter = values.begin(); iter < values.end(); iter++)
	{
		if(*iter < p2)
		{
			if(p2 > p1)
				rising_edges.push_back(p2 - p1);
			p1 = *iter;			
		}
		else
			p2 = *iter;
	}
}

void PeakDetector::print(vector<double>& vec)
{
	for(iter = vec.begin(); iter != vec.end(); iter++)
		fprintf(stdout, "%f\n", *iter);
}