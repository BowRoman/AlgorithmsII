#include <BST\Inc\BST.h>
#include <AVL\Inc\AVL.h>
#include <Heap\Inc\Heap.h>
#include <QuickSort\Inc\QuickSort.h>

void TestBST(std::ostream& outputFile);
void TestAVL(std::ostream& outputFile);
void TestHeap();
void TestQuickSort();

void main()
{
	//std::ofstream outputFile;
	//outputFile.open("Output.txt");
	//TestAVL(outputFile);
	//outputFile.close();
	TestQuickSort();
}

void TestBST(std::ostream& outputFile)
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
}

void TestAVL(std::ostream& outputFile)
{
	AVL::AVLTree<int> myTree;

	myTree.Insert(23);
	myTree.Print(AVL::Order::Pretty, outputFile);
	myTree.Insert(12);
	myTree.Print(AVL::Order::Pretty, outputFile);
	myTree.Insert(34);
	myTree.Print(AVL::Order::Pretty, outputFile);
	myTree.Insert(8);
	myTree.Print(AVL::Order::Pretty, outputFile);
	myTree.Insert(76);
	myTree.Print(AVL::Order::Pretty, outputFile);
	myTree.Insert(10);
	myTree.Print(AVL::Order::Pretty, outputFile);
	myTree.Insert(11);
	myTree.Print(AVL::Order::Pretty, outputFile);
	myTree.Insert(41);
	myTree.Print(AVL::Order::Pretty, outputFile);
	myTree.Insert(30);
	myTree.Print(AVL::Order::Pretty, outputFile);
	myTree.Insert(6);
	myTree.Print(AVL::Order::Pretty, outputFile);

	outputFile << "In Order: ";
	myTree.Print(AVL::Order::In, outputFile);

	int n = 23;
	if (myTree.Search(n))
	{
		outputFile << n << " found" << std::endl;
	}
	else
	{
		outputFile << n << " not found" << std::endl;
	}
	n = 41;
	if (myTree.Search(n))
	{
		outputFile << n << " found" << std::endl;
	}
	else
	{
		outputFile << n << " not found" << std::endl;
	}
	n = 37;
	if (myTree.Search(n))
	{
		outputFile << n << " found" << std::endl;
	}
	else
	{
		outputFile << n << " not found" << std::endl;
	}
	int r = 23;
	if (myTree.Remove(r) != AVL::AVLTree<int>::spNode())
	{
		outputFile << r << " removed" << std::endl;
	}
	else
	{
		outputFile << r << " not found" << std::endl;
	}
	myTree.Print(AVL::Order::Pretty, outputFile);
	r = 8;
	if (myTree.Remove(r) != AVL::AVLTree<int>::spNode())
	{
		outputFile << r << " removed" << std::endl;
	}
	else
	{
		outputFile << r << " not found" << std::endl;
	}
	myTree.Print(AVL::Order::Pretty, outputFile);
}

void TestHeap()
{
	Heap::Heap<int> heap(10);
	heap.Push(23);
	heap.Push(29);
	heap.Push(49);
	heap.Push(-16);
	heap.Push(64);
	heap.Push(12);
	heap.Push(37);

	while (heap.Size() > 0)
	{
		std::cout << heap.Pop() << ", ";
	}
	std::cout << std::endl;
}

void TestQuickSort()
{
	//std::vector<int> testVec = { 32, 56, 12, 0, 32, 85, 35, 96, -69, 12, 96, 34, 83, 17, 22, 47 };
	std::vector<int> testVec = { 32, 56, 12, 0 };
	QuickSort<int> mySort(testVec);

	std::cout << testVec.at(0);

	for (int i = 1; i < (int)testVec.size(); ++i)
	{
		std::cout << ", " << testVec.at(i);
	}

	std::cout << std::endl;
}