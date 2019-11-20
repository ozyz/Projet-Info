CFLAGS=-g

all : test1

<<<<<<< HEAD
test : main.o circuit.o node.o
=======
test1 : circuit.o node.o test_node.o
>>>>>>> 9b9b75f86099581548b820c7f6944456215ac89c
		g++ -o test1 $^ $(LDFLAGS)

%.o:%.cc
	g++ -std=c++11 $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test1
