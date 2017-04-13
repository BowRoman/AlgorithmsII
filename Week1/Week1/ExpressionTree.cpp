//#include "ExpressionTree.h"
//#include <string>
//#include <ctype.h>
//
//#define uint unsigned int
//
//namespace ExpressionTree
//{
//
//	template<typename T>
//	ExpressionTree<T>::ExpressionTree()
//		:root_(nullptr)
//	{
//	}
//
//	template<typename T>
//	ExpressionTree<T>::~ExpressionTree()
//	{
//	}
//
//	template<typename T>
//	void ExpressionTree<T>::ConstructTree(char *expression)
//	{
//		printf("Expression given: %s", expression);
//
//		uint expLen = strlen(expression);
//		uint maxNumPar = expLen / 2;
//		std::vector<uint> parLoc;
//		parLoc.reserve(maxNumPar);
//
//		if (!ValidateExpression(expression))
//		{
//			return;
//		}
//
//		// TODO create tree from expression
//		uint j = 0;
//		for (uint i = 0; i < expLength; ++i)
//		{
//			if (expresion[i] == '(')
//			{
//				parLoc.push_back(i);
//			}
//			if (expresion[i] == ')')
//			{
//				j = parLoc.rbegin();
//				parLoc.pop_back();
//				// if j > i we have passed the closing parenthesis. If e[j] == '(' we have reached a completed section
//				while(j < i && expression[j] != '(')
//				{
//					if (isdigit(expression[j]))
//					{
//						T digit = MakeNumber(expression, j);
//						CreateNode(digit);
//					}
//					if (IsOperator(expression[j]))
//					{
//						CreateNode(expression[j]);
//					}
//					++j;
//				}
//			}
//		}
//	}
//
//	// Creates a data node.
//	template<typename T>
//	void ExpressionTree<T>::CreateNode(T data)
//	{
//		if (!root_)
//		{
//			root_ = new Operand(data);
//		}
//		else
//		{
//			if (!root_->left_)
//			{
//				root_->left_ = new Operand(data);
//			}
//			else if (!root_->right_)
//			{
//				root_->right_ = new Operand(data);
//			}
//			else
//			{
//				printf("Improper expression structure: multiple numbers in sequence not seperated by operator.");
//			}
//		}
//	}
//
//	// Creates an operator node.
//	template<typename T>
//	void ExpressionTree<T>::CreateNode(char data)
//	{
//		OperatorType opType;
//		switch (data)
//		{
//		case '+': optype = OperatorType::add_;
//			break;
//		case '-': optype = OperatorType::subtract_;
//			break;
//		case '*': optype = OperatorType::multiply_;
//			break;
//		case '/': optype = OperatorType::divide_;
//			break;
//		case '%': optype = OperatorType::modulus_;
//			break;
//		}
//		Operator<T> newRoot(opType);
//		newRoot->left_ = root_;
//		root_ = newRoot;
//	}
//
//	template<typename T>
//	T ExpressionTree<T>::MakeNumber(char *expression, unsigned int& index)
//	{
//		char *number = expression[index];
//		uint numSize = 1;
//		while (isdigit(expression[index+1]));
//		{
//			++index;
//			number += expression[index];
//			++numSize;
//		}
//		return atoi(number);
//	}
//
//	// Returns true if the given character is a recognised operator.
//	template<typename T>
//	bool ExpressionTree<T>::IsOperator(char c)
//	{
//		switch (c)
//		{
//		case '+':
//		case '-':
//		case '*':
//		case '/':
//		case '%': return true;
//			break;
//		default: return false;
//			break;
//		}
//	}
//
//	// Returns true if expression contains no unmatched parentheses.
//	template<typename T>
//	bool ExpressionTree<T>::IsValidExpression(char *expression)
//	{
//		uint numOPar = 0;
//		uint numCPar = 0;
//
//		for (uint i = 0; i < expLength; ++i)
//		{
//			if (expresion[i] == '(')
//			{
//				++numOPar;
//			}
//			if (expresion[i] == ')')
//			{
//				numCPar++;
//			}
//		}
//		if (numOPar != numCPar)
//		{
//			return false;
//		}
//		else
//		{
//			return true;
//		}
//	}
//
//}