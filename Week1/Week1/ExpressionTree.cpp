#include "ExpressionTree.h"
#include <string>
#include <ctype.h>

#define uint unsigned int

namespace ExpressionTree
{

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
		uint expLen = strlen(expression);
		uint maxNumPar = expLen / 2;
		std::vector<uint> parLoc;
		parLoc.reserve(maxNumPar);

		if (!ValidateExpression(expression))
		{
			return;
		}

		uint j = 0;
		for (uint i = 0; i < expLength; ++i)
		{
			if (expresion[i] == '(')
			{
				parLoc.push_back(i);
			}
			if (expresion[i] == ')')
			{
				j = parLoc.rbegin();
				parLoc.pop_back();
				while(j < i)
				{
					if (isdigit(expression[j]))
					{
					}
					if (IsOperator(expression[j]))
					{
					}
					++j;
				}
			}
		}
	}

	template<typename T>
	void ExpressionTree<T>::CreateNode(T data)
	{
		if (!root_)
		{
			root_ = new Operand(data);
		}
	}

	template<typename T>
	void ExpressionTree<T>::CreateNode(char data)
	{
		OperatorType opType;
		switch (data)
		{
		case '+': optype = OperatorType::add_;
			break;
		case '-': optype = OperatorType::subtract_;
			break;
		case '*': optype = OperatorType::multiply_;
			break;
		case '/': optype = OperatorType::divide_;
			break;
		case '%': optype = OperatorType::modulus_;
			break;
		}
		Operator<T> newRoot(opType);

	}

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

	template<typename T>
	bool ExpressionTree<T>::IsValidExpression(char * expression)
	{
		uint numOPar = 0;
		uint numCPar = 0;

		for (uint i = 0; i < expLength; ++i)
		{
			if (expresion[i] == '(')
			{
				++numOPar;
			}
			if (expresion[i] == ')')
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