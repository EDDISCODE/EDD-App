CFLAGS=-Wno-sign-compare -Wno-write-strings -I/usr/include/opencv -I/usr/include/opencv2 -L/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_legacy -lopencv_features2d

all: go

go: Segmentation.o TestUtils.o Runner.o
	g++ Segmentation.o TestUtils.o Runner.o $(CFLAGS) -o go

Runner.o: Runner.cpp Runner.h Segmentation.cpp Segmentation.h TestUtils.cpp TestUtils.h
	g++  -c Runner.cpp $(CFLAGS)

Segmentation.o: Segmentation.cpp Segmentation.h TestUtils.cpp TestUtils.h 
	g++  -c Segmentation.cpp $(CFLAGS)

TestUtils.o: TestUtils.cpp TestUtils.h
	g++  -c TestUtils.cpp $(CFLAGS)

clean: 
	rm *.o go
