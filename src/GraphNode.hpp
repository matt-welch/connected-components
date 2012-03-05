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
				GraphNode(int vertexNumber);
	virtual		~GraphNode(void);

	int			GetRank(){return _rank;}
	void		SetRank(int newRank){_rank = newRank;}
	int			GetVertex(){return _vertex;}
	bool		isVisited(){return _visited;}
	void		Visit(){_visited = true;}

	// disjoint set operations - maybe in main()??
	void		MakeSet();
	void		Union(GraphNode *y);
	void		Link(GraphNode *x, GraphNode *y);
	GraphNode*	FindSet();
	int			GetParent(){return _parent->_vertex;}
	string		ToString();

private:
	void		InitMembers();
// data members: 
	int			_vertex;
	GraphNode*	_parent;
	int			_rank;
	bool		_visited;
};

#endif /* end of __GRAPHNODE_HPP__ inclusion guard*/
