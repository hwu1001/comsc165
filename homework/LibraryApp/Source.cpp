#include <iostream>
#include <vector>
#include <Windows.h>
#include <cctype>
#include "Person.h"
#include "Book.h"

using namespace std;

void initializeTestData(vector<Person> &people);
void initializeTestData(vector<Book> &books);
void displayLibraryMembers(vector<Person> const &members);
void addLibraryMember(vector<Person> &members);
void deleteLibraryMember(vector<Person> &members, vector<Book> &books);
void removeLibraryMemberPointersOnBooks(Person* member, vector<Book> &books);
void editLibraryMember(vector<Person> &members);
void editMemberAttributes(vector<Person> &members, int index);
void getNameAndEmail(string &name, string &email);
int userSelectMember(string prompt, vector<Person> &members);
int userSelectMember(string prompt, vector<Book> &books);
void displayLibraryBooks(vector<Book> const &books);
void checkInBook(vector<Book> &books);
void checkOutBook(vector<Book> &books, vector<Person> &members);

int ID_COUNTER = 5;

int main()
{
	int choice;
	vector<Person> libraryMembers(4);
	initializeTestData(libraryMembers);
	vector<Book> libraryBooks(6);
	initializeTestData(libraryBooks);
	
	do
	{
		const int SELECT_MIN = 1, SELECT_MAX = 7;
		choice = 0;
		cout << "Library App Main Menu" << endl;
		cout << "1. Display all current library members" << endl;
		cout << "2. Add a library member" << endl;
		cout << "3. Remove a library member" << endl;
		cout << "4. Edit data of a current library member" << endl;
		cout << "5. View all books in the library" << endl;
		cout << "6. Check out a book" << endl;
		cout << "7. Check in a book" << endl;
		cout << "What would you like to do? (q to quit) ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			displayLibraryMembers(libraryMembers);
			break;
		case 2:
			addLibraryMember(libraryMembers);
			break;
		case 3:
			deleteLibraryMember(libraryMembers, libraryBooks);
			break;
		case 4:
			editLibraryMember(libraryMembers);
			break;
		case 5:
			displayLibraryBooks(libraryBooks);
			break;
		case 6:
			checkOutBook(libraryBooks, libraryMembers);
			break;
		case 7:
			checkInBook(libraryBooks);
			break;
		default:
			if ((choice > SELECT_MAX || choice < SELECT_MIN) && !cin.fail())
			{
				cout << "Invalid selection, please enter again" << endl;
			}
			break;
		}
	} while (!cin.fail());
	return 0;
}

void initializeTestData(vector<Person> &people)
{
	Person temp;
	Person* tempArr = temp.testData();
	copy(tempArr, tempArr + 4, people.begin());
}

void initializeTestData(vector<Book> &books)
{
	Book temp;
	Book* tempArr = temp.testData();
	copy(tempArr, tempArr + 6, books.begin());
}

void displayLibraryMembers(vector<Person> const &members)
{
	// Display all current members
	system("cls");

	if (members.size() < 1)
	{
		cout << "No current members." << endl;
		return;
	}

	int count = 1;
	cout << "Current Library Members" << endl;
	for (Person member : members)
	{
		cout << "#" << count << endl;
		cout << "Name: " << member.getName() << endl;
		cout << "ID: " << member.getId() << endl;
		cout << "Email: " << member.getEmail() << endl;
		cout << endl;
		count++;
	}
}

void addLibraryMember(vector<Person> &members)
{
	system("cls");
	string name, email;
	cin.ignore();
	getNameAndEmail(name, email);

	// Add a member to the library
	members.push_back(Person(name, ID_COUNTER++, email));
	cout << "Library member added" << endl;

}

void deleteLibraryMember(vector<Person> &members, vector<Book> &books)
{
	system("cls");

	if (members.size() < 1)
	{
		cout << "No members to remove." << endl;
		return;
	}

	int choice;
	
	// display members first
	displayLibraryMembers(members);

	choice = userSelectMember("Enter the number of the member to remove: ", members);

	removeLibraryMemberPointersOnBooks(&members[choice], books);

	members.erase(members.begin() + choice);
	cout << "Library member deleted" << endl;

	return;
}

void editLibraryMember(vector<Person> &members)
{
	system("cls");
	if (members.size() < 1)
	{
		cout << "No current members." << endl;
		return;
	}

	displayLibraryMembers(members);
	int choice = userSelectMember("Enter the number of the member to edit: ", members);

	//edit the attributes of a current member
	editMemberAttributes(members, choice);
	cout << "Library member edited" << endl;
}

void editMemberAttributes(vector<Person> &members, int index)
{
	string name, email;
	cin.ignore();
	getNameAndEmail(name, email);
	members[index].setName(name);
	members[index].setEmail(email);
}

void getNameAndEmail(string &name, string &email)
{
	bool done = false;

	while (!done)
	{
		cout << "Please enter the library member's full name: ";
		getline(cin, name);

		if (name.empty())
		{
			cout << "Name not entered, please re-enter." << endl;
			continue;
		}
		done = true;
	}

	done = false;

	while (!done)
	{
		cout << "Please enter the library member's email address: ";
		getline(cin, email);

		if (email.empty())
		{
			cout << "Email not entered, please re-enter." << endl;
			continue;
		}
		done = true;
	}
}

int userSelectMember(string prompt, vector<Person> &members)
{
	bool done = false;
	int choice = 0;

	while (!done)
	{
		cout << prompt;
		cin >> choice;

		if (cin.fail() || choice < 1 || choice > members.size())
		{
			done = false;
			cin.clear(); // If something like a string is entered it corrupts the buffer and causes an infinite loop - so clear it
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid selection, please enter again" << endl;
		}
		else
		{
			done = true;
		}
	}

	return choice - 1;
}

int userSelectMember(string prompt, vector<Book> &books)
{
	bool done = false;
	int choice = 0;

	while (!done)
	{
		cout << prompt;
		cin >> choice;

		if (cin.fail() || choice < 1 || choice > books.size())
		{
			done = false;
			cin.clear(); // If something like a string is entered it corrupts the buffer and causes an infinite loop - so clear it
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid selection, please enter again" << endl;
		}
		else
		{
			done = true;
		}
	}

	return choice - 1;
}

void displayLibraryBooks(vector<Book> const &books)
{
	// Display all current members
	system("cls");

	if (books.size() < 1)
	{
		cout << "No current members." << endl;
		return;
	}

	int count = 1;
	cout << "Current Library Books" << endl;
	for (Book book : books)
	{
		string checkedOut;
		if (book.getCheckedOutStatus())
		{
			checkedOut = "Yes";
		}
		else
		{
			checkedOut = "No";
		}

		Person* borrower = book.getBorrower();
		string borrowerName;
		if (borrower != nullptr)
		{
			borrowerName = borrower->getName();
		}
		else
		{
			borrowerName = "N/A";
		}

		cout << "#" << count << endl;
		cout << "Title: " << book.getTitle() << endl;
		cout << "Author: " << book.getAuthor() << endl;
		cout << "Checked out?: " << checkedOut << endl;
		cout << "Borrower: " << borrowerName << endl;
		cout << endl;
		count++;
	}
}

void checkInBook(vector<Book> &books)
{
	system("cls");
	
	displayLibraryBooks(books);
	int choice = userSelectMember("Enter the number of the book to check in: ", books);
	books[choice].checkIn();
}

void checkOutBook(vector<Book> &books, vector<Person> &members)
{
	system("cls");
	bool available = false;

	displayLibraryBooks(books);
	int bookChoice = userSelectMember("Enter the number of the book to check out: ", books);
	if (books[bookChoice].getCheckedOutStatus())
	{
		cout << "Book not currently available for check out. Please try again later." << endl;
		return;
	}

	displayLibraryMembers(members);
	int memberChoice = userSelectMember("Enter the number of the member checking out the book: ", members);

	available = books[bookChoice].checkOut(&members[memberChoice]);
	if (!available)
	{
		cout << "Book not currently available for check out. Please try again later." << endl;
	}
}

void removeLibraryMemberPointersOnBooks(Person* member, vector<Book> &books)
{
	for (Book &book : books)
	{
		if (book.getBorrower() == member)
		{
			book.setBorrower(nullptr);
		}
	}
}
