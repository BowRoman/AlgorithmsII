#pragma once
#ifndef TREES_AVL_BST_H
#define TREES_AVL_BST_H

#include "Common.h"

namespace AVL
{

enum class Order
{
	In,
	Pre,
	Post,
	Pretty
};

template<typename T>
class AVLTree
{
public:
	struct Node;
	typedef std::shared_ptr<Node> spNode;
	struct Node
	{
		T data_;
		uint8_t height_;
		spNode left_;
		spNode right_;
		Node(T val = T())
			: data_(val)
			, height_(0)
			, right_(nullptr)
			, left_(nullptr)
		{}
		~Node()
		{
			if (left_)
			{
				left_.reset();
			}
			if (right_)
			{
				right_.reset();
			}
		}
	}; // struct Node

	uint8_t GetHeight(const spNode& node) { return node ? node->height_ : 0; }

	spNode Insert(T val);
	// bool Search(T val);
	// bool Remove(T val);

	bool Print(Order order = Order::In, std::ostream& os = std::cout);

private:
	spNode root_;

private:
	int8_t GetBalanceFactor(const spNode& node) { return GetHeight(node->right_) - GetHeight(node->left_); }

	spNode InsertHelper(T val, spNode& node);
	void CalculateHeight(spNode& node);
	spNode Balance(spNode& node);

	spNode RotateRight(spNode& node);
	spNode RotateLeft(spNode& node);
	spNode RotateRightLeft(spNode& node);
	spNode RotateLeftRight(spNode& node);

	void PrintInOrder(std::ostream& os, const spNode currNode = nullptr);
	void PrintPreOrder(std::ostream& os, const spNode currNode = nullptr);
	void PrintPostOrder(std::ostream& os, const spNode currNode = nullptr);
	void PrintPretty(std::ostream& os, int8_t indent, const spNode currNode = nullptr);

}; // class AVLTree

template<typename T>
inline typename AVLTree<T>::spNode AVLTree<T>::Insert(T val)
{
	return InsertHelper(val, root_);
}

template<typename T>
inline bool AVLTree<T>::Print(Order order, std::ostream & os)
{
	switch (order)
	{
	case Order::In: PrintInOrder(os, root_);
		break;
	case Order::Pre: PrintPreOrder(os, root_);
		break;
	case Order::Post: PrintPostOrder(os, root_);
		break;
	case Order::Pretty: PrintPretty(os, 0, root_);
		break;
	default: return false;
		break;
	}
	return true;
} // bool Print(Order order, std::ostream & os)

template<typename T>
typename AVLTree<T>::spNode AVLTree<T>::InsertHelper(T val, spNode& node)
{
	if (!node)
	{
		spNode newNode = std::make_shared<Node>(val);
		if (!root_)
		{
			root_ = newNode;
		}
		return newNode;
	}
	else if (val < node->data_)
	{
		node->left_ = InsertHelper(val, node->left_);
	}
	else
	{
		node->right_ = InsertHelper(val, node->right_);
	}

	return Balance(node);
}

template<typename T>
inline void AVLTree<T>::CalculateHeight(spNode & node)
{
	uint8_t heightLeft = GetHeight(node->left_);
	uint8_t heightRight = GetHeight(node->right_);
	node->height_ = 1 + (heightRight > heightLeft ? heightRight : heightLeft);
} // void CalculateHeight(spNode & node)

template<typename T>
inline typename AVLTree<T>::spNode AVLTree<T>::Balance(spNode & node)
{
	CalculateHeight(node);
	if (GetBalanceFactor(node) == 2)
	{
		if (GetBalanceFactor(node->right_) < 0)
		{
			return RotateRightLeft(node);
		}
		else
		{
			return RotateLeft(node);
		}
	}
	else if (GetBalanceFactor(node) == -2)
	{
		if (GetBalanceFactor(node->left_) > 0)
		{
			return RotateLeftRight(node);
		}
		else
		{
			return RotateRight(node);
		}
	}
	else
	{
		return node;
	}
} // spNode Balance(spNode & node)

template<typename T>
inline typename AVLTree<T>::spNode AVLTree<T>::RotateRight(spNode& node)
{
	spNode newTop = node->left_;

	node->left_ = newTop->right_;
	newTop->right_ = node;

	CalculateHeight(node);
	CalculateHeight(newTop);

	return newTop;
} // spNode RotateRight(spNode node)

template<typename T>
inline typename AVLTree<T>::spNode AVLTree<T>::RotateLeft(spNode& node)
{
	spNode newTop = node->right_;

	node->right_ = newTop->left_;
	newTop->left_ = node;

	CalculateHeight(node);
	CalculateHeight(newTop);

	return newTop;
} // spNode RotateLeft(spNode node)

template<typename T>
inline typename AVLTree<T>::spNode AVLTree<T>::RotateRightLeft(spNode& node)
{
	node->right_ = RotateRight(node->right_);
	return RotateLeft(node);
} // spNode RotateRightLeft(spNode node)

template<typename T>
inline typename AVLTree<T>::spNode AVLTree<T>::RotateLeftRight(spNode& node)
{
	node->left_ = RotateLeft(node->left_);
	return RotateRight(node);
} // spNode RotateLeftRight(spNode node)

template<typename T>
void AVLTree<T>::PrintInOrder(std::ostream & os, const spNode currNode)
{
	if (!currNode)
	{
		return;
	}
	PrintInOrder(os, currNode->left_);
	os << currNode->data_ << " ";
	PrintInOrder(os, currNode->right_);
} // PrintInOrder(std::ostream & os, const spNode currNode)

template<typename T>
void AVLTree<T>::PrintPreOrder(std::ostream & os, const spNode currNode)
{
	if (!currNode)
	{
		return;
	}
	os << currNode->data_ << " ";
	PrintPreOrder(os, currNode->left_);
	PrintPreOrder(os, currNode->right_);
} // PrintPreOrder(std::ostream & os, const spNode currNode)

template<typename T>
void AVLTree<T>::PrintPostOrder(std::ostream & os, const spNode currNode)
{
	if (!currNode)
	{
		return;
	}
	PrintPostOrder(os, currNode->left_);
	PrintPostOrder(os, currNode->right_);
	os << currNode->data_ << " ";
} // PrintPostOrder(std::ostream & os, const spNode currNode)

template<typename T>
void AVLTree<T>::PrintPretty(std::ostream & os, int8_t indent, const spNode currNode)
{
	if (currNode)
	{
		if (currNode->left_) PrintPretty(os, indent + 4, currNode->left_);
		if (currNode->right_) PrintPretty(os, indent + 4, currNode->right_);
		if (indent)
		{
			std::cout << std::setw(indent) << ' ';
		}
		os << currNode->data_ << "\n ";
	}
} // PrintInOrder(std::ostream & os, const spNode currNode)


} // namespace AVL

#endif // #ifndef TREES_AVL_BST_H 