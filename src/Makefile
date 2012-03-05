all: parallel connected

parallel: parallel.o GraphNode.o
	g++ -o parallel -fopenmp parallel.o GraphNode.o

connected: main.o GraphNode.o
	g++ -o connected main.o GraphNode.o

parallel.o: parallel.cpp
	g++ -c $(PARCONFIG) parallel.cpp

main.o: main.cpp
	g++ -c $(CONFIG) main.cpp
	
GraphNode.o: GraphNode.cpp
	g++ -c $(CONFIG) GraphNode.cpp

clean:
	rm -f connected parallel *.o core core.*

tidy: clean
	rm -f *.*~ *~

DEBUG_FLAGS = -g3 -ggdb -O0 -Wall -pedantic -DDEBUG
CONFIG		= -Wall -pedantic
PARCONFIG	= -Wall -pedantic -fopenmp
PARDEBUG	= -g3 -ggdb -O0 -Wall -pedantic -DDEBUG -fopenmp
EASY_FLAGS	= 


debug: CONFIG=$(DEBUG_FLAGS)
debug: connected
debug: PARCONFIG=$(PARDEBUG)
debug: parallel



easy: CONFIG=$(EASY_FLAGS)
easy: parallel connected

test: debug
	./parallel
