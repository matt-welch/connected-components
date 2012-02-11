/*******************************************************************************
 * FILENAME:	GraphNode.cpp
 * DESCRIPTION:	Graph Node (for disjoint data set) Member Function Definitions
 * AUTHOR: 		James Matthew Welch [JMW]
 * SCHOOL:		Arizona State University
 * CLASS:		CSE430::Operating Systems
 * INSTRUCTOR:	Dr. Violet Syrotiuk
 * SECTION:		19464
 * TERM:		Spring 2012
 ******************************************************************************/
#include "GraphNode.hpp"

GraphNode::GraphNode(){
}

GraphNode::~GraphNode(){
}

void GraphNode::MakeSet(GraphNode &x){
	x._parent = &x;
	x._rank = 0;
}

//void GraphNode::Union(GraphNode &x, GraphNode &y){
//	Link(FindSet(x), FindSet(y));
//}

void GraphNode::Link(GraphNode &x, GraphNode &y){
	if(x._rank > y._rank)
		y._parent = x._parent;
	else{
		x._parent = &y;
		if(x._rank == y._rank)
			y._rank = y._rank + 1;
	}
}

//GraphNode GraphNode::FindSet(GraphNode x){
//	if(x != x._parent)
//		x._parent = FindSet(x._parent);
//	return x._parent;
//}
