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
		~Node();

		NodeType GetNodeType() { return eType_ }

		virtual T Compute() = 0;
	};

	//-----------------------------------------------------------------------------------

	template <typename T>
	class Operand : public Node<T>
	{
	private:
		T data_;
	public:
		Operand(T data);
		~Operand();

		T Compute() override;
	};

	//-----------------------------------------------------------------------------------

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
		Node<T>* left_;
		Node<T>* right_;

		Operator(OperatorType type);
		~Operator();

		OperatorType GetOpType() { return eOpType_; }

		T Compute() override;
	};
}