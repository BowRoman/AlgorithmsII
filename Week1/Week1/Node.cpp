#include "Node.h"

template <typename T>
Node<T>::Node(NodeType type)
	:type(type)
{
}

template <typename T>
Node<T>::Node()
{
}

template <typename T>
Node<T>::~Node()
{
}

//-----------------------------------------------------------------

//-----------------------------------------------------------------

//template <typename T>
//Operator<T>::Operator() : Node<T>::Node(NodeType::operator_)
//{
//}

template <typename T>
T Operator::Compute()
{
	T leftResult = left_->Compute();
	T rightResult = right_->Compute();
	T result = T();

	switch (eOpType_)
	{
	case: OperatorType::
	}
}