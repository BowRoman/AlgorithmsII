#pragma once
#include "Common.h"
/*
	key = bee
	child = larva
	leaf = comb
	node = hive
	root = queen
*/

namespace BeeTree
{

struct BTHive
{
	// typename typedef std::shared<BTHive> hive_t;
	int *bees; // TODO: change to std::vector<t> (keep sorted)
	BTHive **larva; // TODO: change to std::vector<hive_t>
	int numOfLarva; // TODO: get from larva.size()
	const int minDeg;
	bool isComb;

	BTHive(int deg, bool comb)
		: minDeg(deg)
		, isComb(comb)
	{
		bees = new int[2 * minDeg - 1]; // TODO: bees.reserve(2*t-1)
		larva = new BTHive*[2 * minDeg];
		numOfLarva = 0;
	}
	
	// insert new bee into the subtree assuming the hive is not full
	void InsertNonFull(int bee)
	{
		int i = numOfLarva - 1;
		if (isComb)
		{
			// find locationg of new bee to insert
			// shift all bees from the location to the right
			while (i >= 0 && bees[i] > bee)
			{
				bees[i + 1] = bees[i];
				--i;
			}
			bees[i + 1] = bee;
			++numOfLarva;
		}
		else // find which larva should insert the new bee
		{
			while (i >= 0 && bees[i] > bee)
			{
				--i;
			}
			++i;
			// check if the larva is full, if so split it
			if (larva[i]->numOfLarva >= (2 * minDeg - 1))
			{
				SplitLarva(i, larva[i]);
				if (bees[i] < bee)
				{
					++i;
				}
			}
			larva[i]->InsertNonFull(bee);
		}
	}
	void Traverse() // TODO: inorder traversal
	{

	}
	void SplitLarva(int i, BTHive *y)
	{
		BTHive *bzz = new BTHive(y->minDeg, y->isComb);
		bzz->numOfLarva = minDeg - 1;

		// copy last minDeg - 1 from y to bzz
		for (int j = 0; j < minDeg - 1; ++j) // TODO: use std::copy or std::partition
		{
			bzz->bees[j] = y->bees[j + minDeg];
		}
		if (!y->isComb)
		{
			for (int j = 0; j < minDeg; ++j)
			{
				bzz->larva[j] = y->larva[j + minDeg];
			}
		}
		// update y's bee number
		y->numOfLarva = minDeg - 1;

		// make space for new larva
		for (int j = numOfLarva; j > i + 1; --j)
		{
			larva[j + 1] = larva[j];
		}
		// link new larva
		larva[i + 1] = bzz;

		// shift keys from index 1+ forward to make room for the middle bee
		for (int j = numOfLarva - 1; j >= i; --j)
		{
			bees[j + 1] = bees[j];
		}
		// copy middle bee of y to this location
		bees[i] = y->bees[minDeg - 1];
		++numOfLarva;
	}
	// returns the hive which contains the given bee, if it exists
	BTHive* Query(int bee); // TODO: hive_t Query(T k)
};

class BeeTree
{
	BTHive *queen; // change to hive_t queen;
	const int minDeg;

public:
	BeeTree(int deg)
		: minDeg(deg)
		, queen(nullptr)
	{}

	void Insert(int bee); // TODO: void Insert(T k)
	void Erase(int bee); // TODO: void Erase(T k)
	void Traverse()			{ if(queen) queen->Traverse(); }

	BTHive* Query(int bee) // TODO: hive_t Query(T k)
	{
		if (queen)
		{
			return queen->Query(bee);
		}
		return nullptr;
	}
};

inline void BeeTree::Insert(int bee)
{
	if (!queen)
	{
		queen = new BTHive(minDeg, true);
		queen->bees[0] = bee;
		queen->numOfLarva = 1;
		return;
	}
	if (queen->numOfLarva < (2 * minDeg - 1))
	{
		queen->InsertNonFull(bee);
	}
	else // queen is full
	{
		BTHive *newQueen = new BTHive(minDeg, false);
		newQueen->larva[0] = queen; // current queen is now the first larva of the new queen
		newQueen->SplitLarva(0, queen);

		// insert new bee into proper subtree
		int i = 0;
		if (newQueen->bees[0] < bee)
		{
			++i;
		}
		newQueen->larva[i]->InsertNonFull(bee);
		queen = newQueen;
	}
}

void BeeTree::Erase(int bee)
{

}

} // namespace BeeTree