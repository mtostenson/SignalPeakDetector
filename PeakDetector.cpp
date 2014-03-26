#include "PeakDetector.h"
using namespace std;

// Constants
const double c_THRESHOLD = 3.0;
const int c_RANGE = 10;

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
	int num_spikes;
	double* p1, *p2, *p3;
	p2 = p3 = NULL;
	iter = values.begin();
	p1 = &*iter;
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
		if ((*spike_iter)->length() >(c_THRESHOLD * local_avg))
			peaks.push_back((*spike_iter)->p2);
	}
	print(peaks);
}

void PeakDetector::print(vector<double>& vec)
{
	for(iter = vec.begin(); iter != vec.end(); iter++)
		fprintf(stdout, "%f\n", *iter);
}