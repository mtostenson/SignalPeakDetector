#include "PeakDetector.h"
using namespace std;

PeakDetector::PeakDetector(char*& filename)
{
	fs.open(filename);
	if(fs.is_open())
		analyze();
	else
	{
		fprintf(stderr, "File \'%s\' not opened.\n", filename);
		return;
	}
}

void PeakDetector::analyze()
{
	double buffer;
	while(!fs.eof())
	{
		fs >> buffer;
		values.push_back(buffer);
	}

	int count, sum;
	double d1, d2;
	for(iter = values.begin(); iter != values.end(); iter++, count++)
	{
		d1 = d2;
		d2 = *iter;
		differences.push_back(d2 - d1);
		sum += (d2 - d1);
		if(!(count % 8))
		{
			averages.push_back(sum / 8.0);
			sum = 0;
		}
	}
	//sort(averages.begin(), averages.end());
	print(differences);
}

void PeakDetector::print(vector<double>& vec)
{
	for(iter = vec.begin(); iter != vec.end(); iter++)
		fprintf(stdout, "%f\n", *iter);
}