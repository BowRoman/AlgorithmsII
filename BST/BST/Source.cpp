#include "BST.h"

void main()
{
	std::ofstream outputFile;
	outputFile.open("Output.txt");

	BST::BSTree<int> myTree;

	myTree.Insert(23);
	myTree.Insert(12);
	myTree.Insert(34);
	myTree.Insert(8);
	myTree.Insert(76);
	myTree.Insert(10);
	myTree.Insert(11);
	myTree.Insert(41);
	myTree.Insert(30);
	myTree.Insert(6);

	myTree.Print(BST::Order::In, outputFile);

	outputFile << "\nMin is: " << myTree.FindMin();
	outputFile << "\nMax is: " << myTree.FindMax();

	int searchFor = 41;
	int remove = 34;

	outputFile << "\nSearch tree for " << searchFor;

	if (myTree.Search(searchFor))
	{
		outputFile << "\n[" << searchFor << " found]\n";
	}
	else
	{
		outputFile << "\n[" << searchFor << " not found]\n";
	}

	outputFile << "\nRemove " << remove;

	if (myTree.Remove(remove))
	{
		outputFile << "\n[" << remove << " removed]\n";
	}
	else
	{
		outputFile << "\n[" << remove << " not removed]\n";
	}
	myTree.Print(BST::Order::In, outputFile);

	outputFile << "\nFind between 9 and 35\n";

	std::vector<int> range = myTree.FindRange(9, 35);
	for (int i = 0; i < range.size(); ++i)
	{
		outputFile << range.at(i) << " ";
	}
	outputFile << std::endl;

	outputFile.close();
}