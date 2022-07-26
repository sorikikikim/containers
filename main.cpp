
#include "tree.hpp"
#include <iostream>


using namespace std;

int main()
{
    Node* root = NULL;
    
  root = insertNode(root, 33);
  root = insertNode(root, 13);
  root = insertNode(root, 53);
  root = insertNode(root, 9);
  root = insertNode(root, 21);
  root = insertNode(root, 61);
  root = insertNode(root, 8);
  root = insertNode(root, 11);
  printTree(root, "", true);
  root = deleteNode(root, 13);
  cout << "After deleting " << endl;
  printTree(root, "", true);
	
	// fill the array with 10 five times
	v1.assign(5, 10);

	ft::tree<int> tmp1(v1);
	
	cout << "prints the tree " << endl;
	cout << endl;
	cout << "The tree elements in v1 are: ";
	for (int i = 0; i < v1.size(); i++)
		cout << v1[i] << " ";
	cout << endl;

	cout << "---------------------------------------------------------" << endl;

	cout << "inserts 15 to the last position" << endl;
	v1.push_back(15);
	int n1 = v1.size();
	cout << "\nThe last element is: " << v1[n1 - 1];

	

	cout << "---------------------------------------------------------" << endl;

	cout << "removes last element" << endl;

	v1.pop_back();

	// prints the tree
	cout << "\nThe tree elements in v1 are: ";
	for (int i = 0; i < v1.size(); i++)
		cout << v1[i] << " ";



	cout << "---------------------------------------------------------" << endl;

	cout << "inserts 5 at the beginning" << endl;

	v1.insert(v1.begin(), 5);
	
	cout << "\nThe first element in v1 is: " << v1[0];
	cout << "---------------------------------------------------------" << endl;

	cout << "removes the first element" << endl;
	//v1.erase(v1.begin());
	//v2.erase(v2.begin());

	cout << "\nThe first element in v1 is: " << v1[0];
	cout << "---------------------------------------------------------" << endl;

	cout << "clear the tree" << endl;
	v1.clear();
	v2.clear();
	cout << "\ntree v1 size after clear(): " << v1.size();
	cout << "\ntree v2 size after clear(): " << v2.size() << endl;

