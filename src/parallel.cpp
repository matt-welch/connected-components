/*******************************************************************************
 * FILENAME:	parallel.cpp
 * DESCRIPTION:	Connected Graph Components Driver console program - parallel version
 * AUTHOR: 		James Matthew Welch [JMW]
 * SCHOOL:		Arizona State University
 * CLASS:		CSE430::Operating Systems
 * INSTRUCTOR:	Dr. Violet Syrotiuk
 * SECTION:		19464
 * TERM:		Spring 2012
 ******************************************************************************/

/*******************************************************************************
 *  Disjoint Set methods, when possible, are adapted from pseudocode provided in
 * _Introduction_to_Algorithms_ (Cormen, Leiserson, Rivest & Stein)
 *
 * Some code-conventions taken from:
 * 		C++ Programming Practicum (Spring 2012)
 ******************************************************************************/

/* Connected Graph Components Driver Program :  */
#include <omp.h>
#include <stdlib.h> // atoi(), exit()
#include <string>
using std::string;

#include <ctime>
using namespace std;

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;

#include "GraphNode.hpp"

//#define DEBUG

int** graph;
GraphNode** list;
int numNodes;


void PrintDisjointSet(int* disjointSet, int numSets){
	cout << "Disjoint Set Representation:(" << numSets << ")" << endl
			<< "[";
	for(int i = 1; i <= numNodes; ++i){
		if(i!=1)
			cout << ", ";
		cout << disjointSet[i];
	}
	cout << "]" << endl;
}

void printMatrix(int** graph, int numNodes){
	cout << "Graph Adjacency Matrix::" << endl;
	for(int i=1; i<numNodes+1; ++i){
		//print adjacency matrix contents
		for(int j = 1; j<numNodes+1; ++j){
			cout << graph[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void printVectorMatrix(vector< vector<int> > array){
	cout << "Graph Adjacency Matrix (vectors)::" << endl;
	cout << "Array size = " << array.capacity() << endl;

	for(vector< vector<int> >::const_iterator x = array.begin();
			x != array.end();
			++x)
	{
		for(vector<int>::const_iterator cell = x->begin();
				cell != x->end();
				++cell)
		{
			cout << *cell;
		}
		cout << endl;
	}
	cout << endl;
}

// beginning of Connected Components driver
int main(int argc, char* argv[]){
	ifstream infile;
	int neighbors;
	string token;
	bool quiet = false;
	bool verbose = false;

	// get time for start of the program
	struct timeval start, end;
	long seconds, useconds;
	gettimeofday(&start, NULL);

	// default filename if no 2nd arg provided at cmd line
	string inFileName = "graph.txt";

	//=======================================================
	if (argc > 1){ // argc should be 2 for correct execution
		inFileName = argv[1];
		if(argc > 2){
			string runFlag(argv[2]);
			if(runFlag.compare("-q") == 0){
				quiet = true;
				verbose = false;
			}else if(runFlag.compare("-v") == 0){
				quiet = false;
				verbose = true;
			}

		}
	}
	//=======================================================

	// ifstream.open() requires a const char*
	infile.open((char*)inFileName.c_str()); //2nd arg: ifstream::in

	if(infile.fail()){
		cout << endl <<"An error occurred while reading from the file \""
				<< inFileName << "\"." << endl;
		exit(1);
	}else{
		// read the nodes in from the graph
		infile >> numNodes; // read in the number of nodes from the first line

		// create adjacency matrix here (one more row than needed so can ignore row-0
		graph = new int*[numNodes+1];

#pragma omp parallel for shared(graph, numNodes)
		for(int i=0; i < numNodes+1; ++i){
			graph[i] = new int[numNodes + 1];
			//initialize graph to zeroes
			for(int j = 0; j < numNodes+1; ++j){
				graph[i][j] = 0;
			}
		}

		for(int i=1; i<=numNodes; ++i){
			infile >> neighbors;
			for(int j=1; j <= neighbors; ++j){
				infile >> token;
				graph[i][atoi(token.c_str())] = 1;
			}
		}

#ifdef DEBUG
		cout << "Filled::" << endl;
		printMatrix(graph, numNodes);
#endif

		infile.close();
#ifdef NOTNEEDED
		cout <<"A graph with "<< numNodes <<" nodes has been read in from the file \"" << inFileName << "\"." << endl;
#endif
	}

	// take graph file and determine the number of connected components
	// initialize sets (while building nodes)
	list = new GraphNode*[numNodes+1];
	int disjointSet[numNodes+1];
	bool visited[numNodes+1];
	int numSets = numNodes;  // numSets is initially == numNodes
#pragma omp parallel for shared(list, disjointSet, numNodes, visited)
	for(int i=0; i<=numNodes; ++i){
		// Makes new nodes for each vertex & MakeSet(this) on each
		list[i] = new GraphNode(i);
		disjointSet[i] = i;
		visited[i] = false;
	}
	disjointSet[0] = numNodes;

#ifdef DEBUG
	PrintDisjointSet(disjointSet, numSets);
#endif
	// connected-components algorithm:
	// each node is already its own set
	// loop through each node's neighbors, connecting components
	//#pragma omp parallel for shared(numSets, disjointSet, numNodes)
//	int numUnions = 0;
#pragma omp parallel for shared(graph, list, disjointSet, numNodes, verbose)
	for(int i=1; i<=numNodes; ++i){
		// get parent of current node
		GraphNode* currentParent = list[i]->FindSet();
		for(int j=1; j<=numNodes; ++j){
			if(graph[j][i]==1 ){
				GraphNode* nextParent = list[j]->FindSet();
				// there is an edge between node-i & node-j
				if(currentParent != nextParent ){
					// we are not yet in the same set
					// union the two sets
					list[i]->Union(list[j]);

					// use parent of lower rank
					if(disjointSet[j] > disjointSet[i]){
						// probably not in a set yet
						disjointSet[j] = disjointSet[i];
					}
					else{
						disjointSet[i] = disjointSet[j];
					}
					//#pragma omp parallel atomic
//					numSets--;// remove one set from the count on union
//					numUnions++;

#ifdef DEBUG
					cout << "Union(" << i << ", " << j << ")" << endl;
					if(verbose)
						PrintDisjointSet(disjointSet, numSets);
#endif
				}
			}
		}
	}
	// hold the number of sets in the array
	disjointSet[0] = numSets;

#if DEBUG
	PrintDisjointSet(disjointSet, numSets);
#endif

	// determine Same-Components, create printable results
#ifdef DEBUG
	cout << ":::OUTPUT:::" << endl;
#endif

	// print the number of sets prior to printing the contents of each set:
	stringstream outputBuffer;
	int setCount = 0;

	/* this section cannot currently be parallelized because of the serial nature of the analysis
	 * it is currently dependent on lower-numbered sets having been visited first */
	for(int i = 1; i<=numNodes; ++i){
		stringstream buffer;
		int setSize = 0;
		//		int setNum = disjointSet[i];
		GraphNode* currentSet = list[i]->FindSet();
		if(!visited[i]){
			for(int j = i; j<=numNodes; ++j){
				if(list[j]->FindSet() == currentSet){
					//				if(disjointSet[j] == i)
					// the parent of j is i
					++setSize;
					if(j>i)
						buffer << " ";
					buffer << j;
					visited[j] = true;
				}
			}

			if(setSize>0){
				if(disjointSet[i] != disjointSet[i-1] || numSets == 1 ){// new set
					string temp = buffer.str();
					buffer.str("");
					buffer << setSize << "\n" << temp << "\n";
					++setCount;
				}
				if(!quiet)
					outputBuffer << buffer.str();
			}
		}
	}

	cout << setCount << endl;
	cout << outputBuffer.str();

	// free nodes to prevent memory leaks (although there's really no point to this

	// print program elapsed time
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	double preciseTime = seconds + useconds/1000000.0;

	cout.precision(10);

	cout << "Elapsed Program Time: " << preciseTime << " s" << endl;

//	cout << "Total number of Sets\t= "<< numSets << endl;
//	cout << "Total number of Unions\t= "<< numUnions << endl;
	cout << "Total number of Sets = "<< setCount << endl;
	cout << endl;

	return 0;
}
