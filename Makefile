CC=g++

all: PeakDetector.h PeakDetector.cpp
	$(CC) -o PeakDetector PeakDetector.h PeakDetector.cpp

clean:
	rm PeakDetector