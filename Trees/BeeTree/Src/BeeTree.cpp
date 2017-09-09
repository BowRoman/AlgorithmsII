#include "Precompiled.h"

#include "BeeTree.h"

namespace BeeTree
{

//------------------------------[BTHive]----------------------------------------
BTHive::BTHive(int deg, bool comb)
	: mMinDeg(deg)
	, bIsComb(comb)
{
	mBees = new int[2 * mMinDeg - 1];
	mLarva = new BTHive*[2 * mMinDeg];
	mNumOfLarva = 0;
} // BTHive::BTHive(int deg, bool comb)

void BTHive::InsertNonFull(int bee)
{
	int i = mNumOfLarva - 1;
	if (bIsComb)
	{
		// find locationg of new bee to insert
		// shift all bees from the location to the right
		while (i >= 0 && mBees[i] > bee)
		{
			mBees[i + 1] = mBees[i];
			--i;
		}
		mBees[i + 1] = bee;
		++mNumOfLarva;
	}
	else // find which larva should insert the new bee
	{
		while (i >= 0 && mBees[i] > bee)
		{
			--i;
		}
		++i;
		// check if the larva is full, if so split it
		if (mLarva[i]->mNumOfLarva >= (2 * mMinDeg - 1))
		{
			SplitLarva(i, mLarva[i]);
			if (mBees[i] < bee)
			{
				++i;
			}
		}
		mLarva[i]->InsertNonFull(bee);
	}
} // void BTHive::InsertNonFull(int bee)

void BTHive::Traverse()
{
	int i = 0;
	for (; i < mNumOfLarva; ++i)
	{
		if (!bIsComb)
		{
			mLarva[i]->Traverse();
		}
		std::cout << " " << mBees[i];
	}
	if (!bIsComb)
	{
		mLarva[i]->Traverse();
	}
} // void BTHive::Traverse()

void BTHive::SplitLarva(int i, BTHive *y)
{
	BTHive *bzz = new BTHive(y->mMinDeg, y->bIsComb);
	bzz->mNumOfLarva = mMinDeg - 1;

	// copy last minDeg - 1 from y to bzz
	for (int j = 0; j < mMinDeg - 1; ++j) // TODO: use std::copy or std::partition
	{
		bzz->mBees[j] = y->mBees[j + mMinDeg];
	}
	if (!y->bIsComb)
	{
		for (int j = 0; j < mMinDeg; ++j)
		{
			bzz->mLarva[j] = y->mLarva[j + mMinDeg];
		}
	}
	// update y's bee number
	y->mNumOfLarva = mMinDeg - 1;

	// make space for new larva
	for (int j = mNumOfLarva; j > i + 1; --j)
	{
		mLarva[j + 1] = mLarva[j];
	}
	// link new larva
	mLarva[i + 1] = bzz;

	// shift keys from index 1+ forward to make room for the middle bee
	for (int j = mNumOfLarva - 1; j >= i; --j)
	{
		mBees[j + 1] = mBees[j];
	}
	// copy middle bee of y to this location
	mBees[i] = y->mBees[mMinDeg - 1];
	++mNumOfLarva;
} // void BTHive::SplitLarva(int i, BTHive *y)

void BTHive::Erase(int bee)
{
	int idx = FindIndexOfBee(bee);

	// The key to be removed is present in this node
	if (idx < mNumOfLarva && mBees[idx] == bee)
	{
		if (bIsComb)
		{
			EraseFromComb(idx);
		}
		else
		{
			EraseFromNonComb(idx);
		}
	}
	else
	{
		if (bIsComb)
		{
			std::cout << "The key " << bee << " is does not exist in the tree\n";
			return;
		}
		bool flag = ((idx == mNumOfLarva) ? true : false);

		if (mLarva[idx]->mNumOfLarva < mMinDeg)
		{
			Fill(idx);
		}

		if (flag && idx > mNumOfLarva)
		{
			mLarva[idx - 1]->Erase(bee);
		}
		else
		{
			mLarva[idx]->Erase(bee);
		}
	}
	return;
}

void BTHive::EraseFromComb(int idx)
{

}

void BTHive::EraseFromNonComb(int idx)
{

}

int BTHive::FindIndexOfBee(int bee)
{
	int idx = 0;
	while (idx < mNumOfLarva && mBees[idx] < bee)
	{
		++idx;
	}
	return idx;
}

void BTHive::Fill(int idx)
{
}

int BTHive::GetPredecessor(int idx)
{
	return 0;
}

int BTHive::GetSuccessor(int idx)
{
	return 0;
}

void BTHive::BorrowFromPrev(int idx)
{
}

void BTHive::BorrowFromNext(int idx)
{
}

void BTHive::Merge(int idx)
{
}

BTHive* BTHive::Query(int bee) // TODO: hive_t Query(T k)
{
	int i = 0;
	while (i<mNumOfLarva && bee>mBees[i])
	{
		i++;
	}
	if (mBees[i] == bee)
	{
		return this;
	}
	if (bIsComb)
	{
		return nullptr;
	}
	return mLarva[i]->Query(bee);
} // BTHive* BTHive::Query(int bee)

//------------------------------[\BTHive]----------------------------------------

//------------------------------[BeeTree]----------------------------------------

BTHive* BeeTree::Query(int bee) // TODO: hive_t Query(T k)
{
	if (mQueen)
	{
		return mQueen->Query(bee);
	}
	return nullptr;
}

//------------------------------[\BeeTree]----------------------------------------

}