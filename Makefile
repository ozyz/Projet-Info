CFLAGS=-g -std=c++11
VCD_OBJS=./build/VCDFile.o ./build/VCDParser.o  ./build/VCDValue.o ./build/VCDFileParser.o  build/VCDScanner.o

all : test2

test_node : node.o test_node.o
	g++ -o test_node $^ $(LDFLAGS)

test2: circuit.o node.o main.o
	g++ -o test2  $^ $(LDFLAGS) $(VCD_OBJS)

test_circuit1: circuit.o node.o test_circuit1.o
		g++ -o test_circuit1 $^ $(LDFLAGS)

%.o:%.cc
	g++ -std=c++11 $(CFLAGS) -c -g $^

%.o:%.cpp
	g++ -std=c++11 $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test1 test2
