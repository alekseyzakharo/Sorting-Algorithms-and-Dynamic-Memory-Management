// File:        sorting.cpp
// Author:      Geoffrey Tien
//              (your name)
// Date:        2016-02-08
// Description: Skeleton file for CMPT 225 assignment #3 sorting functions and helpers
//              Function bodies to be completed by you!

// Complete your sorting algorithm function implementations here

#include <stdlib.h>
#include <time.h>

// Selection Sort
// (your comments here)
template <class T>
int SelectionSort(T arr[], int n)
{
  int count = 0; 
  T tmp; 
  int smallest; 
  for(int i=0; i < (n-1); i++) 
  {
	  smallest = i; 
	  for(int j = i + 1; j < n ; j++) 
	  {
		  if(arr[smallest] > arr[j])
		  {
			  smallest = j;
		  }
		  count++;//counting the (arr[smallest] > arr[j]) comparasin
	  }
	  tmp = arr[i]; 
	  arr[i] = arr[smallest]; 
	  arr[smallest] = tmp;
  }
  return count;
}

// Quicksort
// (your comments here)
template <class T>
int Quicksort(T arr[], int n)
{
  int count = 0;
  QuicksortHelper(arr,0,n-1,count);
  return count;
}

template <class T>
void QuicksortHelper(T arr[], int low, int high, int& counter)
{
  int start = low;
  int end = high;
  T tmp;
  T pivot = arr[QSPartition(arr,low,high,counter)];

  while(start <= end)
  {
 	 while(arr[start] < pivot)
	 {
		  start++;
		  counter++; // +1
	 }
	  while(arr[end] > pivot)
	  {
		  end--;
		  counter++; // +1
	  }
	  if(start<=end)
	  {
		  tmp = arr[start];
		  arr[start] = arr[end];
		  arr[end] = tmp;
		  start++;
		  end--;
		  counter++; // +1
	  }
	  
  }
  if(low < end)
		QuicksortHelper(arr,low,end,counter);
  if(start < high)
		QuicksortHelper(arr,start,high,counter);
}

template <class T>
int QSPartition(T arr[], int low, int high, int& counter)
{
  int pivotindex = 0;
  pivotindex = high;
  return pivotindex;
}

// Randomized Quicksort
// (your comments here)
template <class T>
int RQuicksort(T arr[], int n)
{
  int count = 0;
  RQuicksortHelper(arr,0,n-1,count);
  return count;
}

template <class T>
void RQuicksortHelper(T arr[], int low, int high, int& counter)
{
  int start = low;
  int end = high;
  T tmp;
  T pivot = arr[RQSPartition(arr,low,high,counter)];

	while(start <= end)
	{
		if(arr[start] < pivot)
		{
			start++;
		}
		else if(arr[end] > pivot)
		{
			end--;
		}
		else if(start<=end)
		{
			tmp = arr[start];
			arr[start] = arr[end];
			arr[end] = tmp;
			start++;
			end--;
		}
		counter++;
  }
  if(low < end)
		RQuicksortHelper(arr,low,end,counter);
  if(start < high)
		RQuicksortHelper(arr,start,high,counter);
}

template <class T>
int RQSPartition(T arr[], int low, int high, int& counter)
{
  int pivotindex = 0;
  int randomindex;
  T tmp;

  srand(time(NULL));
  randomindex = (rand()%(high-low))+low;

  tmp = arr[randomindex];
  arr[randomindex] = arr[high];
  arr[high] = tmp;

  pivotindex=high;
  return pivotindex;
}

// Mergesort
// (your comments here)
template <class T>
int Mergesort(T arr[], int n)
{
  int count = 0;
  MergesortHelper(arr,0,n,n,count); // int n??????????????????????
  return count;
}

template <class T>
void MergesortHelper(T arr[], int low, int high, int n, int& counter)
{
	if(low < high)
	{
	int mid = low + (high - low)/2;

	MergesortHelper(arr,low,mid,n,counter);

	MergesortHelper(arr,mid+1,high,n,counter);

	Merge(arr,low,mid,high,n,counter);
  }
}

template <class T>
void Merge(T arr[], int low, int mid, int high, int n, int& counter)
{
	int leftIter = low;
	int leftEnd = mid;
	int rightIter = mid+1;
	int rightEnd = high;

	int iterator = low;


	T *tmp	= new T[n];

	while(leftIter<= leftEnd && rightIter <= rightEnd)
	{
		if(arr[leftIter] > arr[rightIter])
		{
			tmp[iterator] = arr[leftIter];
			iterator++;
			leftIter++;
		}
		else
		{
			tmp[iterator] = arr[rightIter];
			iterator++;
			rightIter++;
		}
	}

	while(leftIter <= leftEnd)
	{
		tmp[iterator] = arr[leftIter];
		iterator++;
		leftIter++;
	}

	while(rightIter <= rightEnd)
	{
		tmp[iterator] = arr[rightIter];
		iterator++;
		rightIter++;
	}
	
	for(int i = low;i <= high;i++)
	{
		arr[i] = arr[i];
		counter++;
	}

	delete [] tmp;

}
 
