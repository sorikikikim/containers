#ifndef TREE_HPP
#define TREE_HPP

#include "utils.hpp"

namespace ft
{
	template <typename T>
	struct Node
	{
		//type define
		typedef T value_type;

		//elements
		value_type *_data;
		Node *_parent;
		Node *_left;
		Node *_right;
		int _height;
		bool& _available;
	};

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<T> >
	class AVLTree
	{
	private:
		typedef Compare key_compare;
		typedef Alloc allocator_type;

		typedef ft::pair<const Key, T> value_type;
		typedef Node<value_type> node_type;
		typedef Node<value_type> *node_pointer;
		typedef Alloc allocator_value;

	public:
		typedef typename Alloc::template rebind<node_type>::other _alloc_node;
		allocator_value _alloc_value;
		key_compare _key_comp;
		node_type *_root;

		AVLTree() : _root(0) {}
		AVLTree(const AVLTree &other) : _root(other._root) {}
		AVLTree(node_type &root) : _root(root) {}
		AVLTree &operator=(const AVLTree &other)
		{
			this->_alloc_value = other._alloc_value;
			this->_alloc_node = other._alloc_node;
			this->_key_comp = other._key_comp;
			this->_root = other._root;
		}

		bool  operator==(AVLTree const& other) const{
      		return (this->_root == other._root);
    	}

    	bool  operator!=(AVLTree const& other) const{
      		return (this->_root != other._root);
    	}

		~AVLTree()
		{
		}

		node_type *create_node(value_type &data)
		{
			node_type *new_node = _alloc_node.allocate(1);

			_alloc_value.construct(new_node->_data, data);
			new_node->_parent = 0;
			new_node->_left = 0;
			new_node->_right = 0;
			new_node->_height = 1;

			return new_node;
		}

		int height(node_type *node)
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
				if (_key_comp(data, root->_right->_data))
					root->_right = right_rotate(root->_right);
				return left_rotate(root);
			}
			return root;
		}

		node_type *delete_node(node_type *root, value_type data)
		{
			int balance_factor;

			if (root == NULL)
				return root;
			if (_key_comp(data, root->_data))
				root->_left = delete_node(root->left, data);
			else if (_key_comp(root->_data, data))
				root->_right = delete_node(root->_right, data);
			else
			{
				if ((root->left == NULL) || (root->right == NULL))
				{
					node_type *tmp = root->_left ? root->_left : root->_right;
					if (tmp == NULL)
					{
						tmp = root;
						root = NULL;
					}
					else
					{ 
						//*root = *tmp;
						//free(tmp);
						root->_left = tmp->_left;
						root->_right = tmp->_right;
						root->_height = tmp->_height;
						root->_available = tmp->_available;
						_alloc_value.destroy(root->_data);
						_alloc_value.construct(root->_data, tmp->_data);
					}
					_alloc_value.deallocate(tmp->_data, 1);
					_alloc_node.deallocate(tmp, 1);
				}
				else
				{
					node_type *tmp = find_min_node(root->_right);
					//root->_data = tmp->_data;
					_alloc_value.destroy(root->_data);
					_alloc_value.construct(root->_data, tmp->_data);
					root->right = delete_node(root->_right, tmp->_data);
				}
			}
			if (root == NULL)
				return root;
			// Update the balance factor of each node and
			// balance the tree

			root->_height = 1 + max(height(root->_left), height(root->right));
			balance_factor = get_balance_factor(root);
			if (balance_factor > 1)
			{
				if (get_balance_factor(root->_left) >= 0)
					return right_rotate(root);
				else
				{
					root->_left = left_rotate(root->_left);
					return right_rotate(root);
				}
			}
			if (balance_factor < -1)
			{
				if (get_balance_factor(root->_right) <= 0)
					return left_rotate(root);
				else
				{
					root->_right = right_rotate(root->_right);
					return left_rotate(root);
				}
			}
			return root;
		}

		 // bool& _available
		node_type* find_node(node_type *root, const key_type &key) const
		{
			if (!root){
                // 새로 넣어야하는 경우
                // _available = true;
				return NULL;
            }
			if (_key_comp(root->_data->_first, key))
				return (find_node(root->_right, key));
			else if (_key_comp(key, root->_data->_first))
				return (find_node(root->_left, key));
            // 이미 있는 경우
            // _available = false;
			return root;
		}

	};
}

#endif
