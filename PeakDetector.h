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
	std::ifstream fs;
	std::vector<double> values;
	std::vector<double> differences;
	std::vector<double> averages;
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