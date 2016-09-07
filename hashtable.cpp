// File:        hashtable.cpp
// Author:      Aleksey Zakharov
// Date:        April. 5th 2016
// Description: Definition of a hash table class for CMPT 225 assignment 5
            
#include "hashtable.h"

// Default constructor
HashTable::HashTable()
{
	maxsize = 101;
	table = new SLinkedList<UserAccount>[maxsize];
	size = 0;
}

// Constructor function makes hash table size = prime < (2 * n) 
// PARAM: n = integer value of array size
HashTable::HashTable(int n)
{
	if(n<2)
		maxsize = 101;
	else
		maxsize = SmallestPrime(2*n);
	table = new SLinkedList<UserAccount>[maxsize];
	size = 0;
}

// Constructor function makes deep copy of passed HashTable object
// PARAM: sourceht = HashTable object which we are trying to make a copy of
HashTable::HashTable(const HashTable& sourceht)
{
	CopyList(sourceht);
}

// Destructor function
HashTable::~HashTable()
{
	RemoveAll();
}

// Assignment operator function, creates deep copy of passed HashTable object
// PARAM: sourceht = HashTable object which we are trying to make a copy of
HashTable& HashTable::operator=(const HashTable& sourceht)
{
	if(this != &sourceht)
	{
		if(sourceht.size == 0)
		{
			RemoveAll();
			return *this;
		}
		CopyList(sourceht);
	}
	return *this;
}

// Function inserts a UserAccount into hash table, inserted using separate chaining, true if inserted, false otherwise
// PARAM: acct = UserAccount object which we are trying to insert
bool HashTable::Insert(UserAccount acct)
{
	if(Search(acct))
		return false;

	if(LoadFactor() > ((double)2/(double)3))
	{
		Resize(maxsize*2);
	}
	table[Hash(acct.GetUsername())].InsertBack(acct);
	size++;
	return true;
}

// Function removes UserAccount from hash table, true if removed, false otherwise
// PARAM: acct = UserAccount object which we are trying to remove
bool HashTable::Remove(UserAccount acct)
{
	if(!Search(acct))
		return false;
	table[Hash(acct.GetUsername())].Remove(acct);
	size--;
	return true;
}

// Function searches for UserAccount in hash table, returns true if found, false otherwise
// PARAM: acct = UserAccount object which we are trying to find
bool HashTable::Search(UserAccount acct) const
{
	int hash = Hash(acct.GetUsername());
	
	if(table[hash].Contains(acct))
		return true;
	return false;
}

// Function returns pointer to UserAccount which we are trying to retrieve from hash table
// PARAM: acct = UserAccount object which we are trying to retrieve from hash table
UserAccount* HashTable::Retrieve(UserAccount acct)
{
	if(!Search(acct))
		return NULL;
	return table[Hash(acct.GetUsername())].Retrieve(acct);
}

// Function returns size of table
int HashTable::Size() const
{
	return size;
}

// Function returns maxsize of table
int HashTable::MaxSize() const
{
	return maxsize;
}

// Function returns loadfactor of hash table
double HashTable::LoadFactor() const
{
	return (double)size/(double)maxsize;
}

// Function returns array indice using horner's method on the string input
// PARAM: input = string attribute used to hash useraccount into array
int HashTable::Hash(string input) const
{
	int length = input.length();
	int i = 0;
	int hash = (input[i++]-96)*32;

	while(length>2)
	{
		hash = ((hash + (input[i++]-96))%maxsize)*32;
		length--;
	}
	hash = ((hash + (input[i++]-96))%maxsize);
	return hash;
}

// Function returns the next smallest prime number after passed parameter
// PARAM: n = number which we use to find next prime number
int HashTable::SmallestPrime(int n) const
{
	n = n + 1;//greater than supplied parameter

	while(!IsPrime(n))
	{
		n++;
	}
	return n;
}

// Function determines if value passed is a prime number
// PARAM: n = number which we are testing to be prime
bool HashTable::IsPrime(int n) const
{
	if(n < 2)
		return true;
	int m = n/2;
	for(int i = 2; i < m ; i++)
	{
		if((n%i) == 0)
			return false;
	}
	return true;
}

// Function resizes array into size n, rehashes all values from old array into new array
// PARAM: n = integer value which we are expanding the array to
bool HashTable::Resize(int n)
{
	if(n < 0 || n < maxsize)
		return false;

	int oldsize = maxsize;
	maxsize = SmallestPrime(n);
	SLinkedList<UserAccount>* oldtable = table;
	table = new SLinkedList<UserAccount>[maxsize]; // resize table

	size = 0;//set size to 0, we will be rehashing

	for(int i = 0; i < oldsize; i++)
	{
		vector<UserAccount> tmp = oldtable[i].Dump();
		for(unsigned int j = 0; j < tmp.size() ; j++)
		{
			Insert(tmp[j]);
		}
		oldtable[i].RemoveAll(); //delete all nodes in old table
	}
	delete[] oldtable; //delete array of nodes
	return true;
}

// Function deletes all hashed values in array
void HashTable::RemoveAll()
{
	for(int i=0;i<maxsize;i++)
	{
		table[i].RemoveAll();
	}
}

// Function helps create a deep copy of another HashTable object
// PARAM: sourceht = HashTable object which we are trying to make a copy of
void HashTable::CopyList(const HashTable& sourceht)
{
	size = sourceht.size;
	maxsize = sourceht.maxsize;

	table = new SLinkedList<UserAccount>[maxsize];

	for(int i = 0; i < maxsize ; i++) //iterate throught all nodes, even empty ones.
	{
		vector<UserAccount> tmp = sourceht.table[i].Dump();
		for(unsigned int j = 0; j < tmp.size() ;j++)
		{
			table[i].InsertBack(tmp[j]);
		}
	}
}