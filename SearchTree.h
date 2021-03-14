#pragma once
#include "Tree.h"

template <class T>
class SearchTree : public Tree<T>
{
protected:
	using typename Tree<T>::Node;
	using Tree<T>::root;
public:

	// protocol for search trees
	void add(T value);
	bool search(T value)
	{
		return search(root, value);
	}
	void remove(T value) { remove(value,root); };
	int level(T value) { return level(root, value,1)-1; };
private:
	void remove(T value ,Node*& current);
	void add(Node* current, T val);
	bool search(Node* current, T val);
	int level(Node* current, T val,int level);
};


#include "Tree.h"

template<class T>
int Tree<T>::leaves()
{
	return leaves(root);
}

template <class T>
int Tree<T>::height()
{
	return height(root);
}
template<class T>
void Tree<T>::reflect()
{
	reflect(root);
}
template<class T>
int Tree<T>::onlyLeftSon()
{
	return(onlyLeftSon(root));
}
//----------------------------------------------------------
//  class Tree implementation
//----------------------------------------------------------
template <class T>
Tree<T>::~Tree() // deallocate tree
{
	if (root != nullptr)
		clear(root);
}
template<class T>
int Tree<T>::onlyLeftSon(Node* current)
{
	if (current->left && !current->right)
		return onlyLeftSon(current->left) + 1;
	if (current->right && current->left)
		return onlyLeftSon(current->right) + onlyLeftSon(current->left);
	if (current->right)
		return onlyLeftSon(current->right);
	return 0;
}
template<class T>
void Tree<T>::reflect(Node* current)
{
	if (current)
	{
		Node* temp = current->right;
		current->right = current->left;
		current->left = temp;
		if (current->left)
			reflect(current->left);

		if (current->right)
			reflect(current->right);
	}
}
template<class T>
int Tree<T>::leaves(Node* current)
{

	if (current)
	{
		if (!current->left && !current->right)
			return 1;
		return leaves(current->right) + leaves(current->left);
	}
	return 0;
}
template<class T>
int Tree<T>::height(Node* current)
{

	if (current)
	{    // Release memory associated with children
		int heightl = 0;
		int heightr = 0;

		if (current->left)
			heightl = height(current->left);
		if (current->right)
			heightr = height(current->right);
		if (heightr > heightl)
			return heightr + 1;
		else
			return heightl + 1;
	}
	return 0;
}
template <class T>
void Tree<T>::clear(Node* current)
{
	if (current)
	{    // Release memory associated with children
		if (current->left)
			clear(current->left);
		if (current->right)
			clear(current->right);
		delete current;
	}
}

template <class T>
bool Tree<T>::isEmpty() const
{
	return  root == nullptr;
}

// preOrder processing of tree rooted at current
template <class T>
void Tree<T>::preOrder(Node* current)
{    // visit Node, left child, right child
	if (current)
	{   // process current Node
		process(current->value);
		// then visit children
		preOrder(current->left);
		preOrder(current->right);
	}
}

// inOrder processing of tree rooted at current
template <class T>
void Tree<T>::inOrder(Node* current)
{    // visit left child, Node, right child
	if (current)
	{
		inOrder(current->left);
		process(current->value);
		inOrder(current->right);
	}
}

// postOrder processing of tree rooted at current
template <class T>
void Tree<T>::postOrder(Node* current)
{    // visit left child, right child, node
	if (current)
	{
		postOrder(current->left);
		postOrder(current->right);
		process(current->value);
	}
}



#include "SearchTree.h"

template <class T>
void SearchTree<T>::add(T val)
{
	// add value to binary search tree 
	if (!root)
	{
		root = new Node(val);
		return;
	}
	add(root, val);
}

template <class T>
bool SearchTree<T>::search(typename Tree<T>::Node* current, T val)
{
	// see if argument value occurs in tree
	if (!current)
		return false;	// not found
	if (current->value == val)
		return true;
	if (current->value < val)
		return search(current->right, val);
	else
		return search(current->left, val);
}

template<class T>
int SearchTree<T>::level(Node* current, T val, int lev)
{
	if (current)
	{
		if (current->value == val)
			return lev;
		int res = level(current->left, val, lev + 1);
		if (res != 0)
			return res;
		res = level(current->right, val, lev + 1);
		if (res != 0)
			return res;
	}
	return 0;

}

template<class T>
void SearchTree<T>::remove(T value, Node*& current)
{
		if (value < current->value)
		{
			remove(value , current->left);
		}
		else if (value > current->value)
		{
			remove(value, current->right);
		}
		else
		{
			Node* tempNodePtr = NULL;
			if (current == NULL)
			{
				cout << "Cannot delete empty node.\n";
			}
			else if (current->right == NULL)
			{
				tempNodePtr = current;
				current = current->left; // Reattach the left child
				delete tempNodePtr;
			}
			else if (current->left == NULL)
			{
				tempNodePtr = current;
				current = current->right; // Reattach the right child
				delete tempNodePtr;
			}
			// If the node has two children.
			else
			{
				// Move one node the right.
				tempNodePtr = current->right;
				// Go to the end left node.
				while (tempNodePtr->left)
				{
					tempNodePtr = tempNodePtr->left;
				}
				// Reattach the left subtree.
				tempNodePtr->left = current->left;
				tempNodePtr = current;
				// Reattach the right subtree.
				current = current->right;
				delete tempNodePtr;
			}
		}


}
	/*if (value < current->value)
	{

		if (current->left != NULL)
		{
			return current->left->remove(value, current);
		}
		else

			return NULL;

	}
	else if (value > current->value) {

		if (current->right != NULL)

			return current->right->remove(value, current);

		else

			return NULL;

	}*/
	/*else
	{

		if (current->left != NULL && current->right != NULL) {

			current->value = current->right->minValue();

			return current->right->remove(current->value, current);

		}
		else if (parent->left == current) {

			parent->left = (left != NULL) ? left : right;

			return current;

		}
		else if (parent->right == current) {

			parent->right = (left != NULL) ? left : right;

			return current;

		}

	}
	*/










	//	if (val < current->value)
	//		remove(current->left, val);
	//	else if (val > current->value)
	//		remove(current->right, val);
	//	else {
	//		if (current->left == NULL)
	//		{
	//			Node* temp = current->right;
	//			delete(current);
	//			current = temp;
	//		}
	//		else if (current->right == NULL) {
	//			struct node* temp = current->left;
	//			free(current);
	//			return temp;
	//		}



	//}
	//
	//
	//
	//
	//
	//
	//
	//
	//if (current->value == val)

	//	// add to right subtree
	//	if (current->right)
	//	{
	//		remove(current->right, val);
	//	}
	//	else (current->right, val);
	//else
	//	// add to left subtree
	//	if (!current->left)
	//	{
	//		current->left = new Node(val);
	//		return;
	//	}
	//	else add(current->left, val);
//}

template <class T>
void SearchTree<T>::add(Node* current, T val)
{
	if (current->value <= val)
		// add to right subtree
		if (!current->right)
		{
			current->right = new Node(val);
			return;
		}
		else add(current->right, val);
	else
		// add to left subtree
		if (!current->left)
		{
			current->left = new Node(val);
			return;
		}
		else add(current->left, val);
}



