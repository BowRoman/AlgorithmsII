#pragma once
#ifndef TREES_HEAP_HEAP_H
#define TREES_HEAP_HEAP_H

#include "Common.h"

namespace Heap
{
template<typename T, typename CMP = std::less<T>>
class Heap
{
private:
	std::vector<T> mHeap;

	void BalanceUp(int idx);
	void BalanceDown();
public:
	Heap() {}
	Heap(int count) { mHeap.reserve(count); }
	
	void Push(T key) { mHeap.push_back(key); BalanceUp(mHeap.size()-1); }
	T Pop();

	T Top();
	int Size() { return mHeap.size(); }
};

//-----------------------------------------------------------------------

template<typename T, typename CMP>
void Heap<T, CMP>::BalanceUp(int idx)
{
	if (idx <= 0)
	{
		return;
	}

	int parentIdx = (idx - 1) >> 1;
	CMP comp;
	T temp = mHeap.at(idx);
	if (!comp(mHeap.at(parentIdx), temp))
	{
		mHeap.at(idx) = mHeap.at(parentIdx);
		mHeap.at(parentIdx) = temp;
		BalanceUp(parentIdx);
	}
}

template<typename T, typename CMP>
void Heap<T, CMP>::BalanceDown()
{
	T temp = mHeap.at(0);
	int idx = 0, currIdx = 0, leftIdx = 0, rightIdx = 0;
	CMP comp;
	int size = mHeap.size();

	while (idx < size >> 1)
	{
		leftIdx = (idx << 1) + 1;
		rightIdx = leftIdx + 1;
		if (rightIdx < size && !comp(mHeap.at(leftIdx), mHeap.at(rightIdx)))
		{
			currIdx = rightIdx;
		}
		else
		{
			currIdx = leftIdx;
		}
		if (comp(temp, mHeap.at(currIdx)))
		{
			break;
		}
		else
		{
			mHeap.at(idx) = mHeap.at(currIdx);
			idx = currIdx;
		}
	}
	mHeap.at(idx) = temp;
}

template<typename T, typename CMP>
inline T Heap<T, CMP>::Pop()
{
	T top = Top();

	mHeap.at(0) = mHeap.at(mHeap.size() - 1);
	mHeap.pop_back();
	if (mHeap.size() > 0)
	{
		BalanceDown();
	}
	return top;
}

template<typename T, typename CMP>
inline T Heap<T, CMP>::Top()
{
	if (mHeap.size() == 0)
	{
		std::cout << "Warning: Heap is empty.";
		return T();
	}
	return mHeap.at(0);
}

};

#endif // #ifndef TREES_HEAP_HEAP_H