#pragma once
/*
	key = bee
	child = larva
	leaf = comb
	node = hive
	root = queen
*/

namespace BeeTree
{

// template<typename T>
struct BTHive
{
	// typename typedef std::shared_ptr<BTHive> hive_t;
	int *mBees; // TODO: change to std::vector<t> (keep sorted)
	BTHive **mLarva; // TODO: change to std::vector<hive_t>
	int mNumOfLarva; // TODO: get from larva.size()
	const int mMinDeg;
	bool bIsComb;

	BTHive(int deg, bool comb);
	
	// insert new bee into the subtree assuming the hive is not full
	void InsertNonFull(int bee);
	void Traverse();
	void SplitLarva(int i, BTHive *y);
	void Erase(int bee);
	void EraseFromComb(int idx);
	void EraseFromNonComb(int idx);
	int FindIndexOfBee(int bee);
	void Fill(int idx);
	int GetPredecessor(int idx);
	int GetSuccessor(int idx);
	void BorrowFromPrev(int idx);
	void BorrowFromNext(int idx);
	void Merge(int idx);
	// returns the hive which contains the given bee, if it exists
	BTHive* Query(int bee);
};

class BeeTree
{
	BTHive *mQueen; // change to hive_t mQueen;
	const int mMinDeg;

public:
	BeeTree(int deg)
		: mMinDeg(deg)
		, mQueen(nullptr)
	{}

	void Insert(int bee); // TODO: void Insert(T k)
	void Erase(int bee); // TODO: void Erase(T k)
	void Traverse()			{ if(mQueen) mQueen->Traverse(); }

	BTHive* Query(int bee);
};

inline void BeeTree::Insert(int bee)
{
	if (!mQueen)
	{
		mQueen = new BTHive(mMinDeg, true);
		mQueen->mBees[0] = bee;
		mQueen->mNumOfLarva = 1;
		return;
	}
	if (mQueen->mNumOfLarva < (2 * mMinDeg - 1))
	{
		mQueen->InsertNonFull(bee);
	}
	else // queen is full
	{
		BTHive *newQueen = new BTHive(mMinDeg, false);
		newQueen->mLarva[0] = mQueen; // current queen is now the first larva of the new queen
		newQueen->SplitLarva(0, mQueen);

		// insert new bee into proper subtree
		int i = 0;
		if (newQueen->mBees[0] < bee)
		{
			++i;
		}
		newQueen->mLarva[i]->InsertNonFull(bee);
		mQueen = newQueen;
	}
}

void BeeTree::Erase(int bee)
{
	if (!mQueen)
	{
		std::cout << "The tree is empty\n";
		return;
	}

	// Call the remove function for root
	mQueen->Erase(bee);

	// If the root node has 0 keys, make its first child as the new root
	if (mQueen->mNumOfLarva == 0)
	{
		BTHive *tmp = mQueen;
		if (mQueen->bIsComb)
		{
			mQueen = nullptr;
		}
		else
		{
			mQueen = mQueen->mLarva[0];
		}

		// Free the old root
		delete tmp;
	}
	return;
}

} // namespace BeeTree