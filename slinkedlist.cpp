// File:        slinkedlist.cpp
// Author:      Aleksey Zakharov
// Date:        April. 5th 2016
// Description: Definition of a linked list class for CMPT 225 assignment 5

#ifdef _SLINKEDLIST_H_

// Default constructor
template <class T>
SLinkedList<T>::SLinkedList()
{
	size = 0;
	front = NULL;
	back = NULL;
}

// Constructor function makes deep copy of passed SLinkedList object
// PARAM: ll = SLinkedList  object which we are trying to make a copy of
template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList& ll)
{
	front = NULL;
	back = NULL;
	size = 0;
	if(ll.size > 0)
	{
		CopyList(ll);
	}
	else
		size = 0;
}

// Destructor
template <class T>
SLinkedList<T>::~SLinkedList()
{
	DeleteList();
}

// Function inserts node to front of linked list, checks for doubles
// PARAM: item = T object which we are trying to insert
template <class T>
void SLinkedList<T>::InsertFront(T item)
{
	if(Contains(item))
		return;
	if(front != NULL)
	{
		Node<T>* newNode = new Node<T>(item);
		newNode->next = front;
		front = newNode;
		size++;
	}
	else
	{
		front = new Node<T>(item);
		size++;
		back = front;
	}
}

// Function inserts node to back of linked list, checks for doubles
// PARAM: item = T object which we are trying to insert
template <class T>
void SLinkedList<T>::InsertBack(T item)
{
	if(Contains(item))
		return;
	if(front != NULL)
	{
		back->next = new Node<T>(item);
		back = back->next;
	}
	else
	{
		back = new Node<T>(item);
		back->next = NULL;
		front = back;
	}
	size++;
}

// Function removes item T from linked list, returns true if successful
// PARAM: item = T object which we are trying to remove
template <class T>
bool SLinkedList<T>::Remove(T item)
{
	if(!Contains(item)) //if array empty we will exit at this point already
		return false;
	Node<T>* tmp1 = front;
	Node<T>* tmp2 = front->next;
	if(tmp1->data == item) // check to see if its the first element we need to remove
	{
		front = tmp2;
		delete tmp1;
		size--;
		return true;
	}
	while(tmp2 != NULL)
	{
		if(tmp2->data == item)
		{
			tmp1->next = tmp2->next;
			if(back = tmp2)
				back = tmp1;
			delete tmp2;
			size--;
			break;
		}
		tmp1 = tmp2;
		tmp2 = tmp2->next;
	}
	return true;
}

// Function deletes all nodes in linked list
template <class T>
void SLinkedList<T>::RemoveAll()
{
	if(size == 0)
		return;
	else
	{
		Node<T>* tmp1 = front;
		Node<T>* tmp2;
		while(tmp1 != NULL)
		{
			tmp2 = tmp1->next;
			delete tmp1;
			tmp1 = tmp2;
		}
		size = 0;
	}
}

// Function returns size of linked list
template <class T>
int SLinkedList<T>::Size() const
{
	return size;
}

// Function returns true if linked list empty, false otherwise
template <class T>
bool SLinkedList<T>::IsEmpty() const
{
	return (size == 0);
}

// Function returns true if item == node in linked list, false otherwise
// PARAM: item = T object which we are trying to find
template <class T>
bool SLinkedList<T>::Contains(T item) const
{
	if(size == 0)
		return false;
	Node<T>* tmp = front;
	while(tmp != NULL)
	{
		if(tmp->data == item)
			return true;
		tmp = tmp->next;
	}
	return false;
}

// Function returns pointer to item T in linked list, returns NULL if not found
// PARAM: item = T object which we are trying to retrieve
template <class T>
T* SLinkedList<T>::Retrieve(T item)
{
	if(!Contains(item))
		return NULL;
	Node<T>* tmp = front;
	while(tmp != NULL)
	{
		if(tmp->data == item)
		{
			return (&tmp->data);
		}
		tmp = tmp->next;
	}
	return NULL;
}

// Function dumps all nodes in linked list into a vector array, returns array
template <class T>
vector<T> SLinkedList<T>::Dump() const
{
	vector<T> tmpV;	//create empty Vector

	if(IsEmpty())
		return tmpV; //return empty Vector

	Node<T>* tmpN = front;
	while(tmpN != NULL)
	{
		tmpV.push_back(tmpN->data);
		tmpN = tmpN->next;
	}
	return tmpV;
}

// Assignment operator, creates deep copy of passed SLinkedList objects linked list
// PARAM: ll = SLinkedList<T> object which we are trying to make a deep copy of
template <class T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList<T>& ll)
{
	if(this != &ll)
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

// Helper function to create a deep copy of passed parameter SLinkedList's linked list
// PARAM: ll = SLinkedList<T> object which we are trying to make a deep copy of
template <class T>
void SLinkedList<T>::CopyList(const SLinkedList& ll)
{
	DeleteList();//delete current list

	Node<T>* tmp = ll.front;
	while(tmp != NULL)
	{
		InsertBack(tmp->data);
		tmp = tmp->next;
	}
}

// Helper function for deep delete
template <class T>
void SLinkedList<T>::DeleteList()
{
	RemoveAll();
}


#endif