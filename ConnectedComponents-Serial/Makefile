connected: main.o GraphNode.o
	g++ -o connected main.o GraphNode.o

main.o: main.cpp
	g++ -c $(CONFIG) main.cpp
	
GraphNode.o: GraphNode.cpp
	g++ -c $(CONFIG) GraphNode.cpp

clean:
	rm -f connected *.o core core.*

tidy: clean
	rm -f *.*~ *~

DEBUG_FLAGS = -g3 -ggdb -O0 -Wall -pedantic -DDEBUG
CONFIG		= -Wall -pedantic
EASY_FLAGS	= 


debug: CONFIG=$(DEBUG_FLAGS)
debug: connected

easy: CONFIG=$(EASY_FLAGS)
easy: connected