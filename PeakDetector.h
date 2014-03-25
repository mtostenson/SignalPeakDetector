//---------------------------------------------------------
// PeakDetector.h
//---------------------------------------------------------

#ifndef _PEAKDETECTOR_H_
#define _PEAKDETECTOR_H_

#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

class PeakDetector
{	
public:
	static PeakDetector* instance();
	void analyze(std::string& filename);
	std::ifstream* get_fs() { return &fs; }
private:
	static PeakDetector* m_instance;
	PeakDetector(){}
	std::ifstream fs;
};

int main(int argc, char* argv[])
{
	PeakDetector* pd = PeakDetector::instance();
	if(argc > 1)
	{
		pd->get_fs()->open(argv[1]);
		if(pd->get_fs()->is_open())
			fprintf(stdout, "File opened successfully.\n");
		else
			fprintf(stderr, "File \'%s\' not opened.\n", argv[1]);
	}
	else
		fprintf(stderr, "Please give data source filename as first parameter.\n");
	return 0;
}

#endif // _PEAKDETECTOR_H_