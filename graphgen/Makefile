graphgen: graphgen-linux.o
	g++ -o graphgen graphgen-linux.cpp

graphgen-linux.o: graphgen-linux.cpp
	g++ -c $(CONFIG) graphgen-linux.cpp
	
clean:
	rm -f graphgen *.o core core.*

tidy: clean
	rm -f *.*~ *~

DEBUG_FLAGS = -g3 -ggdb -O0 -Wall -pedantic -DDEBUG
CONFIG	= -Wall -pedantic
EASY_FLAGS = 


debug: CONFIG=$(DEBUG_FLAGS)
debug: connected

easy: CONFIG=$(EASY_FLAGS)
easy: connected
