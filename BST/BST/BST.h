#pragma once
#include <iostream>
#include <memory>

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
		};

		bool Insert(T val);
		bool Search(T val);
		bool Remove(T val);

		bool Print(Order order = Order::In);

	private:
		spNode root_;

		void PrintInOrder(spNode currNode = nullptr);
		void PrintPreOrder(spNode currNode = nullptr);
		void PrintPostOrder(spNode currNode = nullptr);
	};

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
	}

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
				// How
				return false;
			}
		}
		return false;
	}

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
						root_ == nullptr;
						return true;
					}
					else
					{
						if (parentNode->left_ == currNode)
						{
							currNode.reset();
							parentNode->left_ = nullptr;
							return true;
						}
						else if (parentNode->right_ == currNode)
						{
							currNode.reset();
							parentNode->right_ = nullptr;
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
					// if the right child has no left child, link its right child to the parent's right
					if (!closestNode->left_)
					{
						if (closestNode->right_)
						{
							if (!parentNode)
							{
								root_ = closestNode->right_;
							}
							else
							{
								parentNode->right_ = closestNode->right_;
							}
						}
						currNode->data_ = closestNode->data_;
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
						}
						currNode->data_ = closestNode->data_;
						closestNode.reset();
						return true;
					}
				}
			}
		}
		return false;
	}

	template<typename T>
	inline bool BSTree<T>::Print(Order order)
	{
		switch (order)
		{
		case Order::In: PrintInOrder(root_);
			break;
		case Order::Pre: PrintPreOrder(root_);
			break;
		case Order::Post: PrintPostOrder(root_);
			break;
		default: return false;
			break;
		}
		return true;
	}

	template<typename T>
	inline void BSTree<T>::PrintInOrder(spNode currNode)
	{
		if (!currNode)
		{
			return;
		}
		PrintInOrder(currNode->left_);
		std::cout << currNode->data_ << " ";
		PrintInOrder(currNode->right_);
	}

	template<typename T>
	inline void BSTree<T>::PrintPreOrder(spNode currNode)
	{
		if (!currNode)
		{
			return;
		}
		std::cout << currNode->data_ << " ";
		PrintPreOrder(currNode->left_);
		PrintPreOrder(currNode->right_);
	}

	template<typename T>
	inline void BSTree<T>::PrintPostOrder(spNode currNode)
	{
		if (!currNode)
		{
			return;
		}
		PrintPostOrder(currNode->left_);
		PrintPostOrder(currNode->right_);
		std::cout << currNode->data_ << " ";
	}

}