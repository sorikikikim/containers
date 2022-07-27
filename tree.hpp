#ifndef TREE_HPP
#define TREE_HPP

#include "utils.hpp"

namespace ft
{
	template <typename T>
	struct Node
	{
		//type define
		typedef T	value_type;

		//elements
		value_type*		_data;
		Node*			_parent;
		Node*			_left;
		Node*			_right;
		int				_height;
	};

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<Node<ft::pair<const Key, T> > > >
	class AVLTree
	{
	private:
		typedef Compare		key_compare;
		typedef Alloc		allocator_type;

		typedef ft::pair<const Key, T>		value_type;
		typedef Node<value_type> 			node_type;
		typedef Node<value_type>*			node_pointer;
		typedef Alloc						allocator_node;

	public:
		//allocator_type	_alloc;
		allocator_node	_alloc_node;
		key_compare		_key_comp;
		node_type*		_root;
		
		AVLTree() : _root(0) {}
		AVLTree(const AVLTree &other) : _root(other._root) {}
		AVLTree(node_type &root) : _root(root) {}
		AVLTree &operator=(const AVLTree &other)
		{
			this->_alloc = other._alloc;
			this->_alloc_node = other._alloc_node;
			this->_comp = other._comp;
			this->_root = other._root;
		}
		~AVLTree() 
		{

		}


	private:
		node_type* create_node(value_type &data)
		{
			node_type* new_node = _alloc_node.allocate(1);

			_alloc.construct(new_node->_data, data);
			new_node->_parent = 0;
			new_node->_left = 0;
			new_node->_right = 0;
			new_node->_height = 1;

			return new_node;
		}

		int height(node_type* node)
		{
			if (node == NULL)
				return 0;
			return node->_height;
		}

		int get_balance_factor(node_type *node)
		{
			if (node == NULL)
				return 0;
			return height(node->_left) - height(node->_right);
		}

		int max(int a, int b)
		{
			return (a > b) ? a : b;
		}

		node_type *find_max_node(node_type *node)
		{
			node_type *max = node;

			if (!max)
				return NULL;

			while (max->_right)
				max = max->_right;

			return max;
		}

		node_type *find_min_node(node_type *node)
		{
			node_type *min = node;

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


		node_type *right_rotate(node_type *y)
		{
			node_type *x = y->_left;
			node_type *tmp = x->_right;

			x->_right = y;
			y->_left = tmp;

			y->_height = max(height(y->_left), height(y->_right)) + 1;
			x->_height = max(height(x->_left), height(x->_right)) + 1;

			return x;
		}

		node_type *left_rotate(node_type *x)
		{
			node_type *y = x->_right;
			node_type *tmp = y->_left;

			y->_left = x;
			y->_right = tmp;

			x->_height = max(height(x->_left), height(x->_right)) + 1;
			y->_height = max(height(y->_left), height(y->_right)) + 1;

			return y;
		}

		//위치 찾기 (이미 존재하는지, 존재하지 않는지)
		//넣어
		//balance 맞춤 -> avl
		node_type *insert_node(node_type *root, value_type &data)
		{
			//difference between the height of the left subtree and right subtree
			int balance_factor;

			// Find the correct postion and create the node
			if (root == NULL)
				return (create_node(data));
			if (_key_comp(data.first, root->_data->first))
				root->_left = insert_node(root->_left, data);
			else if (_key_comp(root->_data->first, data.first))
				root->_right = insert_node(root->_right, data);
			else
				return root;
			// Update the balance factor of each node and Balance the tree
			root->_height = 1 + max(height(root->_left), height(root->_right));

			balance_factor = get_balance_factor(root);
			if (balance_factor > 1)
			{
				if (_key_comp(root->_left->_data, data))
					root->_left = left_rotate(root->_left);
				return right_rotate(root);
			}
			if (balance_factor < -1)
			{
				if (data < root->_right->_data)
					root->_right = right_rotate(root->_right);
				return left_rotate(root);
			}
			return root;
		}

		node_type *delete_node(node_type *node, value_type data)
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
					node_type *tmp = node->_left ? node->_left : node->_right;
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
					node_type *tmp = find_min_node(node->_right);
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
