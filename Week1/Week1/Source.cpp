#include "ExpressionTree.h"

void main()
{
	ExpressionTree::ExpressionTree<int> tree;
	tree.ConstructTree("(5+(4*(7-3)))");
}