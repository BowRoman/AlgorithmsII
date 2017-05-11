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
	int Partition(int lIndex, int rIndex, int pivotIndex);

private:
	std::vector<T> &mVector;
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
	int pivotIndex = Partition(lIndex, rIndex, lIndex);
	QSort(lIndex, pivotIndex - 1);
	QSort(pivotIndex + 1, rIndex);
}

template<typename T, typename CMP>
int QuickSort<T,CMP>::Partition(int lIndex, int rIndex, int pivotIndex)
{
	CMP compare;

	if (pivotIndex != rIndex)
	{
		SwapElements(pivotIndex, rIndex);
	}

	int currLeft = lIndex;
	int currRight = rIndex-1;
	T pivot = mVector.at(rIndex);

	while(1)
	{
		while(currLeft < rIndex && compare(mVector.at(currLeft), pivot))
		{
			++currLeft;
		}
		while(currRight > lIndex && !compare(mVector.at(currRight), pivot))
		{
			--currRight;
		}
		if(currLeft >= currRight)
		{
			break;
		}
		if (rIndex != currLeft)
		{
			SwapElements(currLeft, currRight);
		}
	}
	return currLeft;
}

#endif // #ifndef ALGORITHMS_QUICKSORT_QUICKSORT_H