
/*=========================================================================

  Name        : HashTable.h
  Author      : Team 3
  Version     : Course Proj
  Copyright   :
  Description : CIS 22C Course Project

  ========================================================================= */


#ifndef HASHTABLE_H_
#define HASHTABLE_H_


#include <string>
#include "List.h"
#include "Users.h"
using namespace std;


class HashTable {
public:

    HashTable(){}
    //constructor

    ~HashTable(){}
    //destructor

    int hash(string key) const;
    //returns the hash value for the given key
    //the hash value is the sum of
    //of the ASCII values of each char in the key
    //% the size the of the table

    void insert(Users u);
    //inserts a new user into the table (USES NAME)
    //calls the hash function on the key to determine
    //the correct bucket

    void remove(Users u);
    //removes u from the table
    //calls the hash function on the key to determine
    //the correct bucket
    //pre: u is in the table


//================== NAME TABLE FUNCTIONS ======================

    int searchName(string firstName, string lastName) const;
    //searches TABLE based on NAME
    //returns bucket of linked list containing user w/ same name
    //returns -1 if no user
    Users findUser(int index, string fname, string lname);
    //returns user given a table index and the name
    //use bucket returned by searchName


//================== INTEREST TABLE FUNCTIONS ==================

    int searchInterest(string interest) const;
    //find index of a given interest using hash

    void ITinsert(Users u);
    //insert user into table hashing by interest

    Users interestUser(int bucket, int index);


//=============== USERNAME TABLE FUNCTIONS =====================

    void unameInsert(Users u);
    //insert user into table hashing by username

    int searchUserName(string userName);
    //searches TABLE based on USERNAME
    //returns bucket of linked list containing user w/ username
    //returns -1 if no user

    Users giveUser(int bucket, string userName);
    //returns user given bucket and username
    //use after searchUserName returns the bucket

//================== PRINT FUNCTIONS =====================

    int countBucket(int index) const;
    //returns size of bucket

    void printBucket(ostream& out, int index) const;
    //prints a bucket


private:
    static const int SIZE = 100;
    List<Users> Table[SIZE];
};

int HashTable::hash(string key) const
{
    char *p = new char[key.length()+1];

    for (int j = 0; j < (int) key.length(); j++){
        p[j] = key[j];
    }

    int h = 0;
    int i;

    for (i = 0; i < (int) key.length(); i++)
    {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return (abs(h) % SIZE);
}

/**
int HashTable::hash(string key) const
{
	int index, sum = 0;
	for(unsigned int i = 0; i < key.length(); i++)
	{
		sum += (int) key[i]; //summing the ASCII values for each character in the string
	}
	index = sum % SIZE; //dividing the summed ASCII values by 35 && storing remainder as my index
	return index;

}
*/

void HashTable::insert(Users u)
{
	string newKey = u.get_firstName() + u.get_lastName();
	Table[hash(newKey)].insertLast(u);
}

void HashTable::remove(Users u)
{
	//assert(search(u) != -1);
	string newKey = u.get_firstName() + u.get_lastName();
	int index = Table[hash(newKey)].linearSearch(u);
	Table[hash(newKey)].startIterator();
	Table[hash(newKey)].advanceToIndex(index);
	Table[hash(newKey)].removeIterator();
}


//================== NAME TABLE FUNCTIONS ======================

int HashTable::searchName(string firstName, string lastName) const
{
	Users temp;
	temp.set_firstName(firstName);
	temp.set_lastName(lastName);

	string key = firstName + lastName;
	int index = hash(key);
	if (Table[index].isEmpty()) {
		return -1;
	} else if (Table[index].linearSearch(temp) == -1) {
		return -1;
	} else {
		return index;
	}
}

Users HashTable::findUser(int bucket, string fname, string lname)
{
	Users temp, dummy;
	dummy.set_firstName(fname);
	dummy.set_lastName(lname);
	int index = Table[bucket].linearSearch(dummy);
	if (index == -1)
	{
		cout << "error";
	}
	else
	{
		if (index == 1)
		{
			temp.copyData(Table[bucket].getFirst());
		}
		else
		{
			Table[bucket].advanceToIndex(index);
			temp.copyData(Table[bucket].getIterator());
			return temp;
		}
	}
	return temp;
}


//================== INTEREST TABLE FUNCTIONS ==================

int HashTable::searchInterest(string interest) const
{
	int index = hash(interest);
	if (Table[index].isEmpty()) {
		return -1;
	}
	 else {
		return index;
	}
}

void HashTable::ITinsert(Users u)
{
	u.iteratorStart();
	int index;
	string hobby;
	for (int i = 0; i < u.sizeInterests()-1; i++)
	{
		hobby = u.iteratorGet();
		index = hash(hobby);
		Table[index].insertLast(u);
		u.iteratorAdvance();
	}
	hobby = u.iteratorGet();
	index = hash(hobby);
	Table[index].insertLast(u);
}

Users HashTable::interestUser(int bucket, int index)
{
	Users temp;

		if (bucket == 1)
		{
			temp.copyData(Table[bucket].getFirst());
		}
		else
		{
			Table[bucket].advanceToIndex(index);
			temp.copyData(Table[bucket].getIterator());
			return temp;
		}
	return temp;
}

//=============== USERNAME TABLE FUNCTIONS =====================


void HashTable::unameInsert(Users u)
{
	string uname = u.get_userName();
	int index = hash(uname);
	Table[index].insertLast(u);
}

int HashTable::searchUserName(string userName)
{
	Users temp;
	temp.set_userName(userName);

	int index = hash(userName);
	if (Table[index].isEmpty()) {
		return -1;
	} else if (Table[index].linearSearch(temp) == -1) {
		return -1;
	} else {
		return index;
	}
}

Users HashTable::giveUser(int bucket, string userName)
{
	Users temp, dummy;
	dummy.set_userName(userName);
	int index = Table[bucket].linearSearch(dummy);
	if (index == -1)
	{
		cout << "error";
	}
	else
	{
		if (index == 1)
		{
			temp.copyData(Table[bucket].getFirst());
		}
		else
		{
			Table[bucket].advanceToIndex(index);
			temp.copyData(Table[bucket].getIterator());
			return temp;
		}
	}
	return temp;
}

//================== PRINT FUNCTIONS =====================


int HashTable::countBucket(int index) const
{
	assert(index >= 0);
	assert(index < SIZE);
	return Table[index].getLength();
}

void HashTable::printBucket(ostream& out, int index) const
{
	assert(index >= 0);
	assert(index < SIZE);
	Table[index].printNumberedList();
}


#endif /* HASHTABLE_H_ */
