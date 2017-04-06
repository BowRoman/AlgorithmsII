#pragma once

namespace ExpressionTree
{
	enum class NodeType
	{
		operand_,
		operator_,

		max_
	};

	template <typename T>
	class Node
	{
	private:
		NodeType eType_;
	protected:
		Node(NodeType type);
	public:
		Node();
		~Node();

		NodeType GetNodeType() { return eType_ }

		virtual T Compute() = 0;
	};

	//-----------------------------------------------------------------------

	template <typename T>
	class Operand : public base
	{
	private:
		T data_;
	public:
		T Compute() override;
	};

	//-----------------------------------------------------------------------

	enum class OperatorType
	{
		add_,
		subtract_,
		multiply_,
		divide_,
		modulus_,

		max_
	};

	template <typename T>
	class Operator : public Node<T>
	{
	private:
		OperatorType eOpType_;
	public:
		Operator();

		Node<T>* left_;
		Node<T>* right_;

		T Compute() override;
	};
}