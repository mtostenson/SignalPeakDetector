#include "PeakDetector.h"
using namespace std;

PeakDetector* PeakDetector::m_instance = 0;

void PeakDetector::analyze(string& filename)
{}

PeakDetector* PeakDetector::instance()
{
	if(!m_instance) m_instance = new PeakDetector();
	return m_instance;
}
