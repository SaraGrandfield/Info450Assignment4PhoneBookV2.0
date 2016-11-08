// Info450Assignment4PhoneBookV2.0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

class PhoneBook;
bool pcheckEnding(char str[], char ending[], int elength);
bool checkEnding(string str, string ending);
bool checkEnding(char str[], char ending[]);
int firstMenu(PhoneBook book);
void secondMenu(PhoneBook book, int selection);

const int MAXSIZE = 100;
const string back = "\\";
const string txt = ".txt";

bool exitP = false;
bool invalid = true;
string errorM = "Please enter a Valid response \n Example: A \n Now You Try:";


class Contact
{
protected:
	string fName;
	string lName;
	string hPhone;
	string cell;
public:
	Contact()
	{}
	Contact(string first, string last, string home, string cellP)
	{
		fName = first;
		lName = last;
		hPhone = home;
		cell = cellP;
	}
	string fNames()
	{
		return fName;
	}
	string lNames()
	{
		return lName;
	}
	string hPhones()
	{
		return hPhone;
	}
	string cells()
	{
		return cell;
	}
	void display()
	{
		cout << fName << " " << lName << "\n";
		cout << "\tHome Phone: " << hPhone << "\n";
		cout << "\tCell Phone: " << cell<< "\n";
	}
	bool equals(Contact toComp)
	{
		if ((fName == toComp.fName)&&(lName == toComp.lName)&&(hPhone == toComp.hPhone)&&(cell == toComp.cell))
		{
			return true;
		}
		else return false;
	}

};

class PhoneBook
{
protected:

	Contact book[MAXSIZE];
	int numEntry=0;
	int newEntry = 0;
	string fileName;

public:
	void makeBook()
	{
		numEntry = 0;
		string name;
		string path;
		
		cout << "Please Enter a Name for Your New Phone Book:" << "\n" << "Do not include file type" << "\n";
		if (!checkEnding(name, txt))
		{
			name = name + txt;
		}
		cin >> name;
		name = name + ".txt";
		cout << "\n" << "Please Enter the Full File Path Ending in a backslash for the location of your New Phone Book" << "\n" ;
		cin >> path;
		if (!checkEnding(path,back))
		{
			path = path + "\\";
		}
		fileName = path + name;
		ofstream outfile(fileName);
		outfile.close();
	}
	
	void getBook()
	{
		numEntry = 0;
		string firstN;
		string lastN;
		string homeP;
		string cell;

		cout << "Please Enter a Full File Path for the Phone Book you Would Like to open:" << "\n";
		cin >> fileName;
		if(!checkEnding(fileName,txt))
		{
			fileName = fileName + txt;
		}
		ifstream datafile(fileName);
		if (!datafile)
		{
			cerr << "ERROR: could not open file" << endl;
			return;
		}

		// read data from file
		while (!datafile.eof())
		{
			getline(datafile, firstN, ' ');
			getline(datafile, lastN, ',');
			getline(datafile, homeP, ',');
			getline(datafile, cell, '|');
			if (firstN!=""&&lastN!=""&&homeP!=""&&cell!="")
			{
				book[numEntry] = Contact(firstN, lastN, homeP, cell);
				numEntry++;
			}
		}
		datafile.close();
	}

	void displayBook()
	{
		string ans;
		for (int x = 0; x < numEntry; x++)
		{
			cout << x + 1 <<". ";
			book[x].display();
			if (x % 5 == 0)
			{
				cout << "Continue? Y/N";
				cin >> ans;
				if (ans == "n"|| ans=="N" || ans=="No")
				{
					break;
				}

			}
		}
		if (numEntry == 0)
		{
			cout << "You're Book is Empty!" << endl;
		}
	}
	
	//Checks to be sure an entry hasn't already been made for a specific person
	bool validateEntry(Contact newCont)
	{		
		for (int x = 0; x < numEntry; x++)
		{
			if (book[x].equals(newCont))
			{
				return false;
			}
		}
		return true;
	}

	//adds and entry to the phone book array, calls the validation method
	void addEntry()
	{
	string firstn;
	string lastn;
	string homePhone;
	string cellPhone;
	if (numEntry>100)
	{
		cout << "Your Address Book is Full";
		return;
	}

	cout << "Enter First Name please:";
	cin >> firstn;
	cout << endl << "Now, Last Name please:";
	cin >> lastn;
	cout << endl << "Home Phone:";
	cin >> homePhone;
	cout << endl << "Cell Phone:";
	cin >> cellPhone;
	cout << endl;
	Contact newPerson(firstn, lastn, homePhone, cellPhone);
	if (validateEntry(newPerson))
	{
		book[numEntry] = newPerson;
		numEntry++;
		newEntry++;
	}
	else
	{
	cout << "You've already entered " << firstn << " " << lastn << "'s information!" << endl;
	}
	} 

	int  saveBook()
	{
		ofstream outfile(fileName,ios::app);
		if (!outfile)
		{
			cout << "unable to open file for writing " << fileName << endl;
			return -1;
		}
		for (int i = (numEntry-newEntry); i < numEntry; i++)
		{
			outfile << book[i].fNames() << " "<< book[i].lNames() << ",";
			outfile << book[i].hPhones() << ",";
			outfile << book[i].cells() << "|";
			cout << i;
		}
		outfile.close();
		cout << "Save Complete" << endl;
		newEntry = 0;
		return 0;
	}
	};

	int main()
	{
		int choice;
		PhoneBook myBook;
		choice = firstMenu(myBook);
		secondMenu(myBook, choice);

		return 0;
	}

	//Powers main Menu
	int firstMenu(PhoneBook book)
	{
		string start = "Please Input just the Action you would like to Perform : \n 1. Open An Existing Book \n 2. Create A New Book \n 3. Quit";
		//Main menu powered by cases and a while loop, DOES NOT perfectly catch errors breaks if user types a char or string instead of a number
		int choice;
		while (invalid != false)
		{
			cout << start << endl;
			cin >> choice;

			switch (choice)
			{
			case 1:
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				book.getBook();
				return 1;
			case 2:
				book.makeBook();
				return 2;
			case 3:
				cout << "End of Program.\n";
				return 3;
			default:
				cout << "Not a Valid Choice. \n";
				cout << "Choose again.\n";
				cin >> choice;
				break;
			}
		}
	}

	void secondMenu(PhoneBook book, int selection)
	{
		string start = "Please Input just the Action you would like to Perform : \n 1. View Book \n 2. Add an Entry \n 3.Save Book \n4. Quit";
		//Main menu powered by cases and a while loop, DOES NOT perfectly catch errors breaks if user types a char or string instead of a number
		int choice;
		if (selection==2)
		{
			cout << "Please enter your first Contact";
			book.addEntry();
		}
		while (invalid != false)
		{
			cout << start << endl;
			cin >> choice;

			switch (choice)
			{
			case 1:
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				book.displayBook();
				break;
			case 2:
				book.addEntry();
				break;
			case 3:
				book.saveBook();
				break;
			case 4:
				cout << "End of Program.\n";
				return;
			default:
				cout << "Not a Valid Choice. \n";
				cout << "Choose again.\n";
				cin >> choice;
				break;
			}
		}
	}

	//checks if a string ends with a specific other string, takes a string and an ending you wish to check
	bool checkEnding(string str, string ending)
	{
		int slength = str.length();
		int elength = ending.length();
		if (elength > slength)
		{
			return false;
		}
		string subStr = str.substr(slength - elength, slength);
		if (subStr == ending)
		{
			return true;
		}
		else return false;
	}


	bool checkEnding(char str[], char ending[])
	{
		int elength = strlen(ending);
		return pcheckEnding(str, ending, elength);
	}

	bool pcheckEnding(char str[], char ending[], int elength)
	{
		int slength = strlen(str);
		int i = 0;
		char* subStr = new char[elength];
		if (elength > slength)
		{
			return false;
		}

		for (int x = (slength - elength); x<elength; x++)
		{
			subStr[i] = str[x];
			i++;
		}
		if (strcmp(subStr, ending))
		{
			return true;
		}
		else return false;
	}
