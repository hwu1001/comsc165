// Henry Wu
// COMSC 165
// Section 3015
// Homework 3

#include <iostream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include "Person.h"
#include "Book.h"

using namespace std;

void initializeTestData(vector<Person> &people);
void initializeTestData(vector<Book> &books);
void displayLibraryMembers(vector<Person> const &members);
void editLibraryMember(vector<Person> &members);
void editMemberAttributes(vector<Person> &members, int index);
void getNameAndEmail(string &name, string &email);
int userSelectMember(string prompt, int arraySize);
void displayLibraryBooks(vector<Book> const &books);
void displayLibraryBook(Book book);
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
		const int SELECT_MIN = 1, SELECT_MAX = 5;
		choice = 0;
		cout << "Library App Main Menu" << endl;
		cout << "1. Display all current library members" << endl;
		cout << "2. Edit data of a current library member" << endl;
		cout << "3. View all books in the library" << endl;
		cout << "4. Check out a book" << endl;
		cout << "5. Check in a book" << endl;
		cout << "What would you like to do? (q to quit) ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			displayLibraryMembers(libraryMembers);
			break;
		case 2:
			editLibraryMember(libraryMembers);
			break;
		case 3:
			displayLibraryBooks(libraryBooks);
			break;
		case 4:
			checkOutBook(libraryBooks, libraryMembers);
			break;
		case 5:
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

///<summary> Initializes test data for library members. </summary>
///<param name="people"> Vector of people that is populated with test data. </param>
///<returns> Nothing. </returns>
void initializeTestData(vector<Person> &people)
{
	Person temp;
	Person* tempArr = temp.testData();
	copy(tempArr, tempArr + 4, people.begin());
}

///<summary> Initializes test data for library books. </summary>
///<param name="books"> Vector of books that is populated with test data. </param>
///<returns> Nothing. </returns>
void initializeTestData(vector<Book> &books)
{
	Book temp;
	Book* tempArr = temp.testData();
	copy(tempArr, tempArr + 6, books.begin());
}

///<summary> Displays all current library members at the console. </summary>
///<param name="members"> Vector of library members. </param>
///<returns> Nothing. </returns>
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

///<summary> Prompts the user for a library member to edit and allows editing of name and email. </summary>
///<param name="members"> Vector of library members. </param>
///<returns> Nothing. </returns>
void editLibraryMember(vector<Person> &members)
{
	system("cls");
	if (members.size() < 1)
	{
		cout << "No current members." << endl;
		return;
	}

	displayLibraryMembers(members);
	int choice = userSelectMember("Enter the number of the member to edit: ", members.size());

	//edit the attributes of a current member
	editMemberAttributes(members, choice);
	cout << "Library member edited" << endl;
}

///<summary> Sets the library member's new name and email after prompting for them.</summary>
///<param name="members"> Vector of library members. </param>
///<param name="index"> Index in the vector of the library member to edit. </param>
///<returns> Nothing. </returns>
void editMemberAttributes(vector<Person> &members, int index)
{
	string name, email;
	cin.ignore();
	getNameAndEmail(name, email);
	members[index].setName(name);
	members[index].setEmail(email);
}

///<summary> Prompts the user for a library member's new name and email.</summary>
///<param name="name"> Name to get from the user prompt. </param>
///<param name="email"> Email to get from the user prompt. </param>
///<returns> Nothing. </returns>
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

///<summary> Handles incorrect input after asking for a number from an iterable object.</summary>
///<param name="prompt"> String to display to the user about entering the appropriate number. </param>
///<param name="arraySize"> Size of the array the user is selecting from. </param>
///<returns> An integer in the form of whatever the user entered minus 1 (assumes array is using base 0). </returns>
int userSelectMember(string prompt, int arraySize)
{
	bool done = false;
	int choice = 0;

	while (!done)
	{
		cout << prompt;
		cin >> choice;

		if (cin.fail() || choice < 1 || choice > arraySize)
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

///<summary> Displays all library books to the prompt.</summary>
///<param name="books"> Vector of library books. </param>
///<returns> Nothing. </returns>
void displayLibraryBooks(vector<Book> const &books)
{
	// Display all current members
	system("cls");

	if (books.size() < 1)
	{
		cout << "No library books listed." << endl;
		return;
	}

	int count = 1;
	cout << "Current Library Books" << endl;
	for (Book book : books)
	{

		cout << "#" << count << endl;
		displayLibraryBook(book);
		count++;
	}
}

///<summary> Displays a single library book to the prompt including the title, author, and copies/statuses.</summary>
///<param name="book"> A single library book object. </param>
///<returns> Nothing. </returns>
void displayLibraryBook(Book book)
{
	vector<Person*> borrowers = book.getBorrower();
	vector<bool> checkedOutStatuses = book.getCheckedOutStatus();
	cout << "Title: " << book.getTitle() << endl;
	cout << "Author: " << book.getAuthor() << endl;
	cout << "Copies:" << endl;
	cout << "   " << setw(14) << left << "Checked Out?" << setw(8) << "Borrower" << endl;
	cout << "   " << setw(14) << left << "============" << setw(8) << "========" << endl;
	for (int i = 0; i < book.getNumCopies(); i++)
	{
		string checkedOut;
		string borrowerName;
		int checkedWidth = 0;

		if (checkedOutStatuses[i])
		{
			checkedOut = "Yes";
		}
		else
		{
			checkedOut = "No";
		}

		if (borrowers[i] != nullptr)
		{
			borrowerName = borrowers[i]->getName();
		}
		else
		{
			borrowerName = "N/A";
		}
		cout << i + 1 << ". " << setw(14) << left << checkedOut << setw(borrowerName.length()) << left << borrowerName << endl;
	}
	cout << endl;

}

///<summary> Prompts a user for a book and copy of that book to check in to the library.</summary>
///<param name="books"> Vector of library books. </param>
///<returns> Nothing. </returns>
void checkInBook(vector<Book> &books)
{
	system("cls");

	displayLibraryBooks(books);
	int choice = userSelectMember("Enter the number of the book to check in: ", books.size());
	int copyIndex = userSelectMember("Enter the copy number to check in: ", books[choice].getNumCopies());

	if (books[choice].checkIn(copyIndex))
	{
		cout << "Book checked in" << endl;
	}
	else
	{
		cout << "Book was not able to be checked in" << endl;
	}
}

///<summary> Prompts a user for a book to check out of the library.</summary>
///<param name="books"> Vector of library books. </param>
///<param name="members"> Vector of library members. </param>
///<returns> Nothing. </returns>
void checkOutBook(vector<Book> &books, vector<Person> &members)
{
	system("cls");
	bool available = false;
	int copyIndex;

	displayLibraryBooks(books);
	int bookChoice = userSelectMember("Enter the number of the book to check out: ", books.size());

	vector<bool> checkedOutStatuses = books[bookChoice].getCheckedOutStatus();
	for (int i = 0; i < books[bookChoice].getNumCopies(); i++)
	{
		if (!checkedOutStatuses[i])
		{
			copyIndex = i;
			available = true;
			break;
		}
	}

	if (!available)
	{
		cout << "Book not currently available for check out. Please try again later." << endl;
		return;
	}

	displayLibraryMembers(members);
	int memberChoice = userSelectMember("Enter the number of the member checking out the book: ", members.size());

	available = books[bookChoice].checkOut(&members[memberChoice], copyIndex);
	if (!available)
	{
		cout << "Book not currently available for check out. Please try again later." << endl;
	}
}
