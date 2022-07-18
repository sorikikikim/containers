
#include "../vector.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ft::vector<int> v1;
	vector<int> v2;
	
	
	// fill the array with 10 five times
	v1.assign(5, 10);
	v2.assign(5, 10);
	ft::vector<int> tmp(v1);
	cout << "prints the vector " << endl;
	cout << endl;
	cout << "The vector elements in v1 are: ";
	for (int i = 0; i < v1.size(); i++)
		cout << v1[i] << " ";
	cout << endl;

	cout << "The vector elements in v2 are: ";
	for (int i = 0; i < v2.size(); i++)
		cout << v2[i] << " ";
	cout << endl;

	cout << "---------------------------------------------------------" << endl;

	cout << "inserts 15 to the last position" << endl;
	v1.push_back(15);
	int n1 = v1.size();
	cout << "\nThe last element is: " << v1[n1 - 1];

	v2.push_back(15);
	int n2 = v2.size();
	cout << "\nThe last element is: " << v2[n2 - 1] << endl;

	cout << "---------------------------------------------------------" << endl;

	cout << "removes last element" << endl;

	v1.pop_back();
	v2.pop_back();

	// prints the vector
	cout << "\nThe vector elements in v1 are: ";
	for (int i = 0; i < v1.size(); i++)
		cout << v1[i] << " ";

	cout << "\nThe vector elements in v2 are: ";
	for (int i = 0; i < v2.size(); i++)
		cout << v2[i] << " ";
	cout << endl;

	cout << "---------------------------------------------------------" << endl;

	cout << "inserts 5 at the beginning" << endl;

	v1.insert(v1.begin(), 5);
	v2.insert(v2.begin(), 5);

	cout << "\nThe first element in v1 is: " << v1[0];
	cout << "\nThe first element in v2 is: " << v2[0] << endl;

	cout << "---------------------------------------------------------" << endl;

	cout << "removes the first element" << endl;
	//v1.erase(v1.begin());
	//v2.erase(v2.begin());

	cout << "\nThe first element in v1 is: " << v1[0];
	cout << "\nThe first element in v2 is: " << v2[0] << endl;
	cout << "---------------------------------------------------------" << endl;

	cout << "clear the vector" << endl;
	v1.clear();
	v2.clear();
	cout << "\nVector v1 size after clear(): " << v1.size();
	cout << "\nVector v2 size after clear(): " << v2.size() << endl;

	cout << "---------------------------------------------------------" << endl;

	{
		cout << endl;
		cout << "--------my swap--------"; // two vector to perform swap
		ft::vector<int> v1, v2;
		v1.push_back(1);
		v1.push_back(2);
		v2.push_back(3);
		v2.push_back(4);

		cout << "\nVector 1: ";
		for (int i = 0; i < v1.size(); i++)
			cout << v1[i] << " ";

		cout << "\nVector 2: ";
		for (int i = 0; i < v2.size(); i++)
			cout << v2[i] << " ";

		// Swaps v1 and v2
		v1.swap(v2);

		cout << "\nAfter Swap \nVector 1: ";
		for (int i = 0; i < v1.size(); i++)
			cout << v1[i] << " ";

		cout << "\nVector 2: ";
		for (int i = 0; i < v2.size(); i++)
			cout << v2[i] << " ";
	}

	{
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "------original swap------";
		// two vector to perform swap
		vector<int> v1, v2;
		v1.push_back(1);
		v1.push_back(2);
		v2.push_back(3);
		v2.push_back(4);

		cout << "\nVector 1: ";
		for (int i = 0; i < v1.size(); i++)
			cout << v1[i] << " ";

		cout << "\nVector 2: ";
		for (int i = 0; i < v2.size(); i++)
			cout << v2[i] << " ";

		// Swaps v1 and v2
		v1.swap(v2);

		cout << "\nAfter Swap \nVector 1: ";
		for (int i = 0; i < v1.size(); i++)
			cout << v1[i] << " ";

		cout << "\nVector 2: ";
		for (int i = 0; i < v2.size(); i++)
			cout << v2[i] << " ";
	}
}