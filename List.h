
/*=========================================================================

  Name        : List.h
  Author      : Team 3
  Version     : Course Proj
  Copyright   :
  Description : CIS 22C Course Project

  ========================================================================= */


#ifndef LIST_H_
#define LIST_H_


#include <cstddef>
#include <iostream>
#include <assert.h>


using namespace std;


template <class listdata> //List stores generic listdata, not any specific C++ type
class List {

private:
	struct Node {
		listdata data;
		Node* next;
		Node* prev;

		Node(listdata newData){
			data = newData;
			next = NULL;
			prev = NULL;
		}
	};

	Node* first;
	Node* last;
	Node* iterator;
	int length;

  void reversePrint(Node* node) const;
  //Helper function for the public reversePrint() function.
  //Recursively prints the data in a List in reverse.

  bool isSorted(Node* node) const;
  //Helper function for the public isSorted() function.
  //Recursively determines whether a list is sorted in ascending order.

  int binarySearch(int low, int high, listdata data) const;
  //Recursively search the list by dividing the search space in half
  //Returns the index of the element, if it is found in the List
  //Returns -1 if the element is not in the List
  //Post: The iterator location has not been changed

public:
	/* Constructors and Destructors */

	List();
	//Default constructor; initializes and empty list
	//Postcondition: A new empty list is created

	List(const List &list);
	//copy constructor: makes a copy of the list object

	~List();
	//Destructor. Frees memory allocated to the list
	//Postcondition: The list is destroyed (removed)

	/* Manipulation Procedures */

	void removeFirst();
	//Removes the value stored in first node in the list
	//Precondition: The list must not be empty
	//Postcondition: The first data of list is removed

	void removeLast();
	//Removes the value stored in the last node in the list
	//Precondition: The list must not be empty
	//Postcondition: The last data of list is removed

	void insertFirst(listdata data);
	//Inserts a new data at the beginning of the list
	//If the list is empty, the new data becomes both first and last
	//Postcondition: New front of list is created (New data is added in front of the first)

	void insertLast(listdata data);
	//Inserts a new data at the end of the list
	//If the list is empty, the new data becomes both first and last
	//Postcondition: New end of list is created (New data is added after the last)

	void startIterator();
	//startIterator: moves the iterator to the start of the list
	//Precondition: The list must not be empty
	//Postcondition: The iterator now points at the first Node

	void removeIterator();
	//removeIterator: removes the element currently pointed to by the iterator. Iterator then points to NULL.
	//Precondition: The list must not be empty, the iterator must not be pointing at NULL
	//If iterator was pointing at first or last, adjust first or last
	//If the list only has one element, let first, last, iterator all point at NULL
	//Postcondition: The element pointed by iterator gets removed, Iterator points to NULL

	void insertIterator(listdata data);
	//insertIterator: inserts an element after the node currently pointed to by the iterator
	//Precondition: The list must not be empty, the iterator must not be pointing at NULL
	//If iterator was pointing at last, let last point to the new Node inserted
	//Postcondition: The new Node is inserted after the node pointed to by the iterator

	void advanceIterator();
	//advanceIterator: moves the iterator up by one node
	//Precondition: The iterator, iterator->next must not be pointing at NULL

	void reverseIterator();
	//reverseIterator: moves the iterator down by one node
	//PreconditionL The iterator, iterator->prev must not be pointing at NULL


	void advanceToIndex(int index);
	//Moves the iterator to the node whose index number is specified in the parameter
	//Nodes are numbered starting at 1 through the size of the List
	//Pre: size != 0
	//Pre: index <= size

	/* Accessors */

	listdata getFirst() const;
	//Returns the first data in the list
	//Precondition: The list must not be empty

	listdata getLast() const;
	//Returns the last data in the list
	//Precondition: The list must not be empty

	bool isEmpty() const;
	//Determines whether a list is empty.

	int getLength() const;
	//Returns the size of the list

	bool offEnd() const;
	//offEnd: returns whether the iterator is off the end of the list, i.e. is NULL

	listdata getIterator() const;
	//getIterator: returns the element currently pointed at by the iterator

	bool operator==(const List &list);
	//Tests two lists to determine whether their contents are equal
	//Postcondition: returns true if lists are equal and false otherwise

	bool isSorted() const;
	//Wrapper function that calls the isSorted helper function to determine whether
	//a list is sorted in ascending order.
	//We will consider that a list is trivially sorted if it is empty.
	//Therefore, no precondition is needed for this function

	int getIndex() const;
	 //Indicates the index of the Node where the iterator is currently pointing
	 //Nodes are numbered starting at 1 through the size of the list
	 //Pre: !offEnd()

	/* Additional List Operations */

	void printList(ostream& out) const;
	//Prints to the console the value of each data in the list sequentially
	//and separated by a blank space
	//Prints nothing if the list is empty
	//Prints a empty newline character if it's empty..

	void printNumberedList() const;
	//printNumberedList: prints the contents of the linked list to the screen in the format #. <element> followed by a newline

	void printCommaList(ostream& out) const;

	void reversePrint() const;
	//Wrapper function that calls the reverse helper function to print a list in reverse
	//prints nothing if the List is empty

	int linearSearch(listdata data) const;
	//Searchs the list, element by element, from the start of the List to the end of the List
	//Returns the index of the element, if it is found in the List
	//Does not call the indexing functions in the implementation
	//Returns -1 if the element is not in the List
	//Pre: length != 0
	//Post: The iterator location has not been changed


	int binarySearch(listdata data) const;
	//Returns the index where data is located in the List
	//Calls the private helper function binarySearch to perform the search
	//Pre: length != 0
	//Pre: List is sorted (must test on a sorted list)
	//Post: The iterator location has not been changed
};


/* Constructors and Destructors */

//constructor: constructs a new linked list object.
template <class listdata>
List<listdata>::List() {
    first = NULL;
    last = NULL;
    iterator = NULL;
    length = 0;
}

//copy constructor: makes a copy of the list object
template <class listdata>
List<listdata>::List(const List &list)
{
    if(list.first == NULL) //If the original list is empty, make an empty list for this list
    {
        first = last = iterator = NULL;
    }
    else
    {
        first = new Node(list.first->data); //calling Node constructor
        Node* temp = list.first; //set a temporary node pointer to point at the first of the original list
        iterator = first; //set iterator to point to first node of the new list

        while(temp->next != NULL)
        {
            temp = temp->next; //advance up to the next node in the original list
            iterator->next = new Node(temp->data); //using node constructor to create new node w/ copy of data
          	iterator->next->prev = iterator;
          	iterator = iterator->next; //advance to this new node
        }

        last = iterator; //Why do I need this line of code?
        iterator = NULL;

    }

    length = list.length;
}

//destructor: frees the memory associated with the linked list
template <class listdata>
List<listdata>::~List()
{
    Node* b = first;
    Node* a = NULL; //a stands for "after" (i.e. after b)
    while (b != NULL)
    {
        a = b->next; //move a to node after b
        delete b; //remove b (you know it is not NULL from if)
        b = a; //b "catches up" with a (both point to same place in list)
    }
}

/* Manipulation Procedures */

//insertFirst: inserts an element at the beginning of the linked list
template <class listdata>
void List<listdata>::insertFirst(listdata data)
{
    Node* N = new Node(data);
    if (length == 0) //The list is empty
    {
        first = N;
        last = N;
    }
    else //The list has one or more Nodes
    {
        N->next = first; //new Node to previous first Node
        first->prev = N; //previous first Node to new Node
        first = N; //first to new Node
    }
    length++;
}

//insertLast: inserts an element at the end of the list
template <class listdata>
void List<listdata>::insertLast(listdata data)
{
    Node* N = new Node(data);
    if (length == 0) //The list is empty
    {
        first = N;
        last = N;
    }
    else //The list has one or more Nodes
    {
        N->prev = last; //new Node to previous last Node
        last->next = N; //previous last Node to new Node
        last = N; //last to new Node
    }
    length++;
}

//removeFirst: removes the element at the beginning of the list
template <class listdata>
void List<listdata>::removeFirst()
{
	assert(length!=0);
	if(length == 1) //The list has only one node
    {
        delete first;
        first = last = iterator = NULL;
        length = 0;
    }
    else //The list has more than one node
    {
        Node* temp = first;
        first = first->next;
        first->prev = NULL;
        delete temp;
        length--;
    }
}

//removeLast: removes the element at the end of the list
template <class listdata>
void List<listdata>::removeLast()
{
	assert(length != 0);
    if(length == 1) //case2: The list has only one node
    {
        delete last;
        first = last = iterator = NULL;
        length = 0;
    }
    else //case3: The list has more than one node
    {
        Node* temp = last->prev;
        delete last;
        last = temp; //set last to be the former second to last node stored in temp
        last->next = NULL; //set pointer to point at NULL rather than deallocated memory
        length--;
    }
}

//startIterator: moves the iterator to the start of the list
template <class listdata>
void List<listdata>::startIterator()
{
	assert (length != 0);
	iterator = first;
}

//removeIterator: removes the element currently pointed to by the iterator. Iterator then points to NULL.
template <class listdata>
void List<listdata>::removeIterator()
{
	assert(iterator != NULL);//precondition

	/*if (length == 1) //edge case, length =1
	{
		delete iterator;
		first = last = iterator = NULL;
		length = 0;
	}*/
	if (iterator == first) //edge case, iterator = first
		removeFirst();
	else if (iterator == last) //edge case, iterator = last
		removeLast();
	else //general case
	{
		iterator->prev->next = iterator->next;
		iterator->next->prev = iterator->prev;
		delete iterator;
		length --;
		iterator = NULL;
	}
	//iterator = NULL;
}

//insertIterator: inserts an element after the node currently pointed to by the iterator
template <class listdata>
void List<listdata>::insertIterator(listdata data)
{
	assert(iterator != NULL); //precondition

	if (iterator == last) //edge case, iterator pointing at the end Node
		insertLast(data);
	else { //general case
		Node* N = new Node(data);
		N->next = iterator->next;
		N->prev = iterator;
		iterator->next = N;
		N->next->prev = N;
		length ++;
	}
}

//advanceIterator: moves the iterator up by one node
template <class listdata>
void List<listdata>::advanceIterator()
{
	assert(iterator != NULL);
	iterator = iterator->next;
}

//reverseIterator: moves the iterator down by one node
template <class listdata>
void List<listdata>::reverseIterator()
{
	assert(iterator != NULL);
	iterator = iterator->prev;
}

/* Access Functions */

//isEmpty: tests whether the linked list is empty
template <class listdata>
bool List<listdata>::isEmpty() const
{
    return length == 0;
}

//getLength: returns the current length of the list
template <class listdata>
int List<listdata>::getLength() const
{
	return length;
}

//getFirst: returns the first element
template <class listdata>
listdata List<listdata>::getFirst() const
{
	assert(length != 0);
	return first -> data;
}

//getLast: returns the last element
template <class listdata>
listdata List<listdata>::getLast() const
{
	assert(length != 0);
	return last -> data;
}

//getIterator: returns the element currently pointed at by the iterator
template <class listdata>
listdata List<listdata>::getIterator() const
{
	assert(iterator != NULL);
	return iterator->data;
}

//offEnd: returns whether the iterator is off the end of the list, i.e. is NULL
template <class listdata>
bool List<listdata>::offEnd() const
{
	return iterator == NULL;
}

//equalLists: compares two lists to see if they are equal.
template <class listdata>
bool List<listdata>::operator==(const List &list)
{
    if(length != list.length)
        return false;
    Node* temp1 = first;
    Node* temp2 = list.first;
    while(temp1 != NULL)
    {
        if(temp1->data != temp2->data)
            return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

/* Additional List Operations */

//printList: prints the contents of the linked list to the screen separated by a blank space
template <class listdata>
void List<listdata>::printList(ostream& out) const
	{
		if (length == 0)
		{
			out << " \n";
		}
		else
		{
	    Node* temp = first; //create a temporary iterator
	    while (temp != NULL) {

	        //Add two lines of code here
	    	out << temp->data;
	    	temp = temp->next;

	        //Hint: One statement should contain a cout
	    }
	    }
	    out << endl;
}

//printNumberedList: prints the contents of the linked list to the screen in the format #. <element> followed by a newline
template <class listdata>
void List<listdata>::printNumberedList() const
{
    Node* temp = first; //create a temporary iterator
		int num = 1;
    while (temp != NULL) {
        cout << num << ". " << temp->data << endl; //print the data in Node
        temp = temp->next; //point to the next Node
        num++;
    }
    cout << endl; //move to the new line
}

template <class listdata>
void List<listdata>::printCommaList(ostream& out) const
{
    Node* temp = first; //create a temporary iterator
    while (temp != NULL) {
        out << temp->data << ','; //print the data in Node
        temp = temp->next; //point to the next Node
    }
}

template <class listdata>
void List<listdata>::reversePrint() const
{
	reversePrint(last);
	cout << endl;
}

template <class listdata>
void List<listdata>::reversePrint(Node* node) const
{
	   if (node->prev == NULL) {
	    cout << node->data << " ";
	  }
	  else
	  {
		cout << node->data << " ";
	  	reversePrint(node->prev);
	  }
}

template <class listdata>
bool List<listdata>::isSorted() const
{
	return isSorted(first);
}


template <class listdata>
bool List<listdata>::isSorted(Node* node) const
{
	if (node->next == NULL)
	{
		return true;
	}
	else if (node->data > node->next->data)
	{
		return false;
	}
	else
	{
		return isSorted(node->next);
	}
}

template <class listdata>
int List<listdata>::getIndex() const
{
	assert(iterator != NULL);
	Node* temp = iterator;
	int count = length+1;
	while (temp != NULL)
	{
		temp = temp->next;
		count--;
	}
	return count;
}

template <class listdata>
void List<listdata>::advanceToIndex(int index)
{
	assert(length != 0);
	assert(index <= length);
	startIterator();
	for (int i = 1; i < index; i++)
	{
		advanceIterator();
	}
}

template <class listdata>
int List<listdata>::linearSearch(listdata data) const
{
	assert(length != 0);
	Node* temp = first;
	int index = 1;
	while (temp != NULL) {
		if (temp->data == data)
		{
			return index;
		}
		else
		{
			temp = temp->next;
			index++;
		}
	} return -1;
}



template <class listdata>
int List<listdata>::binarySearch(listdata data) const
{
	assert(length != 0);
	assert(isSorted());
	return binarySearch(1, length, data);
}


template <class listdata>
int List<listdata>::binarySearch(int low, int high, listdata data) const
{
	if(high < low)
	{
		return -1;
	}
	int mid = low + (high - low) / 2;
	int midVal;
	Node* temp = first;
	for (int i = 0; i < mid; i++)
	{
		midVal = temp->data;
		temp = temp->next;
	}

	if(midVal == data)
	{
		return mid;
	}
	else if(data < midVal)
	{
		return binarySearch(low,mid-1,data);
	}
	else
	{
		return binarySearch(mid+1,high,data);
	}
}


#endif /* LIST_H_ */
