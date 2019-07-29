
/*=========================================================================

  Name        : Courseproj.cpp - Main UI & File I/O
  Author      : Team 3
  Version     : Ver.3/27
  Copyright   :
  Description : CIS 22C Course Project

  ========================================================================= */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <climits>
#include <cstdlib>
#include <stdlib.h>
//#include <chrono>
//#include <thread>
//#include <unistd.h>
#include "BST.h"
#include "Graph.h"
#include "Users.h"
#include "HashTable.h"


using namespace std;


void popDataStructs(vector<Users> &byID, int &id);
void popFriendsLists(Graph &friendNetwork, vector<Users> &byID);
void dumpStructs(vector<Users> &byID, Graph &fNetwork);

void logIn(HashTable &byUsername, Users &currentUser, int &returnMenu);
void signUp(HashTable &byUsername, Users &currentUser, int &returnMenu, int &greatestID);

void viewOwnProfile(Users &currUser, vector<Users> &byID);
void viewFriendsList(Users &currUser, vector<Users> &byID);

void searchNewFriend(Users &currUser, HashTable &hashByName, HashTable &hashByInterest, Graph &fNetwork, vector<Users> &byID);
void searchByName(Users &currUser, HashTable &hashByName, Graph &fNetwork, vector<Users> &byID);
void searchByInterest(Users &currUser, HashTable &hashByInterest, Graph &fNetwork, vector<Users> &byID);

void friendRecommend(Users &currUser, HashTable &hash, Graph &fNetwork, vector<Users> &byID);

void removeFriend(Users &currUser, HashTable &hash, Graph &fNetwork, vector<Users> &byIdNum);


int main()
{

	cout << "========================================" << endl << endl

	 	 <<	"       Friend Recommendation System     " << endl
		 << "                NINER NET               " << endl << endl

		 << "                 Team 3                 " << endl
		 << "             Mar. 22, 2018              " << endl
		 << "        CIS 22 Course Project, W18      " << endl << endl

		 << "========================================" << endl << endl << endl;

	Users currentUser;

	int greatestID;

	HashTable hashUsers;
	HashTable hashByUsername;
	HashTable hashByInterest;

	vector<Users> byId;

	Graph friendNetwork(30);

	popDataStructs(byId, greatestID);

	for(int i = 0; i < (int)byId.size(); i++)
	{
		hashByUsername.unameInsert(byId[i]);
		hashUsers.insert(byId[i]);
		hashByInterest.ITinsert(byId[i]);
	}

	popFriendsLists(friendNetwork, byId);

	int firstMenuInput = -1;

	//usleep(5000000); // PAUSE 5 sec

	do
	{
		cout << endl << endl <<
				"================ Log-In ================" << endl << endl <<

				"  Welcome to NinerNet!" << endl << endl <<

				"  Would you like to: " << endl << endl <<

				"  1. Log In" << endl <<
		        "  2. Create New Account" << endl << endl <<

			 	"  0. Log-off and Quit" << endl << endl <<

				"========================================" << endl << endl;

		cout << "Enter your selection: ";
		cin >> firstMenuInput;

		if(!cin || firstMenuInput > 2 || firstMenuInput < 0) // Input Error Check
		{
			cout << "\nInvalid Choice, Please enter a number between 0 and 2." << endl;
			firstMenuInput = -1;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch(firstMenuInput)
		{
			case 0:
				dumpStructs(byId, friendNetwork);
				return 0;
				break;
			case 1:
				logIn(hashByUsername, currentUser, firstMenuInput);
				break;
			case 2:
				signUp(hashByUsername, currentUser, firstMenuInput, greatestID);
				byId.push_back(currentUser);
				hashByUsername.unameInsert(currentUser);
				hashUsers.insert(currentUser);
				break;
			default:
				firstMenuInput = -1;
				break;
		}

	}while(firstMenuInput == -1);

	int secondMenuInput = -1;

	do
	{
		for(int a=0; a<30; a++) {
			cout << endl;
		}

		cout <<	"================= Home =================" << endl << endl <<

		        "  Would you like to:" << endl << endl <<

				"  1. View your own profile" << endl <<
				"  2. View your friend list" << endl <<
				"  3. Search a friend" << endl <<
				"  4. Take friend Recommendation" << endl <<
				"  5. Remove Friend (Commented out for now)" << endl << endl <<

				"  0. Log-off and Quit" << endl << endl <<

				"========================================" << endl << endl;

		cout << "Enter your selection: ";
		cin >> secondMenuInput;
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		if(!cin || firstMenuInput > 5 || firstMenuInput < 0) // Input Error Check
		{
			cout << "\nInvalid Choice, Please enter a number between 0 and 5." << endl;
			firstMenuInput = -1;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch(secondMenuInput)
		{
			case 0:
				dumpStructs(byId, friendNetwork);
				break;
			case 1:
				viewOwnProfile(currentUser, byId);
				secondMenuInput = -1;
				break;
			case 2:
				viewFriendsList(currentUser, byId);
				secondMenuInput = -1;
				break;
			case 3:
				searchNewFriend(currentUser, hashUsers, hashByInterest, friendNetwork, byId);
				secondMenuInput = -1;
				break;
			case 4:
				friendRecommend(currentUser, hashUsers, friendNetwork, byId);
				secondMenuInput = -1;
				break;
			case 5:
				removeFriend(currentUser, hashByUsername, friendNetwork, byId);
				secondMenuInput = -1;
				break;
			default:
				break;
		}
	}while(secondMenuInput == -1);

	return 0;
}

void popDataStructs(vector<Users> &byID, int &id)
{
	ifstream fin;

	fin.open("userDatabase.txt");

	if(!fin)
	{
		cout << "User database unable to be found!" << endl;
		exit(-1);
	}

	while(!fin.eof())
	{
		Users temp;
		string testLine;
		getline(fin, testLine);
		if(testLine != "<USER>")
		{
			temp.set_firstName(testLine);

			string tempLName;
			getline(fin, tempLName);
			temp.set_lastName(tempLName);

			string tempUName;
			getline(fin, tempUName);
			temp.set_userName(tempUName);

			string tempPass;
			getline(fin, tempPass);
			temp.set_password(tempPass);

			string tempCollege;
			getline(fin, tempCollege);
			temp.set_college(tempCollege);

			int tempID;
			string tempIdStr;
			getline(fin, tempIdStr);
			stringstream idss(tempIdStr);
			idss >> tempID;
			//tempID = stoi(tempIdStr);
			temp.set_id(tempID);
			id = tempID;


			string wholeInterestStr;
			string tempInterest;
			getline(fin,wholeInterestStr);

			stringstream ss(wholeInterestStr);

			while(getline(ss, tempInterest, ','))
			{
				temp.addInterest(tempInterest);
			}
			byID.push_back(temp);
		}
		else {}
	}

	cout << "loading data structure.. (1/2)" << endl;
	fin.close();
}


void popFriendsLists(Graph &friendNetwork, vector<Users> &byID)
{
	ifstream fin;
	int userID1;
	int userID2;

	fin.open("friendDatabase.txt");

	if(!fin)
	{
		cout << "\nError opening friend database!";
		exit(-2);
	}


	while(fin >> userID1 >> userID2)
	{
		if(userID1 == 0 && userID2 == 0)
		{
			break;
		}
		else
		{	byID[userID1].set_friends(byID[userID2]);
			byID[userID2].set_friends(byID[userID1]);
			friendNetwork.addFriend(byID[userID1], byID[userID2]);
		}
	}

	/**
	for(int i = 0; i < (int)byID.size(); i++)
	{
		friendNetwork.convToBST(byID[i], i);
	}
	*/
	cout << "loading data structure.. (2/2)" << endl << endl << endl;

	fin.close();
}


void logIn(HashTable &byUsername, Users& currentUser, int &returnMenu)
{
	string uNameIn;
	string uPassIn;
	char contCheck = '\n';

	do
	{
		cout << "\nUsername: ";
		cin >> uNameIn;
		cin.clear();

		cout << "Password: ";
		cin >> uPassIn;
		cin.clear();

		Users temp;
		int hashBucket;

		hashBucket = byUsername.searchUserName(uNameIn);

		if(hashBucket == -1)
		{
			cout << "\nYour username could not be matched to a profile!" << endl;
			contCheck = '\n';

			while(contCheck != 'y' && contCheck != 'Y' && contCheck != 'n' && contCheck != 'N')
			{
				cout << "\nWould you like to try again? (y/n): ";
				cin >> contCheck;
			}
		}
		else
		{
			temp = byUsername.giveUser(hashBucket, uNameIn);

			if(temp.get_password() == uPassIn)
			{
				currentUser = temp;
				cout << "\nWelcome " << currentUser.get_firstName() << " " << currentUser.get_lastName() << "!" << endl;
				return;
			}
			else
			{
				cout << "\nYou entered an incorrect password!" << endl;
				contCheck = '\n';

				while(contCheck != 'y' && contCheck != 'Y' && contCheck != 'n' && contCheck != 'N')
				{
					cout << "\nWould you like to try again? (y/n): ";
					cin >> contCheck;
				}
			}
		}
	}while(contCheck == 'y' || contCheck == 'Y');

	returnMenu = -1;
	return;

	exit(0);
}

void signUp(HashTable &byUsername, Users &currentUser, int &returnMenu, int &greatestId)
{
	string newUName;
	string newPass;
	string newFName;
	string newLName;
	string newCollege;

	cout << "Enter your desired username, or enter <BACK> to go back to the menu: ";
	cin >> newUName;

	if(newUName == "<BACK>")
	{
		returnMenu = -1;
		return;
	}

	int hashBucket;

	hashBucket = byUsername.searchUserName(newUName);

	while(hashBucket != -1)
	{
		cout << "Sorry! That username is already taken. Please try a different username.\nEnter your desired username: ";
		cin >> newUName;
		hashBucket = byUsername.searchUserName(newUName);
	}

	currentUser.set_userName(newUName);

	cout << "Enter your desired password: ";
	cin >> newPass;

	currentUser.set_password(newPass);

	cout << "Enter your first name: ";
	cin >> newFName;

	currentUser.set_firstName(newFName);

	cout << "Enter your last name: ";
	cin >> newLName;

	currentUser.set_lastName(newLName);

	cout << "Enter the name of the college you attended: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, newCollege);
	currentUser.set_college(newCollege);

	currentUser.set_id(++greatestId);

	cout << "\nCongratulations " << currentUser.get_firstName() << " " << currentUser.get_lastName() << "! "
			"You've successfully created an account on NinerNet!" << endl << endl;

	return;
}

void viewOwnProfile(Users &currUser, vector<Users> &byID)
{
	char back = '\0';

	cout << "\nYour Profile: " << endl;

	byID[currUser.get_id()].displayProfile(cout);

	cout << "When you are ready to return to the menu, enter any key: ";

	cin >> back;

	if(back != '\0')
	{
		return;
	}
}

void viewFriendsList(Users &currUser, vector<Users> &byID)
{
	cout << "Your Friends List: " << endl;

	byID[currUser.get_id()].print_friends(cout);

	cout << endl;

	cout << "When you are ready to return to the menu, enter any key: ";

	char back = '\0';
	cin >> back;

	if(back != '\0')
	{
		return;
	}

}

void searchNewFriend(Users &currUser, HashTable &hashByName, HashTable &hashByInterest, Graph &fNetwork, vector<Users> &byID)
{
	int searchSelection = -1;

	while(searchSelection < 0 || searchSelection > 2)
	{
		for(int a=0; a<30; a++) {
			cout << endl;
		}
		cout << endl << endl <<
				"=========== Search A Friend ============" << endl << endl <<

		        "  Would you like to: " << endl << endl <<

		        "  1. Search by Name " << endl <<
				"  2. Search by Interest " << endl << endl <<

				"  0. Return to Home" << endl << endl <<

				"========================================" << endl << endl;

		cout << "Enter your selection: ";
		cin >> searchSelection;

		if(searchSelection == 1)
		{
			searchByName(currUser, hashByName, fNetwork, byID);
			return;
		}
		else if(searchSelection == 2)
		{
			searchByInterest(currUser, hashByInterest, fNetwork, byID);
			return;
		}
		else if(searchSelection == 0)
		{
			return;
		}
		else
		{
			cout << "Please enter a number between 0 and 2.";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> searchSelection;
		}
	}
}



void searchByName(Users &currUser, HashTable &hashByName, Graph &fNetwork, vector<Users> &byID)
{
	string searchKey, searchKey2;
	int bucket;
	Users temporary;
	char choice;

	cout << "Enter the first name of the user you wish to search for: ";

	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cin >> searchKey;


	cout << "Enter the last name of the user you wish to search for: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cin >> searchKey2;

	bucket = hashByName.searchName(searchKey, searchKey2);
	if (bucket == -1)
	{
		cout << "The specified user could not be found.\n";
	}
	else
	{
		temporary.copyData(hashByName.findUser(bucket, searchKey, searchKey2));
		byID[temporary.get_id()].displayProfile(cout);
		cout << "Would you like to add this person? (y/n)" << endl;
		cin >> choice;
		if (choice == 'y' || choice== 'Y')
		{
			byID[currUser.get_id()].set_friends(byID[temporary.get_id()]);
			byID[temporary.get_id()].set_friends(byID[currUser.get_id()]);
			fNetwork.addFriend(byID[currUser.get_id()], byID[temporary.get_id()]);
		}
	}
}

void searchByInterest(Users &currUser, HashTable &hashByInterest, Graph &fNetwork,vector<Users> &byID)
{
	string theInterest;
	int numero = 0;
	char choice;
	int option;
	Users temporary;
	cout << "Enter the interest you would like to search: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, theInterest);

	numero = hashByInterest.searchInterest(theInterest);
	if (numero == -1)
	{
		cout << "No users found.\n";
	}
	else
	{
		cout << "\nUsers who are interested in " << theInterest << ":\n";
		hashByInterest.printBucket(cout, numero);
		cout << "Would you like to add someone? (y/n)" << endl;
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			cout << "Which would you like to add?";
			cin >> option;
			while (option <= 0 || option > hashByInterest.countBucket(numero))
			{
				cout << "Please enter a valid option" << endl;
				cin >> option;
			}
			temporary.copyData(hashByInterest.interestUser(numero, option));
			byID[currUser.get_id()].set_friends(byID[temporary.get_id()]);
			byID[temporary.get_id()].set_friends(byID[currUser.get_id()]);
			fNetwork.addFriend(byID[currUser.get_id()], byID[temporary.get_id()]);

		}
	}
}

void friendRecommend(Users &currUser, HashTable &hash, Graph &fNetwork, vector<Users> &byID)
{
	int friendScore[byID.size()];
	int highScore = 0;
	int highIndex = 0;
	int bestScore = byID[currUser.get_id()].getNumInterests() - 2;
	fNetwork.BFS(currUser);
	for (int i = 0; i < fNetwork.getNumVertices(); i++)
	{
		if (i >= byID.size())
			break;
		else
		{
			if (currUser.get_id() == i)
			{
				friendScore[i] = 0;
			}
			else
			{
				friendScore[i] = byID[currUser.get_id()].commonInterests(byID[i]);
				friendScore[i] -= fNetwork.getDistance(i);
			}
		}
	}
	cout << "We recommend you add this user as a friend based on mutual friends and common interests: " << endl;
	for (unsigned int i = 0; i < byID.size(); i++)
	{
		if (friendScore[i] > bestScore)
		{

		}
		else
		{
			if (friendScore[i] > highScore)
			{
				highIndex = i;
				highScore = friendScore[i];
			}
		}
	}
	cout << byID[highIndex] << endl;

	cout << endl;

	cout << "When you are ready to return to the menu, enter any key: ";

	char back = '\0';

	cin >> back;

	if(back != '\0')
	{
		return;
	}
}


void removeFriend(Users &currUser, HashTable &hash, Graph &fNetwork, vector<Users> &byIdNum)
{
/*
	string Username;
	Users temporary;
	bool isFriend;

	cout << "Your Friends List: " << endl;

	byIdNum[currUser.get_id()].print_friends(cout);

	cout << endl;

	cout << "Enter the Username of the friend that you want to remove" << endl;
	//cin.clear();
	//cin.ignore(INT_MAX, '\n');
	cin >> Username;


	int hashBucket;
	hashBucket = hash.searchUserName(Username);
	if (hashBucket == -1)
	{
		cout << "User does not exist" << endl;
	}
	else
	{
		temporary.copyData(hash.giveUser(hashBucket, Username));
		isFriend = byIdNum[currUser.get_id()].searchFriends(byIdNum[temporary.get_id()]);
		if (isFriend == 1)
		{
			byIdNum[currUser.get_id()].removeFriend(byIdNum[temporary.get_id()]);
			byIdNum[temporary.get_id()].removeFriend(byIdNum[currUser.get_id()]);
			//currUser.removeFriend(temporary);
			return;
		}
		else
		{
			cout << "User is not in your friends list." << endl;
		}


	}

	//currUser.friends.remove(byID[userID]);

	//remove friend adjacency on graph
	//update friend bst in user class
*/
}

void dumpStructs(vector<Users> &byID, Graph &fNetwork)
{
	ofstream fout;
	ofstream fout2;

	fout.open("userDatabase.txt");
	fout2.open("friendDatabase.txt");

	for (unsigned int i = 0; i < byID.size(); i++)
	{
		byID[i].outProfile(fout);
		if(i != byID.size()-1)
			fout << '\n';
	}

	fNetwork.fileout(fout2);

	cout << "Logged-off." << endl << endl
		 << "Good Bye!" << endl << endl;

	fout.close();
	fout2.close();
}
