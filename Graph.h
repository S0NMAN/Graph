/***********************************************************************
* 	 Class: Graph
*
*
***********************************************************************/
#pragma once

#include "Vertex.h"
#include "Exception.h"

#include <list>
using std::list;
using std::iterator;

#include <stack>
using std::stack;

#include <queue>
using std::queue;

template<typename V, typename E>
class Graph
{
public:

	// Manager functions

		// No argument constructor
	Graph();

	// Copy constructor
	Graph(const Graph<V, E>& copy);

	// Assignment operator
	Graph<V, E>& operator=(const Graph<V, E>& rhs);

	// Destructor
	~Graph();

	// Mutator functions

		// Insert a new vertex
	void InsertVertex(V data);

	// Remove an existing vertex
	void DeleteVertex(V data);

	// Insert a new arc
	void InsertArc(V start, V end, E edge);

	// Remove an existing arc
	void DeleteArc(V start, V end, E edge);

	// Resets all processed vertecies to unprocessed
	void ResetProcessed();

	// Accessor functions

		// Traverse the graph in a depth-first order
	void DepthFirst(void (*visit)(V&));

	// Traverse the graph in a breadth-first order
	void BreadthFirst(void (*visit)(V&));

	// Member functions

		// Returns true if the graph is empty
	bool isEmpty();

	// Returns a pointer to a vertex
	Vertex<V, E>* FindVertex(V data);

private:
	list< Vertex<V, E> > mVertexList;		// List of verticies in the graph
	int mCount;								// Number of verticies in the graph

protected:
};

//
// Manager functions
//

	/**********************************************************************
	*
	*
	*	   Purpose:
	*
	*		 Entry:
	*
	*		  Exit:
	*
	**********************************************************************/
template<typename V, typename E>
Graph<V, E>::Graph() :
	mVertexList(), mCount(0)
{  }

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
Graph<V, E>::Graph(const Graph<V, E>& copy) :
	mVertexList(copy.mVertexList), mCount(copy.mCount)
{
	*this = copy;
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/




template<typename V, typename E>
Graph<V, E>& Graph<V, E>::operator=(const Graph<V, E>& rhs)
{
	if (this != &rhs)
	{
		V tempvertdata;

		mVertexList = rhs.mVertexList;
		mCount = rhs.mCount;

		for (auto ListIt = mVertexList.begin(); ListIt != mVertexList.end(); ++ListIt)
		{
			for (auto ArcListIt = ListIt->mArcs.begin(); ArcListIt != ListIt->mArcs.end(); ++ArcListIt)
			{
				tempvertdata = ArcListIt->GetDest()->GetData();
				ArcListIt->SetDest(FindVertex(tempvertdata));
			}
		}
	}
	return *this;
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
Graph<V, E>::~Graph()
{  }

//
// Member functions
//

	/**********************************************************************
	*
	*
	*	   Purpose:
	*
	*		 Entry:
	*
	*		  Exit:
	*
	**********************************************************************/
template<typename V, typename E>
void Graph<V, E>::InsertVertex(V data)
{
	Vertex<V, E>* check = FindVertex(data);

	if (!check)
	{
		Vertex<V, E> added;
		added.SetData(data);
		mVertexList.push_back(added);
		++mCount;
	}
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
void Graph<V, E>::DeleteVertex(V data)
{
	Vertex<V, E>* remove = FindVertex(data);
	if (!remove)
		throw Exception("Can't delete vertex, vertex not found");


	remove->RemoveInRoads();
	mVertexList.remove(*remove);
	--mCount;
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
void Graph<V, E>::InsertArc(V start, V end, E edge)
{
	Vertex<V, E>* tempstart = FindVertex(start);
	if (!tempstart)
		throw Exception("Starting vertex not found");

	Vertex<V, E>* tempend = FindVertex(end);
	if (!tempend)
		throw Exception("Destination vertex not found");

	Arc<V, E> path;
	path.SetData(edge);

	if (tempstart != tempend)
	{
		path.SetDest(tempend);
		tempstart->AddArc(path);

		path.SetDest(tempstart);
		tempend->AddArc(path);
	}
	else
	{
		path.SetDest(tempstart);
		tempstart->AddArc(path);
	}
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
void Graph<V, E>::DeleteArc(V start, V end, E edge)
{
	Vertex<V, E>* tempstart = FindVertex(start);
	if (!tempstart)
		throw Exception("Starting vertex not found");

	Vertex<V, E>* tempend = FindVertex(end);
	if (!tempend)
		throw Exception("Destination vertex not found");

	Arc<V, E> path;
	path.SetData(edge);

	if (tempstart != tempend)
	{
		path.SetDest(tempend);
		tempstart->DeleteArc(path);

		path.SetDest(tempstart);
		tempend->DeleteArc(path);
	}
	else
	{
		path.SetDest(tempstart);
		tempstart->DeleteArc(path);
	}
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
void Graph<V, E>::ResetProcessed()
{
	for (auto ListIt = mVertexList.begin(); ListIt != mVertexList.end(); ++ListIt)
	{
		ListIt->SetProcessed(false);
	}
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
bool Graph<V, E>::isEmpty()
{
	return(mVertexList.size() == 0);
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
Vertex<V, E>* Graph<V, E>::FindVertex(V data)
{
	Vertex<V, E>* found = nullptr;
	for (auto ListIt = mVertexList.begin(); ListIt != mVertexList.end() && !found; ++ListIt)
	{
		if (ListIt->GetData() == data)
			found = &(*ListIt);
	}
	return found;
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
void Graph<V, E>::DepthFirst(void (*visit)(V&))
{
	if (mVertexList.empty())
		throw Exception("Graph is empty");

	stack< Vertex<V, E>* > dep;
	Vertex<V, E>* current;

	dep.push(&mVertexList.front());
	while (!dep.empty())
	{
		current = dep.top();
		dep.pop();
		visit(current->GetData());
		current->SetProcessed(true);

		for (auto ListIt = current->mArcs.begin(); ListIt != current->mArcs.end(); ++ListIt)
		{
			if (!ListIt->GetDest()->GetProcessed())
			{
				dep.push(ListIt->GetDest());
				ListIt->GetDest()->SetProcessed(true);
			}
		}
	}
	ResetProcessed();
}

/**********************************************************************
*
*
*	   Purpose:
*
*		 Entry:
*
*		  Exit:
*
**********************************************************************/
template<typename V, typename E>
void Graph<V, E>::BreadthFirst(void (*visit)(V&))
{
	if (mVertexList.empty())
		throw Exception("Graph is empty");

	queue< Vertex<V, E>* > bread;
	Vertex<V, E>* current;

	bread.push(&mVertexList.front());
	while (!bread.empty())
	{
		current = bread.front();
		bread.pop();
		visit(current->GetData());
		current->SetProcessed(true);

		for (auto ListIt = current->mArcs.begin(); ListIt != current->mArcs.end(); ++ListIt)
		{
			if (!ListIt->GetDest()->GetProcessed())
			{
				bread.push(ListIt->GetDest());
				ListIt->GetDest()->SetProcessed(true);
			}
		}
	}
	ResetProcessed();
}
