
/*=========================================================================

  Name        : Graph.cpp
  Author      : Team 3
  Version     : Course Proj
  Copyright   :
  Description : CIS 22C Course Project

  ========================================================================= */


#include <iostream>
#include "Graph.h"
#include <cstdlib>
#include <vector>
#include <iomanip>


Graph::Graph(int i)
{
	vertices =i;
	edges =0;
		for (int a =0; a<=i; a++)
		{
			adj.push_back(List<Users>());
			color.push_back('W');
			distance.push_back(-1);
			parent.push_back(0);
		}
}

Graph::~Graph()
{
	for(int a=0; a <=vertices;a++)
		{
		color.pop_back();
		distance.pop_back();
		parent.pop_back();
		for(int b=1; b <= adj[b].getLength();b++)
		{
			adj[b].removeLast();

		}
		adj.pop_back();
	}
}

int Graph::getNumEdges() const
{
	return edges;
}

int Graph::getNumVertices() const
{
	return vertices;
}

bool Graph::isEmpty() const
{
	if( vertices == 0 )
		return true;
	else return false;
}

int Graph::getDistance(int v) const
{	assert( v <= vertices);

	return distance [v];

}

int Graph:: getParent(int v) const
{
assert( v <= vertices);

	return parent[v];
}

char Graph:: getColor(int v) const
{	assert( v <= vertices);
	return color[v];

}

void Graph:: addFriend(Users a, Users b)
{
	int u=a.get_id();
	int v=b.get_id();

	    if(adj[u].isEmpty())
	    {
	        adj[u].insertFirst(b);

	        if(adj[v].isEmpty())
	            adj[v].insertFirst(a);

	        else
	        {
	            adj[v].insertLast(a);
	        }

	        edges++;
	    }
	    else if(adj[v].isEmpty())
	    {
	        adj[v].insertFirst(a);

	        if(adj[u].isEmpty())
	            adj[u].insertFirst(b);
	        else
	        {
	            adj[u].insertLast(b);
	        }
	        edges++;
	    }
	    else
	    {
	        if(adj[u].linearSearch(b) != -1)
	        {
	            return;
	        }
	        else if(adj[v].linearSearch(a) != -1)
	        {
	            return;
	        }
	        else
	        {
	            adj[u].insertLast(b);
	            adj[v].insertLast(a);


	            edges++;
	        }
	    }
}

void Graph::removeFriend(Users a, Users b)
{
	int u=a.get_id();
	int v=b.get_id();

	Users temp;

	if(adj[u].linearSearch(b) != -1)
	{	adj[u].startIterator();
		for(int i=0; i < adj[u].getLength();i++)
		{	temp =adj[u].getIterator();
			if(temp ==b)
				adj[u].removeIterator();
		}
	}
	else if(adj[v].linearSearch(a) != -1)
	{
		adj[v].startIterator();
		for(int i=0; i < adj[v].getLength();i++)
		{temp =adj[v].getIterator();
			if(adj[v].getIterator()==a)
			adj[v].removeIterator();
							}

	}
	edges--;
}

/*
int u=a.get_id();
int v=b.get_id();

assert(!adj[u].isEmpty());
assert(!adj[v].isEmpty());

if(adj[u].linearSearch(b) == -1) {
	cout << "Error - removeFriend (Graph.cpp)" << endl;
	return;
} else if(adj[v].linearSearch(a) != -1) {
	cout << "Error - removeFriend (Graph.cpp)" << endl;
	return;
} else {

	adj[u].startIterator();
	adj[v].startIterator();

	int index1 = adj[ul.linearSearch(b);
	int index2 = adj[v].linearSearch(a);

	adj[u].removeIterator();
	adj[v].removeIterator();

	edges--;
} */

void Graph:: BFS(Users a)
{
	int source = a.get_id();
	if(source<=0 || source>=vertices)
	{
		cout << "BFS : There is error for number of source" << endl;
		return;
	}
	else
	{	List<Users> list;
	  //  ;

		Users temp,temp1;
		color[source] = 'G';
		distance[source] = 0;

		list.insertLast(a);
		while(!list.isEmpty())
		{
			temp= list.getFirst();
			int tempIndex= temp.get_id();
			list.removeFirst();

			for(int i = 1; i <= adj[tempIndex].getLength(); i++)
			{
				adj[tempIndex].advanceToIndex(i);
				temp1 = adj[tempIndex].getIterator();
				int tempIndex2= temp1.get_id();
				if(color[tempIndex2] == 'W')
				{
					color[tempIndex2] = 'G';
					distance[tempIndex2] = distance[tempIndex] +1 ;
					parent[tempIndex2] = tempIndex;
					list.insertLast(temp1);
				}
			} color[tempIndex] = 'B';
		}
	}
}

void Graph:: printGraph(ostream& out)
{
	    for(int i=0; i<getNumVertices(); i++)
	    {
	        out << i << ": ";
	        adj[i].printList(out);
	        out << endl;
	    }
}

void Graph:: printBFS(ostream& out)
{
	 cout << "Print BFS " << endl;
	out << left << setw(6) << "v" << setw(6) << "c" << setw(6) << "p" << setw(6) << "d" << endl;
	for(int i =0; i<=vertices; i++)
	{
		out << left << setw(6) << i << setw(6) << color[i] << setw(6) << parent[i] << setw(6) << distance[i] << endl;
	}
}

/**
void Graph::convToBST(Users &user, int index)
{
	adj[index].startIterator();
	int number = adj[index].getLength();
	while(number>0)
	{
		adj[index].advanceIterator();
		number--;
	}

}
*/

int Graph:: FriendDistance(int friendId)
{
	return distance[friendId];
}


void Graph::fileout(ostream& out)
{
	for (int i=0; i< vertices; i++) {
		if (adj[i].isEmpty()) {
			break;
		} else {
			adj[i].startIterator();
			for (int j=0; j < adj[i].getLength(); j++) {
				out << i << " " << adj[i].getIterator().get_id() << endl;
				adj[i].advanceIterator();
			}
		}
	}
	out << "0 0"; //something
}

