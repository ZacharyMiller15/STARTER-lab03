CXX_FLAG = --std=c++11 -g

all: testbst

testbst: testbst.o intbst.o
	g++ $(CXX_FLAG) -o testbst testbst.o intbst.o

testbst.o: testbst.cpp intbst.h
	g++ -c $(CXX_FLAG) testbst.cpp

intbst.o: intbst.cpp intbst.h
	g++ -c $(CXX_FLAG) intbst.cpp

clean:
	rm -f testbst *.o