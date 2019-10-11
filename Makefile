CFLAGS=-g

all : test

test : main.o circuit.o connection.o node.o
		g++ -o test1 $^ $(LDFLAGS)

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test1
