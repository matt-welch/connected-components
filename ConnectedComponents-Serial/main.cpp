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

#define DEBUG

int** graph;
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

// beginning of Connected Components driver
int main(){
	ifstream infile;
	string inFileName = "graph.txt";
	int neighbors;
	string token;

	// ifstream.open() reauires a const char* 
	infile.open((char*)inFileName.c_str()); //2nd arg: ifstream::in

	if(infile.fail()){
		cout << endl <<"An error occurred while reading from the file \""
			<< inFileName << "\"." << endl;
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

#ifdef DEBUG
		cout << "Initialized::" << endl;
		printMatrix(graph, numNodes);
#endif

		for(int i=1; i<=numNodes; ++i){
			infile >> neighbors;

#ifdef DISABLE
			cout << neighbors << endl;
#endif
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
		cout << endl <<"A graph has been read in from the file \"" << inFileName << "\"." << endl;
	}

	cout << endl << endl << "Microsoft Visual Studio 2010 is shite!!!" << endl << endl;

	return 0;
}
