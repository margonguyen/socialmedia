
/*=========================================================================

  Name        : BST.h
  Author      : Team 3
  Version     : Course Proj
  Copyright   :
  Description : CIS 22C Course Project

  ========================================================================= */

#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <assert.h>
using namespace std;


template<typename bstdata>
class BST {

	private:
    	struct Node {
    		bstdata data;
    		Node* left;
    		Node* right;

    		Node(bstdata newdata){
    			data = newdata;
    			left = NULL;
    			right = NULL;
    		}
    	};

    	Node* root;

    	/**Private helper functions*/
    	void insertNode(Node* root, bstdata data);
    	//private helper function for insert
    	//recursively inserts a value into the BST

    	void inOrderPrint(ostream& out, Node* root) const;
    	//private helper function for inOrderPrint
    	//recursively prints tree values in order from smallest to largest

    	void friendPrint(ostream& out, Node* root, int listNum) const;

    	void preOrderPrint(ostream& out, Node* root) const;
    	//private helper function for preOrderPrint
    	//recursively prints tree values in pre order

    	void postOrderPrint(ostream& out, Node* root) const;
    	//private helper function for postOrderPrint
    	//recursively prints tree values in post order

    	void copyNode(Node* copy);
    	//recursive helper function to the copy constructor

    	void freeNode(Node* root);
    	//private helper function for the destructor
    	//recursively frees the memory in the BST

    	bool searchNode(Node* root, bstdata data) const;
    	//recursive helper function to search
    	//returns whether the value is found in the tree

    	bstdata minimum(Node* root) const;
    	//recursive helper function to minimum
    	//returns the minimum value in the tree

    	bstdata maximum(Node* root) const;
    	//recursive helper function to maximum
    	//returns the maximum value in the tree

    	Node* removeNode(Node* root, bstdata data);
    	//recursive helper function to remove
    	//removes data from the tree

    	void getSize(Node* root, int& size) const;
    	//recursive helper function to the size function
    	//calculates the size of the tree
    	//stores the result in size

    	int getHeight(Node* root) const;
    	//recursive helper function to the height function
    	//returns the height of the tree


	public:

    	/**constructors and destructor*/

    	BST();
    	//Instantiates a new BST

    	BST(const BST &bst);
    	//copy constructor

    	~BST();
    	//deallocates the tree memory

    	/**access functions*/

    	bstdata minimum() const;
    	//returns the minimum value in the BST
    	//pre: !empty()

    	bstdata maximum() const;
    	//returns the maximum value in the BST
    	//pre: !empty()

    	bool isEmpty() const;
    	//determines whether the BST is empty

    	int getSize() const;
    	//returns the size of the tree

    	bstdata getRoot() const;
    	//returns the value stored at the root of the BST
    	//pre: !isEmpty()

    	int getHeight() const;
    	//returns the height of the tree

    	bool search(bstdata data) const;
    	//returns whether the data is found in the tree
    	//pre: !isEmpty()

    	/**manipulation procedures*/

    	void insert(bstdata data);
    	//inserts new data into the BST

    	void remove(bstdata data);
    	//removes the specified value from the tree
    	//pre: data is located in the tree
    	//pre: !isEmpty()

    	/**additional functions*/

    	void inOrderPrint(ostream& out) const;
    	//calls the inOrderPrint function to print out the values
    	//stored in the BST

    	void friendPrint(ostream& out) const;

    	void preOrderPrint(ostream& out) const;
    	//calls the reOrderPrint function to print out the values
    	//stored in the BST

    	void postOrderPrint(ostream& out) const;
    	//calls the postOrderPrint function to print out the values
    	//stored in the BST

};

/**Constructors and Destructor*/

template <class bstdata>
BST<bstdata>::BST() {
	root = NULL;
}


//helper destructor
template <class bstdata>
void BST<bstdata>::freeNode(Node* root) {
	if (root != NULL) {
		freeNode(root->left);
		freeNode(root->right);
		delete root;
	}

}


//wrapper destructor
template <class bstdata>
BST<bstdata>::~BST() {
	freeNode(root);
}

//helper copy constructor
template <class bstdata>
void BST<bstdata>::copyNode(Node* copy) {
	if (copy != NULL) {
		insert(copy->data);
		copyNode(copy->left);
		copyNode(copy->right);
	}
}


//wrapper copy constructor
template <class bstdata>
BST<bstdata>::BST(const BST &bst) {
	root = NULL;
	copyNode(bst.root);
}



/**Manipulation Procedures**/

//helper insertNode
template <class bstdata>
void BST<bstdata>::insertNode(Node* root, bstdata data) {
	Node* N = new Node(data);
	if (data == root->data)
		return;
	else if (data <= root->data) {
		if (root->left == NULL)
			root->left = N;
		else
			insertNode(root->left, data);
	}
	else {
		if (root->right == NULL)
			root->right = N;
		else
			insertNode(root->right, data);
	}
}


//wrapper insert
template <class bstdata>
void BST<bstdata>::insert(bstdata data) {
	if (root == NULL)
		root = new Node(data);	//if the tree is empty insert the value at the root
	else
		insertNode(root, data); //otherwise call the helper function, passing it the root
}


//helper remove
template <class bstdata>
typename BST<bstdata>::Node* BST<bstdata>::removeNode(Node* root, bstdata data) {
	if (root == NULL)
		return root;
	else if (data < root->data)
		root->left = removeNode(root->left, data);
	else if (data > root->data)
		root->right = removeNode(root->right, data);
	else {
		if (getHeight(root) == 0) {
			delete root;
			root = NULL;
		}
		else if (root->left != NULL && root->right == NULL) {

			root = root->left;
			delete root;
		}
		else if (root->right != NULL && root->left == NULL) {

			root = root->right;
			delete root;
		}
		else {
			root->data = minimum(root->right);
			root->right = removeNode(root->right, root->data);
		}
	}
	return root;
}


//wrapper remove
template <class bstdata>
void BST<bstdata>::remove(bstdata data) {
	assert(search(data));
	assert(!isEmpty());
	removeNode(root, data);
}



/**Accessors*/

//helper getSize()
template <class bstdata>
void BST<bstdata>::getSize(Node* root, int& size) const {
	if (root != NULL) {
		size++;
		getSize(root->left, size);
		getSize(root->right, size);
	}
}


//wrapper getSize
template <class bstdata>
int BST<bstdata>::getSize() const {
	int size = 0;
	getSize(root, size);
	return size;
}


//helper getHeight
template <class bstdata>
int BST<bstdata>::getHeight(Node* root) const {
	if (root == NULL)
		return -1;	//height of null child is -1
	else {
		int lh = getHeight(root->left);
		int rh = getHeight(root->right);
		if (lh < rh)
			return 1 + rh;
		else
			return 1 + lh;
	}
}


//wrapper getHeight
template <class bstdata>
int BST<bstdata>::getHeight() const {
	return getHeight(root);
}


template <class bstdata>
bool BST<bstdata>::isEmpty() const {
	return getSize() == 0;
}


template <class bstdata>
bstdata BST<bstdata>::getRoot() const {
	assert(!isEmpty());
	return root->data;
}


//helper minimum
template <class bstdata>
bstdata BST<bstdata>::minimum(Node* root) const {
	if (root->left != NULL)
		return minimum(root->left);
	else
		return root->data;
}


//wrapper minimum
template <class bstdata>
bstdata BST<bstdata>::minimum() const {
	assert(!isEmpty());
	return minimum(root);
}


//helper maximum
template <class bstdata>
bstdata BST<bstdata>::maximum(Node* root) const {
	if (root->right != NULL)
		return maximum(root->right);
	else
		return root->data;
}

//wrapper maximum
template <class bstdata>
bstdata BST<bstdata>::maximum() const {
	assert(!isEmpty());
	return maximum(root);
}

//helper search
template <class bstdata>
bool BST<bstdata>::searchNode(Node* root, bstdata data) const {
	if (data == root->data)
		return true;
	else if (data <= root->data) {
		if (root->left == NULL)
			return false;
		else
			searchNode(root->left, data);
	}
	else {
		if (root->right == NULL)
			return false;
		else
			searchNode(root->right, data);
	}
	//return false;
}

//wrapper search
template <class bstdata>
bool  BST<bstdata>::search(bstdata data) const {
	assert(!isEmpty());
	if (data == root->data)
		return true;
	else
		return searchNode(root, data);
}


/**Print functions**/

//helper inOrderPrint
template <class bstdata>
void BST<bstdata>::inOrderPrint(ostream& out, Node* root) const {
	if (root != NULL) {
		inOrderPrint(out, root->left);
		out << root->data << " ";
		inOrderPrint(out, root->right);
	}
}


//wrapper inOrderPrint
template <class bstdata>
void BST<bstdata>::inOrderPrint(ostream& out) const {
	inOrderPrint(out, root);
}


//helper preOrderPrint
template <class bstdata>
void BST<bstdata>::preOrderPrint(ostream& out, Node* root) const {
	if (root != NULL) {
		out << root->data << " ";
		preOrderPrint(out, root->left);
		preOrderPrint(out, root->right);
	}
}


//wrapper preOrderPrint
template <class bstdata>
void BST<bstdata>::preOrderPrint(ostream& out) const {
	preOrderPrint(out, root);
}


//helper postOrderPrint
template <class bstdata>
void BST<bstdata>::postOrderPrint(ostream& out, Node* root) const {
	if (root != NULL) {
		postOrderPrint(out, root->left);
		postOrderPrint(out, root->right);
		out << root->data << " ";
	}
}


//wrapper postOrderPrint
template <class bstdata>
void BST<bstdata>::postOrderPrint(ostream& out) const {
	postOrderPrint(out, root);
}


#endif //BST_H_
