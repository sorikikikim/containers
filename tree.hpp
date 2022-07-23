#ifndef TREE_HPP
#define TREE_HPP

namespace ft 
{
	template <class T>
	struct Node {
		T data;
		node *left;
		node *right;
		int balance_factor;
	};

	class AVL {
		private: 
			Node* root;

		public:

			void insert(const T value)
			{
				if (root == NULL)
				{
					root = new Node;
					root->data = value;
					root->left = NULL;
					root->right = NULL;
				} 
				else if (value < root->data)
				{
					root->left = insert(root->left, value);
					root = balance(root);
				}
				else 
				{
					root->right = insert(root->right, value);
					root = balance(root);
				}
			}

			Node* balance(Node *root)
			{
				this->balce_factor = diff(root);
				if (factor > 1)
			}


	}
}

#endif
