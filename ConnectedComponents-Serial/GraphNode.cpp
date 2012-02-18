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

GraphNode::GraphNode(int vertexNumber){
	// constructor for GraphNodes - replaces need to MakeSet on each
	_parent = this;
	_vertex = vertexNumber;
	_rank = 0;
}

GraphNode::~GraphNode(){
}

void GraphNode::MakeSet(){
	this->_parent = this;
	this->_rank = 0;
}

void GraphNode::Union(GraphNode *y){
	Link(this->FindSet(), y->FindSet());
}

void GraphNode::Link(GraphNode *x, GraphNode *y){
	if(x->_rank > y->_rank)
		y->_parent = x;
	else{
		x->_parent = y;
		if(x->_rank == y->_rank)
			y->_rank++;
	}
}

GraphNode* GraphNode::FindSet(){
	if(this != this->_parent)
		this->_parent = this->_parent->FindSet();
	return this->_parent;
}
