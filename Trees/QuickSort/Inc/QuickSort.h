#pragma once
#ifndef ALGORITHMS_QUICKSORT_QUICKSORT_H
#define ALGORITHMS_QUICKSORT_QUICKSORT_H

#include "Common.h"

template<typename T, typename CMP = std::less<T>>
class QuickSort
{
public:
	QuickSort(std::vector<T> &unSortedVec);
	~QuickSort();

	std::vector<T> &Get();
private:
	void SwapElements(int index1, int index2);
	void Sort();
	void QSort(int lVal, int rVal);
	int Partition(const int begin, const int end);

private:
	std::vector<T> &mVector;
	CMP mComp;
};

template<typename T, typename CMP>
inline QuickSort<T,CMP>::QuickSort(std::vector<T>& unSortedVec)
	: mVector(std::move(unSortedVec))
{
	Sort();
}

template<typename T, typename CMP>
inline QuickSort<T,CMP>::~QuickSort()
{
}

template<typename T, typename CMP>
inline std::vector<T>& QuickSort<T,CMP>::Get()
{
	return mVector;
}

template<typename T, typename CMP>
inline void QuickSort<T,CMP>::SwapElements(int index1, int index2)
{
	T temp = mVector.at(index1);
	mVector.at(index1) = mVector.at(index2);
	mVector.at(index2) = temp;
}

template<typename T, typename CMP>
inline void QuickSort<T,CMP>::Sort()
{
	QSort(0, mVector.size() - 1);
}

template<typename T, typename CMP>
void QuickSort<T,CMP>::QSort(int lIndex, int rIndex)
{
	if ((rIndex - lIndex) <= 0)
	{
		return;
	}
	int pivotIndex = Partition(lIndex, rIndex);
	QSort(lIndex, pivotIndex - 1);
	QSort(pivotIndex + 1, rIndex);
}

template<typename T, typename CMP>
int QuickSort<T,CMP>::Partition(const int begin, const int end)
{
	int pivot = mVector[end];
	int Index = begin;
	for (int iter = begin; iter < end; iter++)
	{
		if (mVector[iter] <= pivot)
		{
			if (Index != iter)
			{
				SwapElements(iter, Index);
			}
			Index++;
		}
	}
	if (Index != end)
	{
		SwapElements(end, Index);
	}
	return Index;
}

#endif // #ifndef ALGORITHMS_QUICKSORT_QUICKSORT_H