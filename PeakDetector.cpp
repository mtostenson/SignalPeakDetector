#include "PeakDetector.h"
using namespace std;

// Constants ----------------------------------------------
const double c_THRESHOLD = 3.0;
const int c_RANGE = 20;
//---------------------------------------------------------

//---------------------------------------------------------
// PeakDetector Constructor
//
// Attempts to open file received as parameter. Continues
//   execution if successful, otherwise exits program.
//---------------------------------------------------------
PeakDetector::PeakDetector(char*& filename)
{
	fs.open(filename);
	if (fs.is_open())
	{
		analyze();
		print(peaks);
	}
	else
		fprintf(stderr, "File \'%s\' not opened.\n", filename);
}

//---------------------------------------------------------
// PeakDetector::analyze()
//
// Detects peak values from the input data. The data is
//   evaluated into discrete 'spikes.' 
// The length of each spike is calculated and compared to 
//   the average of its neighboring spikes based on 
//   c_RANGE, and is considered a peak if its length is 
//   greater than the neighboring averages multiplied by 
//   c_THRESHOLD.
//---------------------------------------------------------
void PeakDetector::analyze()
{
	double buffer;
	while(!fs.eof())
	{
		fs >> buffer;
		values.push_back(buffer);
	}	
	int num_spikes;
	double* p1, *p2, *p3;
	p1 = &*values.begin();
	for (iter = values.begin(); iter + 1 < values.end(); iter++)
	{
		if (*(iter + 1) < *iter)
		{
			if (!p2)
				p2 = &*iter;
		}
		else
		{
			if (p2)
			{
				p3 = &*iter;
				spikes.push_back(new Spike(*p1, *p2, *p3));
				p1 = p3;
				p2 = p3 = NULL;
				num_spikes++;
			}
		}
	}
	for (vector<Spike*>::iterator spike_iter = spikes.begin();
	spike_iter < spikes.end(); spike_iter++)
	{
		vector<Spike*>::iterator spike_iter2;
		double local_avg;
		if (spike_iter < spikes.begin() + c_RANGE)
		{
			spike_iter2 = spike_iter + 1;
			for (int i = 0; i < c_RANGE; i++, spike_iter2++)
				local_avg += (*spike_iter2)->length();
		}
		else
		{
			if (spike_iter > spikes.end() - c_RANGE)
			{
				spike_iter2 = spike_iter - 1;
				for (int i = 0; i < c_RANGE; i++, spike_iter2--)
					local_avg += (*spike_iter2)->length();
			}
			else
			{
				spike_iter2 = spike_iter + 1;
				for (int i = 0; i < c_RANGE / 2; i++, spike_iter2++)
					local_avg += (*spike_iter2)->length();
				spike_iter2 = spike_iter - 1;
				for (int i = 0; i < c_RANGE / 2; i++, spike_iter2--)
					local_avg += (*spike_iter2)->length();
			}
		}
		local_avg = local_avg / c_RANGE;
		if ((*spike_iter)->length() > (c_THRESHOLD * local_avg))
			peaks.push_back((*spike_iter)->p2);
	}
}

//---------------------------------------------------------
// PeakDetector::print
//
// Prints all the values in a vector of doubles.
//---------------------------------------------------------
void PeakDetector::print(vector<double>& vec)
{
	for(iter = vec.begin(); iter != vec.end(); iter++)
		fprintf(stdout, "%f\n", *iter);
}