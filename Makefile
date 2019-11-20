CFLAGS=-g

all : test1

test1 : circuit.o node.o test_node.o
		g++ -o test1 $^ $(LDFLAGS)

test2: circuit.o node.o main.o
		g++ -o test2 $^ $(LDFLAGS)

%.o:%.cc
	g++ -std=c++11 $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test1
