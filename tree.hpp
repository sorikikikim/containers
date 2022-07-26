#ifndef TREE_HPP
#define TREE_HPP

#include "utils.hpp"

namespace ft
{
	template <typename Pair>
	struct Node
	{
	public:
		typedef Pair	value_type;

		//elements
		value_type*		data;
		Node*			parent;
		Node*			left;
		Node*			right;
		int				height;
	};

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class AVLTree
	{
	private:
		typedef Key			key_type;
		typedef T			mapped_type;
		typedef Compare		key_compare;
		typedef Alloc		allocator_type;

		typedef ft::pair<const Key, T>		value_type;
		typedef Node<value_type> 			node_type;
		typedef Node<value_type>*			node_pointer;
		typedef std::allocator<node_type>	allocator_node;

	public:
		allocator_type	_alloc;
		allocator_node	_alloc_node;
		key_compare		_comp;
		
		

		Node<T>* create_node(value_type &data)
		{
			Node<T>* new_node = _alloc_node.allocate(1);

			_alloc.construct(new_node->_data, data);
			new_node->_parent = 0;
			new_node->_left = 0;
			new_node->_right = 0;
			new_node->_height = 1;

			return new_node;
		}

		int height(Node<T> *node)
		{
			if (node == NULL)
				return 0;
			return node->_height;
		}

		int get_balance_factor(Node<T> *node)
		{
			if (node == NULL)
				return 0;
			return height(node->_left) - height(node->_right);
		}

		int max(int a, int b)
		{
			return (a > b) ? a : b;
		}

		Node<T> *find_max_node(Node<T> *node)
		{
			Node<T> *max = node;

			if (!max)
				return NULL;

			while (max->_right)
				max = max->_right;

			return max;
		}

		Node<T> *find_min_node(Node<T> *node)
		{
			Node<T> *min = node;

			if (!min)
				return NULL;

			while (min->_right)
				min = min->_right;

			return min;
		}

		//   P (center) is going up and will replace Q (target)
		//
		//
		//               Q                                P              |
		//              / \     RIGHT ROTATION           / \             |
		//             P   C   ------------------->>>   A   Q            |
		//            / \                                  / \           |
		//           A   B                                B   C          |

		Node<T> *right_rotate(Node<T> *y)
		{
			Node<T> *x = y->_left;
			Node<T> *tmp = x->_right;

			x->_right = y;
			y->_left = tmp;

			y->_height = max(height(y->_left), height(y->_right)) + 1;
			x->_height = max(height(x->_left), height(x->_right)) + 1;

			return x;
		}

		Node<T> *left_rotate(Node<T> *x)
		{
			Node<T> *y = x->_right;
			Node<T> *tmp = y->_left;

			y->_left = x;
			y->_right = tmp;

			x->_height = max(height(x->_left), height(x->_right)) + 1;
			y->_height = max(height(y->_left), height(y->_right)) + 1;

			return y;
		}

		Node<T> *insert_node(Node<T> *node, value_type data)
		{
			//difference between the height of the left subtree and right subtree
			int balance_factor;

			// Find the correct postion and insert the node
			if (node == NULL)
				return (create_node(data));
			if (data < node->_data)
				node->_left = insert_node(node->_left, data);
			else if (data < node->_data)
				node->_right = insert_node(node->_right, data);
			else
				return node;
			// Update the balance factor of each node and Balance the tree
			node->_height = 1 + max(height(node->_left), height(node->_right));

			balance_factor = get_balance_factor(node);
			if (balance_factor > 1)
			{
				if (data > node->_left->_data)
					node->_left = left_rotate(node->_left);
				return right_rotate(node);
			}
			if (balance_factor < -1)
			{
				if (data < node->_right->_data)
					node->_right = right_rotate(node->_right);
				return left_rotate(node);
			}
			return node;
		}

		Node<T> *delete_node(Node<T> *node, value_type data)
		{
			int balance_factor;

			if (node == NULL)
				return node;
			if (data < node->_data)
				node->_left = delete_node(node->left, data);
			else if (data > node->_data)
				node->_right = delete_node(node->_right, data);
			else
			{
				if ((node->left == NULL) || (node->right == NULL))
				{
					Node<T> *tmp = node->_left ? node->_left : node->_right;
					if (tmp == NULL)
					{
						tmp = node;
						node = NULL;
					}
					else
						*node = *tmp;
					free(tmp);
				}
				else
				{
					Node<T> *tmp = find_min_node(node->_right);
					node->_data = tmp->_data;
					node->right = delete_node(node->_right, tmp->_data);
				}
			}
			if (node == NULL)
				return node;
			// Update the balance factor of each node and
			// balance the tree
			node->_height = 1 + max(height(node->_left), height(node->right));

			balance_factor = get_balance_factor(node);
			if (balance_factor > 1)
			{
				if (balance_factor < 0)
					node->_left = left_rotate(node->_left);
				return right_rotate(node);
			}
			if (balance_factor < -1)
			{
				balance_factor = get_balance_factor(node->_right);
				if (balance_factor > 0)
					node->_right = right_rotate(node->_right);
				return left_rotate(node);
			}
			return node;
		}

	};
}

#endif
