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
		delete right_;
		delete left_;
		right_ = nullptr;
		left_ = nullptr;
	}

	//-----------------------------------------------------------------------------------

	template <typename T>
	Operand<T>::Operand(T data)
		: Node<T>::Node(NodeType::operand_)
		, data_(data)
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
	Operator<T>::Operator(OperatorType type)
		: Node<T>::Node(NodeType::operator_)
		, eOpType_(type)
		, left_(nullptr)
		, right_(nullptr)
	{
	}

	template <typename T>
	Operator<T>::~Operator()
	{
	}

	// Performs the node's operation on the child nodes.
	template <typename T>
	T Operator<T>::Compute()
	{
		T leftResult();
		if (left_)
		{
			leftResult = left_->Compute();
		}
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