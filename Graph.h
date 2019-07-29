
/*=========================================================================

  Name        : Graph.h
  Author      : Team 3
  Version     : Course Proj
  Copyright   :
  Description : CIS 22C Course Project

  ========================================================================= */

#ifndef GRAPH_H_
#define GRAPH_H_


#include <iostream>
#include <cstdlib>
#include <vector>
#include "List.h"
#include "Users.h"


using namespace std;


class Graph {

public:
	Graph(int n);
	//initializes an empty graph to have n vertices

	~Graph();

	int getNumEdges() const;
	//returns the number of edges in the graph

	int getNumVertices() const;
	//returns the number of vertices in the graph

	bool isEmpty() const;
	//returns whether the graph is empty (no vertices)

	int getDistance(int v) const;
	//Pre: v <= vertices
	//Returns the value of the distance[v]

	int getParent(int v) const;
	//Pre: v <= vertices
	//Returns the value of the parent[v]

	char getColor(int v) const;
	//Pre: v <= vertices
	//Returns the value of color[v]


	void addFriend(Users u, Users v);
	//inserts vertex v into the adjacency list of vertex u (i.e. inserts v into the list at index u)
	//and inserts u into v.

	void removeFriend(Users u, Users v);
	//remove vertex v from adj[u], and u from adj[v]

	void printGraph(ostream& out);
	//Prints the adjacency list of each vertex in the graph,
	//vertex: <space separated list of adjacent vertices>
	//Prints to the console or to an output file given the ostream parameter

	void printBFS(ostream& out);
	//Prints the current values in the parallel vectors after executing BFS
	//Prints to the console or to an output file given the ostream parameter

	void BFS(Users users);
	//Performs breath first search on this Graph give a source vertex
	//pre: at least one vertex must exist
	//pre: source is a vertex in the graph

	void printPath(string users, int destination, ostream& out);
	//Prints the path from the source to the destination vertex
	//Prints to the console or to an output file given the ostream parameter

	int FriendDistance(int friendId);

	void fileout(ostream& out);


private:
    int vertices, edges; //number of edges and vertices
    vector< List<Users> > adj;
    vector<char> color;
    vector<int> distance;
    vector<int> parent;

};

#endif /* GRAPH_H */
