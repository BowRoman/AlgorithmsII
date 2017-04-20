#pragma once
#ifndef TREES_BST_BST_H
#define TREES_BST_BST_H

#include "Common.h"

namespace BST
{

enum class Order
{
	In,
	Pre,
	Post
};

template<typename T>
class BSTree
{
public:
	struct Node;
	typedef std::shared_ptr<Node> spNode;
	struct Node
	{
		T data_;
		spNode left_;
		spNode right_;
		Node(T val = T())
			: data_(val)
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

	bool Insert(T val);
	bool Search(T val);
	bool Remove(T val);

	T FindMin();
	T FindMax();
	std::vector<T> FindRange(T min, T max);

	bool Print(Order order = Order::In, std::ostream& os = std::cout);

private:
	spNode root_;

	void FindRangeHelper(T min, T max, std::vector<T>& inRange, const spNode& curr);

	void PrintInOrder(std::ostream& os, const spNode currNode = nullptr);
	void PrintPreOrder(std::ostream& os, const spNode currNode = nullptr);
	void PrintPostOrder(std::ostream& os, const spNode currNode = nullptr);
}; // class BSTree

template<typename T>
inline bool BSTree<T>::Insert(T val)
{
	if (!root_)
	{
		root_ = std::make_shared<Node>(val);
		return true;
	}
	spNode currNode = root_;
	while (currNode)
	{
		if (val < currNode->data_)
		{
			if (!currNode->left_)
			{
				currNode->left_ = std::make_shared<Node>(val);
				return true;
			}
			else
			{
				currNode = currNode->left_;
			}
		}
		else if (val >= currNode->data_)
		{
			if (!currNode->right_)
			{
				currNode->right_ = std::make_shared<Node>(val);
				return true;
			}
			else
			{
				currNode = currNode->right_;
			}
		}
	}
	return false;
} // bool BSTree<T>::Insert(T val)

template<typename T>
inline bool BSTree<T>::Search(T val)
{
	spNode currNode = root_;
	while (currNode)
	{
		if (val < currNode->data_)
		{
			currNode = currNode->left_;
		}
		else if (val > currNode->data_)
		{
			currNode = currNode->right_;
		}
		else if (val == currNode->data_)
		{
			return true;
		}
		else
		{
			// How?
			return false;
		}
	}
	return false;
} // bool BSTree<T>::Search(T val)

template<typename T>
inline bool BSTree<T>::Remove(T val)
{
	spNode parentNode = nullptr;
	spNode currNode = root_;
	while (currNode)
	{
		if (val < currNode->data_)
		{
			parentNode = currNode;
			currNode = currNode->left_;
		}
		else if (val > currNode->data_)
		{
			parentNode = currNode;
			currNode = currNode->right_;
		}
		else if (val == currNode->data_)
		{
			// node to delete has no children
			if (!currNode->left_ && !currNode->right_)
			{
				if (!parentNode)
				{
					currNode.reset();
					root_.reset();
					return true;
				}
				else
				{
					if (parentNode->left_ == currNode)
					{
						currNode.reset();
						parentNode->left_.reset();
						return true;
					}
					else if (parentNode->right_ == currNode)
					{
						currNode.reset();
						parentNode->right_.reset();
						return true;
					}
				}
			}
			// node to delete has 1 child
			if (!currNode->left_ || !currNode->right_)
			{
				// 1. the node to delete is the root
				if (!parentNode)
				{
					// z. left
					if (currNode->left_)
					{
						root_ = currNode->left_;
						currNode.reset();
						return true;
					}
					// b. right
					if (currNode->right_)
					{
						root_ = currNode->right_;
						currNode.reset();
						return true;
					}
				}
				// 2. the node to delete is the left child
				else if (parentNode->left_ == currNode)
				{
					// a. its child if on the left
					if (currNode->left_)
					{
						// make the parents left child equal to the deleted nodes child
						parentNode->left_ = currNode->left_;
						currNode.reset();
						return true;
					}
					// b. right
					if (currNode->right_)
					{
						parentNode->left_ = currNode->right_;
						currNode.reset();
						return true;
					}
				}
				// 3. right
				else if (parentNode->right_ == currNode)
				{
					// a. left
					if (currNode->left_)
					{
						// make the parents left child equal to the deleted nodes child
						parentNode->right_ = currNode->left_;
						currNode.reset();
						return true;
					}
					// b. right
					if (currNode->right_)
					{
						parentNode->right_ = currNode->right_;
						currNode.reset();
						return true;
					}
				}
			}
			// node to delete has 2 children
			else
			{
				// set closestnode to the node-to-deletes right child
				spNode closestNode = currNode->right_;
				// if the right child has no children replace the deleted nodes data with the right child's
				if (!closestNode->left_ && !closestNode->right_)
				{
					currNode->data_ = closestNode->data_;
					currNode->right_.reset();
					closestNode.reset();
				}
				// if the right child has no left child, link its right child to the parent's child
				else if (!closestNode->left_)
				{
					currNode->data_ = closestNode->data_;
					currNode->right_ = closestNode->right_;
					closestNode->right_.reset();
					closestNode.reset();
					return true;
				}
				else
				{
					while (closestNode->left_)
					{
						parentNode = closestNode;
						closestNode = closestNode->left_;
					}
					if (closestNode->right_)
					{
						parentNode->left_ = closestNode->right_;
						closestNode->right_.reset();
					}
					else
					{
						parentNode->left_.reset();
					}
					currNode->data_ = closestNode->data_;
					closestNode.reset();
					return true;
				}
			}
		}
	}
	return false;
} // bool BSTree<T>::Remove(T val)

template<typename T>
inline T BSTree<T>::FindMin()
{
	if (!root_)
	{
		return T();
	}
	spNode smallest = root_;
	while (smallest->left_)
	{
		smallest = smallest->left_;
	}
	return smallest->data_;
} // T BSTree<T>::FindMin()

template<typename T>
inline T BSTree<T>::FindMax()
{
	if (!root_)
	{
		return T();
	}
	spNode largest = root_;
	while (largest->right_)
	{
		largest = largest->right_;
	}
	return largest->data_;
} // T BSTree<T>::FindMax()

template<typename T>
std::vector<T> BSTree<T>::FindRange(T min, T max)
{
	std::vector<T> inRange;
	FindRangeHelper(min, max, inRange, root_);
	return inRange;
} // std::vector<T> BSTree<T>::FindRange(T min, T max)

template<typename T>
inline bool BSTree<T>::Print(Order order, std::ostream& os = std::cout)
{
	switch (order)
	{
	case Order::In: PrintInOrder(os, root_);
		break;
	case Order::Pre: PrintPreOrder(os, root_);
		break;
	case Order::Post: PrintPostOrder(os, root_);
		break;
	default: return false;
		break;
	}
	return true;
} // bool BSTree<T>::Print(Order order, std::ostream& os = std::cout)

template<typename T>
void BSTree<T>::FindRangeHelper(T min, T max, std::vector<T>& inRange, const spNode & curr)
{
	if (!curr)
	{
		return;
	}
	if (curr->data_ >= min)
	{
		FindRangeHelper(min, max, inRange, curr->left_);
		if (curr->data_ <= max)
		{
			inRange.push_back(curr->data_);
			FindRangeHelper(min, max, inRange, curr->right_);
		}
	}
	else if (curr->data_ <= max)
	{
		FindRangeHelper(min, max, inRange, curr->right_);
	}
} // void BSTree<T>::FindRangeHelper(T min, T max, std::vector<T>& inRange, const spNode & curr)

template<typename T>
void BSTree<T>::PrintInOrder(std::ostream& os, const spNode currNode)
{
	if (!currNode)
	{
		return;
	}
	PrintInOrder(os, currNode->left_);
	os << currNode->data_ << " ";
	PrintInOrder(os, currNode->right_);
} // void BSTree<T>::PrintInOrder(std::ostream& os, const spNode currNode)

template<typename T>
void BSTree<T>::PrintPreOrder(std::ostream& os, const spNode currNode)
{
	if (!currNode)
	{
		return;
	}
	os << currNode->data_ << " ";
	PrintPreOrder(os, currNode->left_);
	PrintPreOrder(os, currNode->right_);
} // void BSTree<T>::PrintPreOrder(std::ostream& os, const spNode currNode)

template<typename T>
void BSTree<T>::PrintPostOrder(std::ostream& os, const spNode currNode)
{
	if (!currNode)
	{
		return;
	}
	PrintPostOrder(os, currNode->left_);
	PrintPostOrder(os, currNode->right_);
	os << currNode->data_ << " ";
} // void BSTree<T>::PrintPostOrder(std::ostream& os, const spNode currNode)

} // namespace BST

#endif // #ifndef TREES_BST_BST_H 