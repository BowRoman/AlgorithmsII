#include "BST.h"

void main()
{
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

	myTree.Print(BST::Order::In);

	int searchFor = 0;

	//std::cout << "\nSearch tree for: ";
	//std::cin >> searchFor;

	//if (myTree.Search(searchFor))
	//{
	//	std::cout << "[" << searchFor << " found]";
	//}
	//else
	//{
	//	std::cout << "[" << searchFor << " not found]\n";
	//}

	std::cout << "\nRemove: ";
	std::cin >> searchFor;

	if (myTree.Remove(searchFor))
	{
		std::cout << "[" << searchFor << " removed]";
	}
	else
	{
		std::cout << "[" << searchFor << " not removed]\n";
	}
	myTree.Print(BST::Order::In);
}