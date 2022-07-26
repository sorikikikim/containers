namespace ft
{
    template <typename T>
    class Node
    {
    public:
        Node *left;
        Node *right;
        Node *parent;

        int height;
        T pair;

        Node() : left(NULL), right(NULL), parent(nullptr), height(1) {}

        Node(Node<T> const &node) : pair(node.pair)
        {
            left = node.left;
            right = node.right;
            height = node.height;
            parent = node.parent;
        }

        Node(T const &pair) : pair(pair)
        {
            left = NULL;
            right = NULL;
            parent = NULL;
            height = 1;
        }

        Node<T> &operator=(Node<T> const &rhs)
        {
            if (this != &rhs)
            {
                left = rhs.left;
                right = rhs.right;
                parent = rhs.parent;
                height = rhs.height;
            }
            return *this;
        }

        bool operator==(Node<T> const &rhs)
        {
            if (left == rhs.left && right == rhs.right && parent == rhs.parent && height == rhs.height)
                return true;
            return false;
        }

        bool operator!=(Node<T> const &rhs)
        {
            if (left == rhs.left && right == rhs.right && parent == rhs.parent && height == rhs.height)
                return false;
            return true;
        }
    };

    template <typename nodePtr>
    nodePtr get_next(nodePtr root)
    {
        if (root->right)
        {
            root = root->right;
            while (root->left)
            {
                root = root->left;
            }
        }
        else
        {
            nodePtr y = root->parent;
            while (root == y->right)
            {
                root = y;
                y = y->parent;
            }
            if (root->right != y)
            {
                root = y;
            }
        }
        return (root);
    }

    template <typename nodePtr>
    nodePtr get_precedent(nodePtr root)
    {
        if (root->left)
        {
            nodePtr y = root->left;
            while (y->right)
            {
                y = y->right;
            }
            root = y;
        }
        else
        {
            nodePtr y = root->parent;
            while (root == y->left)
            {
                root = y;
                y = y->parent;
            }
            root = y;
        }
        return root;
    }

    template <class T, class Comp, typename Alloc = std::allocator<T> >
    class Avl
    {
    public:
        typedef Node<T> mynode;
        typedef typename Alloc::template rebind<Node<T> >::other allocator_type;
        Node<T> *ptr;
        Comp comp;
        allocator_type m_allocate;

    public:
        Avl(const allocator_type &alloc = allocator_type()) : ptr(nullptr), m_allocate(alloc){};
        Avl(Comp &p, const allocator_type &alloc = allocator_type()) : ptr(nullptr), comp(p), m_allocate(alloc){};

        Avl(Node<T> &p) : ptr(p)
        {
        }

        size_t size(Node<T> *root)
        {
            size_t ret = 1;
            if (root == NULL)
                return 0;

            if (root->left)
                ret += size(root->left);
            if (root->right)
                ret += size(root->right);
            return ret;
        }

        Node<T> *clear(Node<T> *root)
        {
            if (root == NULL)
                return NULL;
            if (root->left)
            {
                clear(root->left);
                m_allocate.deallocate(root->left, 1);
                root->left = NULL;
                root->parent = NULL;
            }
            if (root->right)
            {
                clear(root->right);
                m_allocate.deallocate(root->right, 1);
                root->right = NULL;
                root->parent = NULL;
            }
            return NULL;
        }

        T &get_data()
        {
            return (ptr->pair);
        }

        Node<T> *most_left(Node<T> *ptr2) const
        {
            Node<T> *tmp = ptr2;
            while (tmp && tmp->left)
                tmp = tmp->left;
            return tmp;
        }

        Node<T> *most_right(Node<T> *ptr2) const
        {
            Node<T> *tmp = ptr2;
            while (tmp && tmp->parent)
                tmp = tmp->parent;
            return tmp;
        }

        Node<T> *newNode(T const &pair)
        {
            Node<T> *node = m_allocate.allocate(1);
            m_allocate.construct(node, pair);
            node->parent = nullptr;
            node->left = nullptr;
            node->right = nullptr;
            node->height = 1;
            return node;
        }

        int max(int a, int b) const
        {
            return (a > b ? a : b);
        }

        int height(Node<T> *root) const
        {
            if (root == NULL)
                return 0;
            return (root->height);
        }

        Node<T> *right_rotate(Node<T> *y)
        {
            Node<T> *x;
            Node<T> *T2;
            Node<T> *temp_parent;
            x = y->left;
            T2 = x->right;

            temp_parent = y->parent;
            y->parent = x;
            x->right = y;
            x->parent = temp_parent;
            y->left = T2;
            if (T2)
                T2->parent = y;
            y->height = max(height(y->left), height(y->right)) + 1;
            x->height = max(height(x->left), height(x->right)) + 1;

            return x;
        }

        Node<T> *left_rotate(Node<T> *x)
        {
            Node<T> *y;
            Node<T> *T2;
            Node<T> *temp_parent;
            y = x->right;
            T2 = y->left;

            temp_parent = x->parent;
            x->parent = y;
            y->left = x;
            y->parent = temp_parent;

            x->right = T2;
            if (T2)
                T2->parent = x;

            x->height = max(height(x->left), height(x->right)) + 1;
            y->height = max(height(y->left), height(y->right)) + 1;

            return y;
        }

        int getBalanceFactor(Node<T> *N)
        {
            if (N == NULL)
                return 0;
            return (height(N->left) - height(N->right));
        }

        Node<T> *insertNode(Node<T> *root, T pair)
        {
            if (root == nullptr)
            {
                return newNode(pair);
            }
            if (comp(pair, root->pair))
            {
                Node<T> *ret = insertNode(root->left, pair);
                ret->parent = root;
                root->left = ret;
            }
            else if (comp(root->pair, pair))
            {
                Node<T> *ret = insertNode(root->right, pair);
                ret->parent = root;
                root->right = ret;
            }
            else
                return root;
            root->height = max(height(root->left), height(root->right)) + 1;
            int bf = getBalanceFactor(root);
            if (bf > 1)
            {
                if (comp(pair, root->left->pair))
                {
                    return right_rotate(root);
                }
                else if (comp(root->left->pair, pair))
                {

                    root->left = left_rotate(root->left);

                    return right_rotate(root);
                }
            }
            if (bf < -1)
            {
                if (comp(root->right->pair, pair))
                {
                    return left_rotate(root);
                }
                else if (comp(pair, root->right->pair))
                {
                    root->right = right_rotate(root->right);
                    return left_rotate(root);
                }
            }
            return root;
        }

        Node<T> *insertNode2(Node<T> *root, const T &pair)
        {
            if (root == nullptr)
            {
                return newNode(pair);
            }
            if (comp(pair, root->pair))
            {
                Node<T> *ret = insertNode(root->left, pair);
                ret->parent = root;
                root->left = ret;
            }
            else if (comp(root->pair, pair))
            {
                Node<T> *ret = insertNode(root->right, pair);
                ret->parent = root;
                root->right = ret;
            }
            else
                return root;

            return root;
        }

        Node<T> *balance_tree(Node<T> *root, T pair)
        {
            if (root == nullptr)
                return nullptr;
            if (comp(pair, root->pair))
                balance_tree(root->left, pair);
            else if (comp(root->pair, pair))
                insertNode(root->right, pair);
            else
                return root;

            root->height = max(height(root->left), height(root->right)) + 1;
            int bf = getBalanceFactor(root);

            if (bf > 1)
            {
                if (comp(pair, root->left->pair))
                {
                    return right_rotate(root);
                }
                else if (comp(root->left->pair, pair))
                {
                    root->left = left_rotate(root->left);
                    return right_rotate(root);
                }
            }
            if (bf < -1)
            {

                if (comp(root->right->pair, pair))
                {
                    return left_rotate(root);
                }
                else if (comp(pair, root->right->pair))
                {
                    root->right = right_rotate(root->right);
                    return left_rotate(root);
                }
            }
            return root;
        }

        Node<T> *search_by_key(T pair, bool &bl, Node<T> *ptr2)
        {
            Node<T> *tmp;
            tmp = ptr2;

            while (1 && tmp)
            {
                if (tmp->pair.first == pair.first)
                {
                    bl = true;
                    return (tmp);
                }
                if (comp(tmp->pair, pair))
                    tmp = tmp->right;
                else
                    tmp = tmp->left;
            }
            Node<T> *ret = newNode(pair);
            return (ret);
        }

        Node<T> *nodeWithMimumValue(Node<T> *node)
        {
            Node<T> *current = node;
            while (current->left != NULL)
                current = current->left;
            return current;
        }

        bool count(Node<T> *root, T pair) const
        {
            Node<T> *tmp;
            tmp = root;

            while (1 && tmp)
            {
                if (tmp->pair.first == pair.first)
                {
                    return (true);
                }
                if (comp(tmp->pair, pair))
                    tmp = tmp->right;
                else
                    tmp = tmp->left;
            }
            return false;
        }

        Node<T> *deleteNode(Node<T> *root, T key)
        {
            if (root == NULL)
                return root;
            if (comp(key, root->pair))
                root->left = deleteNode(root->left, key);
            else if (comp(root->pair, key))
                root->right = deleteNode(root->right, key);
            else
            {
                if ((root->left == NULL) || (root->right == NULL))
                {
                    Node<T> *temp = root->left ? root->left : root->right;
                    if (temp == NULL)
                    {
                        temp = root;
                        root = NULL;
                    }
                    else
                    {
                        Node<T> *temp1 = root->parent;
                        m_allocate.construct(root, temp->pair);
                        root->left = temp->left;
                        root->right = temp->right;
                        root->height = temp->height;
                        root->parent = temp1;
                    }
                    m_allocate.destroy(temp);
                    m_allocate.deallocate(temp, 1);
                }
                else
                {
                    Node<T> *temp = nodeWithMimumValue(root->right);

                    Node<T> *new_node = m_allocate.allocate(1);
                    m_allocate.construct(new_node, temp->pair);
                    new_node->parent = root->parent;
                    new_node->left = root->left;
                    new_node->right = root->right;
                    new_node->height = root->height;

                    if (root->left)
                        root->left->parent = new_node;
                    if (root->right)
                        root->right->parent = new_node;

                    if (root == root->parent->left)
                        root->parent->left = new_node;
                    else if (root == root->parent->right)
                        root->parent->right = new_node;
                    root->left = nullptr;
                    root->right = nullptr;
                    root->parent = nullptr;
                    root = new_node;
                    root->right = deleteNode(root->right, temp->pair);
                }
            }
            if (root == NULL)
                return root;

            root->height = 1 + max(height(root->left),
                                   height(root->right));
            int balanceFactor = getBalanceFactor(root);
            if (balanceFactor > 1)
            {
                if (getBalanceFactor(root->left) >= 0)
                {
                    return right_rotate(root);
                }
                else
                {
                    root->left = left_rotate(root->left);
                    return right_rotate(root);
                }
            }
            if (balanceFactor < -1)
            {
                if (getBalanceFactor(root->right) <= 0)
                {
                    return left_rotate(root);
                }
                else
                {
                    root->right = right_rotate(root->right);
                    return left_rotate(root);
                }
            }
            return root;
        }
    };
}


// template <typename T>
// 	class Node
// 	{
// 	public:
// 		T _pair;
// 		Node *_parent;
// 		Node *_left;
// 		Node *_right;
// 		int _height;

// 		Node() : _parent(0), _left(0), _right(0), _height(1) {}
// 		Node(const Node<T> &other) : _pair(other._pair), _parent(other._parent),
// 									 _left(other._left), _right(other._right), _height(other._height) {}
// 		Node<T>& operator=(const Node<T> &other) 
// 		{
// 			if (this != &other)
//             {
//                 _parent = other._parent;
//                 _left = other._left;
//                 _right = other._right;
//                 _height = other._height;
//             }
//             return *this;
// 		}
// 		~Node() {}

// 	};

#ifndef __AVL_HPP__
#define __AVL_HPP__

#include <iostream>
#include "pair.hpp"
#include "node.hpp"
#include "../vector.hpp"
#include "../algorithm/max.hpp"

namespace ft
{
	// ******************************************* //
	// ********* Class template AvlTree ********** //
	// ******************************************* //
	template <	class Key,
				class T,
			  	class Compare,						// deleted after test
			  	class Alloc // deleted after test
			  	>
	class AvlTree
	{
		// ================================== //
		// ========= Member Types =========== //
		// ================================== //
	public:
		typedef Key 				key_type;
		typedef T 					mapped_type;
		typedef Compare 			key_compare;
		typedef Alloc 				allocator_value_type;

		typedef ft::pair<const key_type, mapped_type> 	value_type;
		typedef ft::node<value_type> 					node_type;
		typedef std::allocator<node_type> 				allocator_node_type;
		typedef size_t                                 	size_type;

		// ============================================== //
		// ========= Member Private Attributs =========== //
		// ============================================== //
	public:
		node_type 				*_root; // Node elements
		node_type 				*_current; // Current elements
		allocator_value_type 	_alloc_value;
		allocator_node_type 	_alloc_node;
		key_compare				_key_comp;

	public:
		// ============================================== //
		// ============= Constructors  ================== //
		// ============================================== //
		AvlTree() : _root(nullptr) , _current(nullptr) {} // Default constructor

		AvlTree(node_type const &root, node_type const &current) : _root(root), _current(current){}

		// ============================================== //
		// ===============   Operators    =============== //
		// ============================================== //
		AvlTree &operator=(const AvlTree &tree)
		{
			this->_root = tree._root;
			this->_current = tree._current;
			this->_alloc_value = tree._alloc_value;
			this->_key_comp = tree._key_comp;
			return (*this);
		}

		bool  operator==(AvlTree const& tree) const{
      		return (this->_root == tree._root && this->_current == tree._current);
    	}

    	bool  operator!=(AvlTree const& tree) const{
      		return (this->_root != tree._root || this->_current != tree._current);
    	}

		// ========================================================= //
		// ===========   Member/ Non Member Functions    ============ //
		// ========================================================= //

		private :
		// Calculate height fast
		int height(node_type *N)
		{
			if (N == NULL)
				return 0;
			return N->height;
		}

		// Rotate right
		node_type *rightRotate(node_type *y)
		{
			node_type *x = y->left;
			node_type *beta = x->right;
			x->right = y;
			y->left = beta;
			y->height = ft::max(height(y->left), height(y->right)) + 1;
			x->height = ft::max(height(x->left), height(x->right)) + 1;
			return x;
		}

		// Rotate left
		node_type *leftRotate(node_type *x)
		{
			node_type *y = x->right;
			node_type *beta = y->left;
			y->left = x;
			x->right = beta;
			x->height = ft::max(height(x->left), height(x->right)) + 1;
			y->height = ft::max(height(y->left), height(y->right)) + 1;
			return y;
		}

		// Get the balance factor of each node
		int getBalanceFactor(node_type *N)
		{
			if (N == NULL)
				return 0;
			return height(N->left) - height(N->right);
		}

		// Create new node
		node_type *newNode(const value_type &val)
		{
			node_type *ptr;
			ptr = this->_alloc_node.allocate(1);
			ptr->left = NULL;
			ptr->right = NULL;
			ptr->data = this->_alloc_value.allocate(1);
			this->_alloc_value.construct(ptr->data, val);
			ptr->height = 1;
			return ptr;
		}

		public :
		node_type *findMin(node_type *root) const
		{
			while (root && root->left)
				root = root->left;
			return root;
		}

		node_type *findMax(node_type *root) const
		{
			while (root && root->right)
				root = root->right;
			return root;
		}


		// Insert new node in the avl tree
		node_type *insertNode(node_type *node, const value_type &val)
		{
			// Find the correct postion and insertNode the node
			if (node == nullptr)
				return (newNode(val));
			if (_key_comp(val.first, node->data->first))
				node->left = insertNode(node->left, val);
			else if (_key_comp(node->data->first, val.first))
				node->right = insertNode(node->right, val);
			else
				return node;

			// Update the balance factor of each node and
			// balance the tree
			node->height = 1 + ft::max(height(node->left), height(node->right));
			int balanceFactor = getBalanceFactor(node);
			if (balanceFactor > 1)
			{
				if (_key_comp(val.first, node->left->data->first))
				{
					return rightRotate(node);
				}
				else if (_key_comp(node->left->data->first, val.first))
				{
					node->left = leftRotate(node->left);
					return rightRotate(node);
				}
			}
			if (balanceFactor < -1)
			{
				if (_key_comp(node->right->data->first, val.first))
				{
					return leftRotate(node);
				}
				else if (_key_comp(val.first, node->right->data->first))
				{
					node->right = rightRotate(node->right);
					return leftRotate(node);
				}
			}
			return node;
		}

		node_type *deleteNode(node_type *root, const key_type &key) // test
		{
			// Find the node and delete it
			if (root == NULL)
				return root;
			if (_key_comp(key, root->data->first))
				root->left = deleteNode(root->left, key);
			else if (_key_comp(root->data->first, key))
				root->right = deleteNode(root->right, key);
			else
			{
				if ((root->left == NULL) || (root->right == NULL))
				{
					node_type *temp = root->left ? root->left : root->right;
					if (temp == NULL)
					{
						temp = root;
						root = nullptr;
					}
					else
					{
						// *root = *temp;
						root->right = temp->right;
						root->left = temp->left;
						root->height = temp->height;
						this->_alloc_value.destroy(root->data);
						this->_alloc_value.construct(root->data, *(temp->data));
					}
							
					this->_alloc_value.deallocate(temp->data, 1);
					this->_alloc_node.deallocate(temp, 1);
				}
				else
				{
					node_type *temp = findMin(root->right);
					// root->data = temp->data;
					this->_alloc_value.destroy(root->data);
					this->_alloc_value.construct(root->data, *(temp->data));

					root->right = deleteNode(root->right, temp->data->first);
				}
			}
			if (root == NULL)
				return root;
			// Update the balance factor of each node and
			// balance the tree
			root->height = 1 + ft::max(height(root->left), height(root->right));
			int balanceFactor = getBalanceFactor(root);
			if (balanceFactor > 1)
			{
				if (getBalanceFactor(root->left) >= 0)
					return rightRotate(root);
				else
				{
					root->left = leftRotate(root->left);
					return rightRotate(root);
				}
			}
			if (balanceFactor < -1)
			{
				if (getBalanceFactor(root->right) <= 0)
					return leftRotate(root);
				else
				{
					root->right = rightRotate(root->right);
					return leftRotate(root);
				}
			}
			return root;
		}

		
		
		// Get next node using inorder successor
		node_type *nextNode(node_type *root, node_type *x) const
		{
			node_type *succ = nullptr;
			if (!root)
				return nullptr;
			while (1)
			{
				if (_key_comp(x->data->first, root->data->first))
				{
					succ = root;
					root = root->left;
				}
				else if (_key_comp(root->data->first, x->data->first))
					root = root->right;
				else
				{
					if (root->right)
						succ = findMin(root->right);
					break;
				}
				if (!root)
					return succ;
			}
			return succ;
		}

		// Get previous node using inorder successor
		node_type *previousNode(node_type *root, node_type *x)
		{
			node_type *prec = nullptr;
			if (!root)
				return nullptr;
			while (1)
			{
				if (_key_comp(x->data->first, root->data->first))
					root = root->left;
				else if (_key_comp(root->data->first, x->data->first))
				{
					prec = root;
					root = root->right;
				}
				else
				{
					if (root->left)
						prec = findMax(root->left);
					break;
				}
				if (!root){
					return prec;
				}
			}
			return prec;
		}

		node_type* findNode(node_type *root,  const key_type &key) const
		{
			if (!root)
				return NULL;
			if (_key_comp(root->data->first, key))
				return (findNode(root->right, key));
			else if (_key_comp(key, root->data->first))
				return (findNode(root->left, key));
		
			return root;
		}

		void  findKeysRange(node_type *root, const key_type &key, node_type **lower, node_type **upper) const
		{

			if (root)
			{
				if (key <= root->data->first && root->data->first < (*lower)->data->first)
					*lower = root;
				if (key < root->data->first && root->data->first < (*upper)->data->first)
					*upper = root;
				if (root->data->first <= key)
					findKeysRange(root->right, key, lower, upper);
				else if (key <= root->data->first)
					findKeysRange(root->left, key, lower, upper);
			}
		}

		// Print the balanced tree
		static void printTree(node_type *root, std::string indent, bool last)
		{
			if (root != nullptr)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "   ";
				}
				else
				{
					std::cout << "L----";
					indent += "|  ";
				}
				std::cout << root->data->first << std::endl;
				printTree(root->left, indent, false);
				printTree(root->right, indent, true);
			}
		}
	}; // class template AvlTree
} // namespace ft


//     void  preorder(node_type *root)
//     {
//       if (root)
//       {
//         std::cout << root->data->first << " ";
//         preorder(root->left);
//         preorder(root->right);
//       }
//     }

//     void  postorder(node_type *root)
//     {
//       if (root)
//       {
//         postorder(root->left);
//         postorder(root->right);
//         std::cout << root->data->first << " ";
//       }
//     }
