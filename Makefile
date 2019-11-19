CFLAGS=-g

all : test

test : main.o circuit.o node.o test_node.o
		g++ -o test1 $^ $(LDFLAGS)

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test1
