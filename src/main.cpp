/*******************************************************************************
 * FILENAME:	main.cpp
 * DESCRIPTION:	Connected Graph Components Driver console program
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

#include <stdlib.h> // atoi(), exit()
#include <string>
using std::string;

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

	// default filename if no 2nd arg provided at cmd line
	string inFileName = "graph.txt";

	//=======================================================
	if (argc == 2){ // argc should be 2 for correct execution
		inFileName = argv[1];
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
		cout <<"A graph with "<< numNodes <<" nodes has been read in from the file \"" << inFileName << "\"." << endl;
	}

	// take graph file and determine the number of connected components
	// initialize sets (while building nodes)
	list = new GraphNode*[numNodes+1];
	int disjointSet[numNodes+1];

	for(int i=0; i<=numNodes; ++i){
		// Makes new nodes for each vertex & MakeSet(this) on each
		list[i] = new GraphNode(i);
		disjointSet[i] = i;
	}
	disjointSet[0] = numNodes;
#ifdef DEBUG
	cout << "Disjoint Set Representation: sets=" << disjointSet[0] << endl
			<< "[";
	for(int i = 1; i <= numNodes; ++i){
		if(i!=1)
			cout << ", ";
		cout << disjointSet[i];
	}
	cout << "]" << endl;
#endif
	// connected-components algorithm:
	// each node is already its own set
	// loop through each node's neighbors, connecting components
	int numSets = numNodes;  // numSets is initially == numNodes
	for(int i=1; i<=numNodes; ++i){
		for(int j=1; j<=numNodes; ++j){
			if(graph[j][i]==1 && (list[i]->FindSet() != list[j]->FindSet()) ){
				list[i]->Union(list[j]);
				if(j>i)
					disjointSet[j] = disjointSet[i];
				else
					disjointSet[i] = disjointSet[j];
#ifdef DEBUG
				cout << "Union(" << i << ", " << j << ")" << endl;
#endif
				numSets--;// remove one set from the count on union
			}
		}
	}
	// hold the number of sets in the array
	disjointSet[0] = numSets;

#ifdef DEBUG
	cout << "Disjoint Set Representation: sets=" <<  disjointSet[0] << endl
			<< "[";
	for(int i = 1; i <= numNodes; ++i){
		if(i!=1)
			cout << ", ";
		cout << disjointSet[i];
	}
	cout << "]" << endl;
#endif

	// determine Same-Components, create printable results
#ifdef DEBUG
	cout << ":::OUTPUT:::" << endl;
#endif
	cout << numSets << endl;

	for(int i = 1; i<=numNodes; ++i){
		stringstream buffer;
		int setSize = 0;
		buffer << setSize << endl << buffer.str();
#ifdef DEBUG
		cout << "Set Rep: ";
#endif
		for(int j = i; j<=numNodes; ++j){
			if(disjointSet[j] == i){
#ifdef DEBUG
				cout << j << ", " << disjointSet[j] << endl;
#endif
				++setSize;
				if(j>i)
					buffer << ", ";
				buffer << j;
			}
		}
	}

	cout << endl << endl;
	return 0;
}
