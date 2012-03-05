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
	InitMembers();
}

GraphNode::GraphNode(int vertexNumber){
	// constructor for GraphNodes - replaces need to MakeSet on each
	_vertex = vertexNumber;
	InitMembers();
}

void GraphNode::InitMembers(){
	MakeSet();
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
/*	if(x->_vertex < y->_vertex)
		y->_parent = x;
	else{
		x->_parent = y;
	}*/
}

GraphNode* GraphNode::FindSet(){
	if(this != this->_parent)
		this->_parent = this->_parent->FindSet();
	return this->_parent;
}

string GraphNode::ToString(){
	stringstream output;
	output << "V: " << _vertex <<
			", P: " << _parent->GetVertex() <<
			", R: " << _rank;
	return output.str();
}
