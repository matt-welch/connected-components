/*******************************************************************************
 * FILENAME:	GraphNode.hpp
 * DESCRIPTION:	Graph Node (for disjoint data set) Class Declaration
 * AUTHOR: 		James Matthew Welch [JMW]
 * SCHOOL:		Arizona State University
 * CLASS:		CSE430::Operating Systems
 * INSTRUCTOR:	Dr. Violet Syrotiuk
 * SECTION:		19464
 * TERM:		Spring 2012
 ******************************************************************************/

#ifndef __GRAPHNODE_HPP__
#define __GRAPHNODE_HPP__
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

// Graph Node class declaration
class GraphNode {
public: 
// methods
				GraphNode(void);
	virtual		~GraphNode(void);
	void		MakeSet(GraphNode &x);
	void		Union(GraphNode &x, GraphNode &y);
	void		Link(GraphNode &x, GraphNode &y);
	GraphNode	FindSet(GraphNode x);

// data members: 
	GraphNode	*_parent;
	int			_rank;
};

#endif /* end of __GRAPHNODE_HPP__ inclusion guard*/
