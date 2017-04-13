#pragma once
#include "Node.h"
#include <vector>

namespace ExpressionTree
{
	template<typename T>
	class ExpressionTree
	{
	public:
		ExpressionTree();
		~ExpressionTree();

		void ConstructTree(char *expression);

	private:
		Node<T>* root_;

		void CreateNode(int data);
		void CreateNode(char data);

		bool IsOperator(char c);
		bool IsValidExpression(char *expression, std::vector<unsigned int>& parLoc);
	};
}