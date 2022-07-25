#ifndef TREE_HPP
#define TREE_HPP

#include "map.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class AVLtree
	{
	private:
		//typedef T mapped_type;
		typedef Key						key_type;
		typedef T						type;
		typedef Compare					key_compare;
		typedef Alloc					allocator_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef Node<T>					node_type;
		typedef Node<T>*				node_pointer;
		typedef typename Alloc::template rebind<node_type>::other allocator_node;
		
	public:

		allocator_type _alloc_pair;
		allocator_node _alloc_node;

		struct Node
		{
			value_type	_data;
			Node*		_parent;
			Node*		_left;
			Node*		_right;
			int			_height;
		};

		Node* create_node(value_type data)
		{
			Node* new_node = _alloc_node.allocate(1);

			_alloc_pair.construct(new_node->_data, data);
			new_node->_parent = 0;
			new_node->_left = 0;
			new_node->_right = 0;
			new_node->_height = 1;

			return new_node;
		}

		int get_height(Node* node)
		{
			if (node == NULL)
				return 0;
			return node->_height;
		}

		int get_balance_factor(Node* node)
		{
			if (node == NULL)
				return 0;
			return get_height(node->_left) - get_height(node->_right);
		}

		int get_bigger(int a, int b)
		{
			return (a > b) ? a : b;
		}

		Node* find_max_node(Node* node)
		{
			Node* max = node;

			if (!max)
				return NULL;

			while (max->_right)
				max = max->_right;

			return max;
		}

		//   P (center) is going up and will replace Q (target)
                //
                //
                //               Q                                 P              |
                //              / \     RIGHT ROTATION            / \             |
                //             P   C  ------------------->>>     A   Q            |
                //            / \                                   / \           |
                //           A   B                                 B   C          |

		Node* right_rotate(Node* target)
		{
			
		}

		Node* insert_node(Node* node, value_type data)
		{
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
			node->_height = 1 + get_bigger(get_height(node->_left), get_height(node->_right));
			
			balance_factor = get_balance_factor(node);
			if (balance_factor > 1)
			{
				if (data > node->_left->data)
					node->left = left_rotate(node->left);
				return right_rotate(node);
			}
		}



	};
}

#endif
