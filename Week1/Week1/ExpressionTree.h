#pragma once
#include "Node.h"
#include <vector>
#include <ctype.h>

#define uint unsigned int

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

		void CreateTNode(T data);
		void CreateDNode(char data);

		T MakeNumber(char *expression, uint& index);

		bool IsOperator(char c);
		bool IsValidExpression(char *expression, uint expLength);
	};

	template<typename T>
	ExpressionTree<T>::ExpressionTree()
		:root_(nullptr)
	{
	}

	template<typename T>
	ExpressionTree<T>::~ExpressionTree()
	{
	}

	template<typename T>
	void ExpressionTree<T>::ConstructTree(char *expression)
	{
		printf("Expression given: %s", expression);

		uint expLen = strlen(expression);
		uint maxNumPar = expLen / 2;
		std::vector<uint> parLoc;
		parLoc.reserve(maxNumPar);

		if (!IsValidExpression(expression, expLen))
		{
			return;
		}

		// TODO create tree from expression
		uint j = 0;
		for (uint i = 0; i < expLen; ++i)
		{
			if (expression[i] == '(')
			{
				parLoc.push_back(i);
			}
			if (expression[i] == ')')
			{
				j = parLoc.size();
				parLoc.pop_back();
				// if j > i we have passed the closing parenthesis. If e[j] == '(' we have reached a completed section
				while (j < i && expression[j] != '(')
				{
					if (isdigit(expression[j]))
					{
						T digit = MakeNumber(expression, j);
						CreateTNode(digit);
					}
					if (IsOperator(expression[j]))
					{
						CreateDNode(expression[j]);
					}
					++j;
				}
			}
		}
	}

	// Creates a data node.
	template<typename T>
	void ExpressionTree<T>::CreateTNode(T data)
	{
		Operand<T>* newNode = new Operand<T>(data);
		if (!root_)
		{
			root_ = newNode;
		}
		else
		{
			if (!root_->left_)
			{
				root_->left_ = newNode;
			}
			else if (!root_->right_)
			{
				root_->right_ = newNode;
			}
			else
			{
				printf("Improper expression structure: multiple numbers in sequence not seperated by operator.");
			}
		}
	}

	// Creates an operator node.
	template<typename T>
	void ExpressionTree<T>::CreateDNode(char data)
	{
		OperatorType opType;
		switch (data)
		{
		case '+': opType = OperatorType::add_;
			break;
		case '-': opType = OperatorType::subtract_;
			break;
		case '*': opType = OperatorType::multiply_;
			break;
		case '/': opType = OperatorType::divide_;
			break;
		case '%': opType = OperatorType::modulus_;
			break;
		}
		Operator<T>* newRoot = new Operator<T>(opType);
		newRoot->left_ = root_;
		root_ = newRoot;
	}

	template<typename T>
	T ExpressionTree<T>::MakeNumber(char *expression, uint& index)
	{
		char *number;
		number[0] = expression[index];
		uint numSize = 1;
		while (isdigit(expression[index + 1]));
		{
			++index;
			number += expression[index];
			++numSize;
		}
		return atoi(number);
	}

	// Returns true if the given character is a recognised operator.
	template<typename T>
	bool ExpressionTree<T>::IsOperator(char c)
	{
		switch (c)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '%': return true;
			break;
		default: return false;
			break;
		}
	}

	// Returns true if expression contains no unmatched parentheses.
	template<typename T>
	bool ExpressionTree<T>::IsValidExpression(char *expression, uint expLength)
	{
		uint numOPar = 0;
		uint numCPar = 0;

		for (uint i = 0; i < expLength; ++i)
		{
			if (expression[i] == '(')
			{
				++numOPar;
			}
			if (expression[i] == ')')
			{
				numCPar++;
			}
		}
		if (numOPar != numCPar)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}