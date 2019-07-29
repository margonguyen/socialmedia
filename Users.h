
/*=========================================================================

  Name        : Users.h
  Author      : Team 3
  Version     : Course Proj
  Copyright   :
  Description : CIS 22C Course Project

  ========================================================================= */


#ifndef USERS_H_
#define USERS_H_


#include <string>
#include <ostream>
#include "BST.h"
#include "List.h"


using namespace std;


class Users {
private:
		string firstName;
	    string lastName;
	    string userName;
	    string password;
	    string college;
	    int id;
	    BST<Users> friends;
	    List<string> interests;
public:

    Users();
    Users(const Users &user);
    Users(string f, string l,string u, string pass, string c, int i);


    string get_firstName() const;
    string get_lastName() const;
    string get_userName() const;
    string get_password() const;
    string get_college() const;
    int get_id() const;

    void print_friends(ostream &out);
    string get_interest() const;


    void set_firstName(string f);
    void set_lastName(string l);
    void set_userName(string u);
    void set_password(string pass);
    void set_college(string c);
    void set_id(int i);
    void addInterest(string intrst);
    void set_friends(Users buddy);


    friend ostream& operator<<(ostream & os, const Users& users);
    bool operator<(const Users& users);
    bool operator>(const Users& users);
    bool operator <=(const Users& user);


	void displayProfile(ostream& out);
	bool operator==(const Users& user);
	bool operator!=(const Users& user);
	int sizeInterests();
	void iteratorStart();
	string iteratorGet();
	void iteratorAdvance();


    friend void print(ostream& os, const Users users);
    friend void getFriend(const Users &users);


    void printFriend(ostream & os);
    void copyData(Users user);

    void removeFriend(Users user);
    bool searchFriends(Users user);

    void outProfile(ostream& out);

    int commonInterests(Users two);
    int getNumInterests();
};

#endif /* USERS_H_ */


