CFLAGS=-g

all : test

test : main.o circuit.o node.o
		g++ -o test1 $^ $(LDFLAGS)

%.o:%.cc
	g++ -std=c++11 $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test1
