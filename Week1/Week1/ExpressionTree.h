#pragma once
#include "Node.h"

namespace ExpressionTree
{
	template<typename T>
	class ExpressionTree
	{
		Node<T>* root_;

	public:
		ExpressionTree();
		~ExpressionTree();

		void ConstructTree(char *expression);
	};
}