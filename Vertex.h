#pragma once

/***********************************************************************
* 	 Class: Vertex
* 
*
***********************************************************************/
#include "Arc.h"

#include <list>
using std::list;

template<typename V, typename E> class Graph;

template<typename V, typename E>
class Vertex
{
	friend class Graph<V, E>;

public:

	// Manager functions

		// No argument constructor
	Vertex();

	// Copy constructor
	Vertex(const Vertex<V, E>& copy);

	// Assignment operator
	Vertex<V, E>& operator=(const Vertex<V, E>& rhs);

	// Destructor
	~Vertex();

	// Operator overloads

		// Equality operator
	bool operator==(Vertex<V, E> rhs);

	// Mutator functions

		// Sets the data in the vertex
	void SetData(V data);

	// Change the processed state
	void SetProcessed(bool change);

	// Adds an arc
	void AddArc(Arc<V, E> road);

	// Removes an arc
	void DeleteArc(Arc<V, E> road);

	// Removes all arcs pointing to a vertex
	void RemoveInRoads();

	// Accessor functions

		// Data accessor
	V& GetData();

	// Returns the state of the vertex
	bool GetProcessed();


	

private:
	list< Arc<V, E> > mArcs;
	V mData;
	int mRoads;
	bool mProcessed;

protected:
};

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
Vertex<V, E>::Vertex() :
	mArcs(), mData(), mRoads(0),
	mProcessed(false)
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
Vertex<V, E>::Vertex(const Vertex<V, E>& copy) :
	mArcs(copy.mArcs), mData(copy.mData),
	mRoads(copy.mRoads), mProcessed(copy.mProcessed)
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
Vertex<V, E>& Vertex<V, E>::operator=(const Vertex<V, E>& rhs)
{
	if (this != &rhs)
	{
		mArcs = rhs.mArcs;
		mData = rhs.mData;
		mRoads = rhs.mRoads;
		mProcessed = rhs.mProcessed;
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
Vertex<V, E>::~Vertex()
{  }

//
// Operator overloads
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
bool Vertex<V, E>::operator==(Vertex<V, E> rhs)
{
	return (mData == rhs.mData);
}

//
// Mutator functions
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
void Vertex<V, E>::SetData(V data)
{
	mData = data;
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
void Vertex<V, E>::SetProcessed(bool changed)
{
	mProcessed = changed;
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
void Vertex<V, E>::AddArc(Arc<V, E> road)
{
	mArcs.push_back(road);
	mRoads = mArcs.size();
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
void Vertex<V, E>::DeleteArc(Arc<V, E> road)
{
	mArcs.remove(road);
	mRoads = mArcs.size();
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
void Vertex<V, E>::RemoveInRoads()
{
	Vertex<V, E>* tempV = nullptr;

	Arc<V, E> tempA;
	tempA.SetDest(this);

	for (auto iterate= mArcs.begin(); iterate != mArcs.end() && mArcs.size() != 0; iterate++)
	{
		if (iterate->GetDest() != this)
		{
			tempA.SetData(iterate->GetData());
			tempV = iterate->GetDest();
			tempV->DeleteArc(tempA);
		}
	}
}


template<typename V, typename E>
V& Vertex<V, E>::GetData()
{
	return mData;
}


template<typename V, typename E>
bool Vertex<V, E>::GetProcessed()
{
	return mProcessed;
}

