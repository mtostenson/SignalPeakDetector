#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> peakIndeces;

void readValues(std::ifstream& fs, std::vector<double>& values)
{
	double value;
	fs.clear();
	fs.seekg(0, std::ios::beg);
	while (!fs.eof())
	{
		fs >> value;
		values.push_back(value);
	}
}

void print(std::vector<double>& values, std::vector<double>::iterator& iter)
{
	int curPos;
	std::vector<int>::iterator iter2 = peakIndeces.begin();
	for (iter = values.begin(); iter != values.end() - 1; iter++)
	{
		fprintf(stdout, "%f", *iter);
		if (*iter2 == curPos)
		{
			fprintf(stdout, " PEAK");
			iter2++;
		}
		fprintf(stdout, "\n");
		curPos++;
	}
	fprintf(stdout, "-------------------------------------------------\n");
	fprintf(stdout, "TOTAL VALUES: %d\n", (int)values.size());
	fprintf(stdout, "-------------------------------------------------\n");
}

void analyze(std::vector<double>& values, std::vector<double>::iterator& iter)
{
	int pos;
	int peaks;
	int vals[3];
	for (iter = values.begin(); iter != values.end(); iter++)
	{
		vals[0] = vals[1];
		vals[1] = vals[2];
		vals[2] = *iter;
		if (vals[0] < vals[1] && vals[2] < vals[1])
		{
			peaks++;
			peakIndeces.push_back(pos - 1);
		}
		pos++;
	}
	fprintf(stdout, "-------------------------------------------------\n");
	fprintf(stdout, "TOTAL PEAKS: %d\n", peaks);
}

int main(int argc, char* argv[])
{
	std::ifstream fs;
	std::vector<double> values;
	std::vector<double>::iterator iter;
	if (argc > 1)
	{
		fs.open(argv[1]);
		if (!fs.is_open())
		{
			fprintf(stderr, "FILE \"%s\" NOT FOUND.\n", argv[1]);
			return 0;
		}
	}
	else
	{
		fprintf(stderr, "NO SOURCE FILE SPECIFIED.\n");
		return 0;
	}	
	readValues(fs, values);
	analyze(values, iter);
	print(values, iter);
	return 0;
}