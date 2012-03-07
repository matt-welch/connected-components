all: parallel connected

intel: parallel_i.o GraphNode_i.o main_i.o
	icpc -o parallel -openmp parallel_i.o GraphNode_i.o
	icpc -o connected -openmp main_i.o GraphNode_i.o

parallel_i.o: GraphNode_i.o
	icpc -c parallel.cpp -openmp -o parallel_i.o

GraphNode_i.o: GraphNode.cpp GraphNode.hpp
	icpc -c GraphNode.cpp -openmp -o GraphNode_i.o

main_i.o: main.cpp GraphNode.cpp GraphNode.hpp
	icpc -c main.cpp -openmp -o main_i.o

parallel: parallel.o GraphNode.o
	g++ -o parallel -fopenmp parallel.o GraphNode.o

parallel.o: parallel.cpp GraphNode.cpp GraphNode.hpp
	g++ -c $(PARCONFIG) parallel.cpp

connected: main.o GraphNode.o
	g++ -o connected main.o GraphNode.o

main.o: main.cpp  GraphNode.cpp GraphNode.hpp
	g++ -c $(CONFIG) main.cpp
	
GraphNode.o: GraphNode.cpp
	g++ -c $(CONFIG) GraphNode.cpp

clean:
	rm -f connected parallel *.o core core.*

tidy: clean
	rm -f *.*~ *~

DEBUG_FLAGS = -g3 -ggdb -O0 -Wall -pedantic -DDEBUG
INTEL_FLAGS = -openmp
CONFIG		= -Wall -pedantic
PARCONFIG	= -fopenmp
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
