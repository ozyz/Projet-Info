CFLAGS=-g

all : test1

test1 : circuit.o node.o test_node.o
		g++ -o test1 $^ $(LDFLAGS)

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test1
