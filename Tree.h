
#pragma once
#include <iostream> // for process: std::cout
//-----------------------------------
//  class Tree (Binary Trees)
// process nodes in Pre/In/Post  order
//-----------------------------------
template <class T>
class Tree
{
protected:
	//--------------------------------------------------------
	//  inner class Node
	//      a single Node from a binary tree
	//--------------------------------------------------------
	class Node
	{
	public:
		T value;
		Node* left;
		Node* right;
		Node(T val)
			: value(val), left(nullptr), right(nullptr) {}
		Node(T val, Node* l, Node* r)
			: value(val), left(l), right(r) {}
	};		//end of Node class

	Node* root;

public:
	int leaves() ;
	int height() ;
	void reflect();
	int onlyLeftSon();
	Tree() { root = nullptr; };	 // initialize tree
	~Tree();
	bool isEmpty() const;
	void clear() { clear(root); root = nullptr; };
	void preOrder() { preOrder(root); };
	void inOrder() { inOrder(root); };
	void postOrder() { postOrder(root); };

	virtual void process(T val) { std::cout << val << " "; }
	virtual void add(T val) = 0;
	virtual bool search(T val) = 0;
	virtual void remove(T val) = 0;

private:

	int onlyLeftSon(Node* current);
	void reflect(Node* current);
	int leaves(Node* current);
	int height(Node* current);
	void  clear(Node* current);
	void  preOrder(Node* current);
	void  inOrder(Node* current);
	void  postOrder(Node* current);
};
