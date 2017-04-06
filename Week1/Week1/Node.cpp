#include "Node.h"

namespace ExpressionTree
{

	template <typename T>
	Node<T>::Node(NodeType type)
		:type(type)
	{
	}

	template <typename T>
	Node<T>::~Node()
	{
	}

	//-----------------------------------------------------------------------------------

	template <typename T>
	Operand<T>::Operand() : Node<T>::Node(NodeType::operand_)
	{
	}

	template <typename T>
	Operand<T>::~Operand()
	{
	}

	template <typename T>
	T Operand<T>::Compute()
	{
		return data_;
	}

	//-----------------------------------------------------------------------------------

	template <typename T>
	Operator<T>::Operator() : Node<T>::Node(NodeType::operator_)
	{
	}

	template <typename T>
	Operator<T>::~Operator()
	{
	}

	template <typename T>
	T Operator<T>::Compute()
	{
		T leftResult = left_->Compute();
		T rightResult = right_->Compute();
		T result = T();

		switch (eOpType_)
		{
		case: OperatorType::add_ : result = leftResult + rightResult;
			break;
		case: OperatorType::subtract_ : result = leftResult - rightResult;
			break;
		case: OperatorType::multiply_ : result = leftResult * rightResult;
			break;
		case: OperatorType::divide_ : result = leftResult / rightResult;
			break;
		case: OperatorType::modulus_ : result = leftResult % rightResult;
			break;
		}

		return result;
	}

}