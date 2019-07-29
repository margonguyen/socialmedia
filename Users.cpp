
/*=========================================================================

  Name        : Users.cpp
  Author      : Team 3
  Version     : Course Proj
  Copyright   :
  Description : CIS 22C Course Project

  ========================================================================= */


#include <iostream>
#include "Users.h"
#include "BST.h"
#include "List.h"


using namespace std;


Users::Users():firstName(""), lastName(""), userName(""), password(""), college(""), id(){};

Users::Users(const Users &user)
{
	firstName = user.firstName;
	lastName = user.lastName;
	id = user.id;
	userName = user.userName;
	password = user.password;
	college = user.college;

	interests=user.interests;

}

Users::Users(string f, string l,string u, string pass, string c, int i)
{
    firstName= f;
    lastName = l;
    userName = u;
    password = pass;
    college = c;
    id =i;
}

string Users::get_firstName() const{
    return firstName;
}

string Users::get_lastName() const{
    return lastName;
}

string Users::get_userName() const{
    return userName;
}

string Users::get_password() const{
    return password;
}

string Users::get_college() const{
    return college;
}

int Users::get_id() const
{
	return id;
}

void Users::print_friends(ostream &out)
{
	friends.inOrderPrint(out);
}

string Users::get_interest() const
{
	return interests.getLast();
}

void Users::set_firstName(string f){
firstName =f;
}

void Users::set_lastName(string l){
lastName = l;
}

void Users::set_userName(string u){
	userName = u;
}

void Users::set_password(string pass){
    password = pass;
}

void Users::set_college(string c){
    college = c;
}
void Users::set_id(int i)
{
	id = i;
}

void Users::addInterest(string intrst)
{
	interests.insertLast(intrst);
}

void Users::set_friends( Users buddy)
{
	friends.insert(buddy);
}

bool Users::operator==(const Users& user) {
	if (firstName == user.firstName && lastName == user.lastName)
	{
		return true;
	}
	else if (userName == user.userName)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Users::operator <(const Users& user)
{string name = lastName + firstName;
string name1 = user.lastName + user.firstName;
    if (name < name1)
        return true;
    else if (name == name1 && userName !=user.userName)
        return (userName < user.userName);
    else if (name == name1 && userName == user.userName)
        return false;
    else
        return false;
}

bool Users::operator >(const Users& user)
{ string name = lastName + firstName;
string name1 = user.lastName + user.firstName;
    if (name > name1)
        return true;
    else if (name == name1 && userName != user.userName)
        return (userName > user.userName);
    else if (name == name1 && userName==user.userName)
        return false;
    else
        return false;
}

bool Users::operator <=(const Users& user)
{
	string name = lastName + firstName;
	string name1 = user.lastName + user.firstName;
	    if (name < name1)
	        return true;
	    else if (name == name1 && userName != user.userName)
	        return (userName > user.userName);
	    else if (name == name1 && userName==user.userName)
	        return true;
	    else
	        return false;
}

ostream& operator <<(ostream &os, const Users& user)
{
    os << user.firstName << " " <<  user.lastName << " (" << user.userName << ")" << "\n";

    return os;
}

void print(ostream& os, const Users users)
{		os <<"Friends of " << users.firstName << " is";

	users.friends.inOrderPrint(os);
}


void Users::printFriend(ostream & os)
{
	friends.inOrderPrint(os);
}

void Users::displayProfile(ostream& out)
{
	out << endl << firstName << " " << lastName;
	out << " (" << userName << ")" << endl;
	out << "From " << college << endl;
	out << "Interests: \n";
	interests.printNumberedList();
	out << "ID: " << id << endl;
}

int Users::sizeInterests()
{
	return interests.getLength();
}

void Users::iteratorStart()
{
	interests.startIterator();
}

string Users::iteratorGet()
{
	return interests.getIterator();
}

void Users::iteratorAdvance()
{
	interests.advanceIterator();
}

bool Users::operator!=(const Users& user)
{
	if (firstName == user.firstName && lastName == user.lastName)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Users::copyData(Users user)
{
	firstName = user.get_firstName();
	lastName = user.get_lastName();
	userName = user.get_userName();
	password = user.get_password();
	college = user.get_college();
	id = user.get_id();


	List<string> newIntrsts = user.interests;
	interests = newIntrsts;
}

void Users::removeFriend(Users user)
{
	friends.remove(user);
	return;
}

bool Users::searchFriends(Users user)
{
	return friends.search(user);
}

void Users::outProfile(ostream& out)
{
	out << firstName << endl << lastName << endl;
	out << userName << endl << password << endl;
	out << college << endl << id << endl;
	interests.printCommaList(out);
	out << endl;
	out << "<USER>";
}

int Users::commonInterests(Users two)
{
	string interest1;
	int common = 0;

	/*interests.startIterator();
	int common = 0;

	for (int i = 0; i < interests.getLength(); i++)
	{
		interest1 = interests.getIterator();
		if (two.interests.linearSearch(interest1) == true)
		{
			common++;
		}
		interests.advanceIterator();
	}
	*/
	return common;
}

int Users::getNumInterests()
{
	return interests.getLength();
}
