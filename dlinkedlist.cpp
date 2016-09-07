// File:        dlinkedlist.cpp
// Author:      Aleksey Zakharov 301295506
// Date:        February 1, 2016
// Description: Sources file of a template doubly-linked-list class for CMPT 225 assignment 2

#ifdef _DLINKEDLIST_H_

#include "dlinkedlist.h"

//creates a deep copy of nodes 
// POST:  Calling object has an exact copy of all nodes from passed object
// PARAM: ll = DLinkedList reference from which we are tring to copy nodes
template <class T>
void DLinkedList<T>::CopyList(const DLinkedList& ll)
{
	Node<T>* tmp = ll.front; // set tmp to passed linkedlist
	while(tmp!=NULL)
	{
		//backward = forward;
		InsertBack(tmp->data);
		tmp = tmp->next;
	}
}

//Deallocates all dynamic memory from nodes in list 
// POST:  Deletes all nodes in list
template <class T>
void DLinkedList<T>::DeleteList()
{
	//check to see if list is empty
	if(size == 0)
		return;
	else
	{
		Node<T>* current = front;
		Node<T>* nextOne;
		while(current->next != NULL)
		{
			nextOne = current->next;
			delete current;
			current = nextOne;
		}
		size = 0;
	}
}

//Default constructor  
// POST:  sets size to 0, front point to NULL and back point to NULL
template <class T>
DLinkedList<T>::DLinkedList()
{
	size = 0;
	front = NULL;
	back = NULL;
}

//Copy constructor  
// POST:  Copy list from passed object, set appropriate front, size and back
// PARAM: ll = DLinkedList object from which you wish to copy all nodes from
template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList& ll)
{
	//check to see if list being passed is empty
	back = NULL;
	front= NULL;
	if(ll.size > 0)
	{
		CopyList(ll);
		return;
	}
	else
	{
	size = 0;
	}
}

//Destructor
// PRE:   
// POST:  
// PARAM: 
template <class T>
DLinkedList<T>::~DLinkedList()
{
	DeleteList();
}

//Function that adds a node to front of the list  
// POST:  Item is in the front of the list
// PARAM: T = object that you wish to add to front of list
template <class T>
void DLinkedList<T>::InsertFront(T item)
{
	if(front != NULL)
	{
		Node<T>* newNode = new Node<T>(item); //first node
		Node<T>* tmp = front;
		front = newNode;
		newNode->next = tmp;
		newNode->prev = NULL;
		tmp->prev= front;
		size+=1;
	}
	else
	{
		 front = new Node<T>(item);
		 size+=1;
		 back = front;
	}
}

//Function that adds a node to back of the list 
// POST:  Item is at the back of the list
// PARAM: T = object that you wish to add to the back of list
template <class T>
void DLinkedList<T>::InsertBack(T item)
{
	//if back is not a nullptr
	if(back != NULL)
	{
		back->next = new Node<T>(item);
 		back->next->prev = back;
		back = back->next;
		size+=1;
	}
 	else
	{
		back = new Node<T>(item);
		back->next = NULL;
		back->prev = NULL;
		front = back;
		size=+1;
	}
}

//Function that adds an item at some index in the list
// PRE: 0 based index, list must contain index, will throw exception if invalid index
// POST:  Item is at index p of the list
// PARAM: item = item we wish to add to list, p = index of where item to be inserted
template <class T>
void DLinkedList<T>::InsertAt(T item, int p)
{
	if(p < 0 || p >= size)
		throw std::out_of_range("index out of range");
	else if( p == 0)
	{
		InsertFront(item);
		return;
	}
	int iterator = 0;
	Node<T>* tmpFront = front;

	while(iterator < (p-1))
	{
		tmpFront = tmpFront->next;
		iterator++;
	}
	//afte the while loop we are one node behind the one that were inserting at
	Node<T>* tmpBack = tmpFront;
	tmpFront = tmpFront->next;
	//insert node infront of tmpBack, tmpBack->next is in the proper location
	tmpBack->next = new Node<T>(item);
	//set new node's next to tmpfront
	tmpBack->next->next = tmpFront;
	//set new node's back to tmpBack
	tmpBack->next->prev = tmpBack;
	//set tmpFront's prev to new node
	tmpFront->prev = tmpBack->next;
	size+=1;
}

//Function to remove item from an index
// PRE: 0 based index, will throw exception of index invalid
// POST: Item at index p removed
// PARAM: p = index of item to be removed
template <class T>
T DLinkedList<T>::RemoveAt(int p)
{
	if(p < 0 || p >= size)
	{
		throw std::out_of_range("index out of range");
		//return;
	}
	T item;
	Node<T>* tmpFront;
	Node<T>* tmpBack;
	Node<T>* tmpMid;

	//if we are removing first node
	if(p == 0) 
	{
		tmpFront = front;
		front = front->next;
		front->prev = NULL;
		item = tmpFront->data;
		delete tmpFront;
		size--;
		return item;
	}
	//if we are trying to remove last node
	if(p == size-1)
	{
		tmpBack = back;
		back = back->prev;
		back->next = NULL;
		item = tmpBack->data;
		size--;
		return item;
	}

	int iterator = 0;
	tmpFront = front;
	//iterate until we are one position behind the node we want to remove
	while(iterator < p-1)
	{
		tmpFront = tmpFront->next;
		iterator++;
	}
	tmpBack = tmpFront;
	tmpMid = tmpFront->next; //we are trying to remove this
	tmpFront = tmpFront->next->next; //point to node after the one we are tring to remove
	tmpFront->prev = tmpBack;	
	tmpBack->next = tmpFront;
	item = tmpMid->data;
	delete tmpMid;
	size--;
	return item;
}

//Function that removed duplicates from list
// POST:  List contains only a single copy of each element
template <class T>
void DLinkedList<T>::RemoveDuplicates()
{
	//
	if(size <= 1)
		return;
	int iteratorOne = 0;
	int iteratorTwo;
	Node<T>* tmpBack = front;
	Node<T>* tmpFront = front;
	while(iteratorOne < size-1)
	{
		iteratorTwo = iteratorOne+1;
		tmpFront = tmpBack->next;
		while(iteratorTwo < size && tmpFront != NULL)
		{
			if(tmpBack == tmpFront)
			{
				tmpFront=tmpFront->prev; //set pointer one node back
				RemoveAt(iteratorTwo);
				tmpFront = tmpFront->next; //move pointer past deleted node
				continue;
			}
			tmpFront = tmpFront->next;
			iteratorTwo++;
		}
		iteratorOne++;
		tmpBack = tmpBack->next;
	}
}

//Returns size of list
template <class T>
int DLinkedList<T>::Size() const
{
	return size;
}


//Returns true if list is empty, false otherwise
template <class T>
bool DLinkedList<T>::IsEmpty() const
{
	return (size == 0);
}


//Returns true if item is currently in list 
// PARAM: item = item that we wish to find in list
template <class T>
bool DLinkedList<T>::Contains(T item) const
{
	if(size == 0)
		return false;
	Node<T>* tmp = front;
	while(tmp!= nullptr)
	{
		if(tmp == item)
			return true;
		tmp = tmp->next;
	}
	return false;
}

//Returns the item at element p
// PRE:	 0 based index, throws exception if index is invalid
// PARAM: p = index of item to be retrieved
template <class T>
T DLinkedList<T>::ElementAt(int p) const
{
	if(p < 0 || p >= size)
		throw std::out_of_range("index out of range");
	int iterator = 0;
	Node<T>* tmp = front;
	while(iterator < size)
	{
		if(iterator == p)
			break;
		tmp = tmp->next;
		iterator++;
	}
	return tmp->data;
}

//Assignment operator
// PRE: if object encounters self, do nothing
// POST:  deep copy of all items in ll
// PARAM: ll = object who's list we wish to copy
template <class T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList& ll)
{
	if(this  != &ll)
	{
		if(ll.size == 0)
		{
			DeleteList();
			return *this;
		}
		CopyList(ll);
	}
	return *this;
}

#endif;