// Henry Wu
// COMSC 165
// Section 3015
// Homework 4

#include <iostream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include <memory>
#include "Person.h"
#include "Publication.h"
#include "Music.h"
#include "Book.h"
#include "Video.h"
#include "Date.h"

using namespace std;

#pragma region functionDeclarations
template <class T>
void initializeTestData(vector<T> &collection, int size);
void getNameAndEmail(string &name, string &email);
int userSelectMember(string prompt, int size);
int getIntInput(string prompt, int max, int min = 1, bool isArray = true);

void editLibraryMember(vector<Person> &members);
void editMemberAttributes(Person &member);
void editPublicationMenu(vector<Book> &books, vector<Music> &music, vector<Video> &videos);
template <class T>
void editPublicationAttributes(T &publication);
void editLibraryBook(vector<Book> &books);
void editBookAttributes(Book &book);
void editLibraryMusic(vector<Music> &music);
void editMusicAttributes(Music &album);
void editLibraryVideo(vector<Video> &videos);
void editVideoAttributes(Video &video);

void displayLibraryMembers(vector<Person> const &members);
void displayLibraryPublications(vector<Book> const &books, vector<Music> const &music, vector<Video> const &videos);
template <class T>
void displayLibraryPublication(T libraryItem);
void displayLibraryBooks(vector<Book> const &books);
void displayLibraryBook(Book book);
void displayLibraryMusicAll(vector<Music> const &music);
void displayLibraryMusic(Music music);
void displayLibraryVideos(vector<Video> const &videos);
void displayLibraryVideo(Video video);
void displayOverduePublications(vector<Book> &books, vector<Music> &music, vector<Video> &videos);

void checkInPublicationMenu(vector<Book> &books, vector<Music> &music, vector<Video> &videos);
template <class T>
void checkInOnePublication(vector<T> &collection);
void checkOutPublicationMenu(vector<Book> &books, vector<Music> &music, vector<Video> &videos, vector<Person> &members);
template <class T>
void checkOutOnePublication(vector<T> &collection, vector<Person> &members);
#pragma endregion

int ID_COUNTER = 5;

#pragma region mainProgram
int main()
{
	int choice;
	// We haven't done anything on polymorphism yet so keep objects in different collections
	// Could use virtual methods and dynamic_cast if we wanted a single collection of different objects though
	vector<Person> libraryMembers;
	initializeTestData<Person>(libraryMembers, 4);
	vector<Book> libraryBooks;
	initializeTestData<Book>(libraryBooks, 6);
	vector<Music> libraryMusic;
	initializeTestData<Music>(libraryMusic, 3);
	vector<Video> libraryVideos;
	initializeTestData<Video>(libraryVideos, 3);

	do
	{
		const int SELECT_MIN = 1, SELECT_MAX = 7;
		choice = 0;
		cout << "Library App Main Menu" << endl;
		cout << "1. Display all current library members" << endl;
		cout << "2. View all publications in the library" << endl;
		cout << "3. Edit data of a current library member" << endl;
		cout << "4. Edit a publication" << endl;
		cout << "5. Check out a publication" << endl;
		cout << "6. Check in a publication" << endl;
		cout << "7. Display all publications with an overdue copy" << endl;
		cout << "What would you like to do? (q to quit) ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			displayLibraryMembers(libraryMembers);
			break;
		case 2:
			displayLibraryPublications(libraryBooks, libraryMusic, libraryVideos);
			break;
		case 3:
			editLibraryMember(libraryMembers);
			break;
		case 4:
			editPublicationMenu(libraryBooks, libraryMusic, libraryVideos);
			break;
		case 5:
			checkOutPublicationMenu(libraryBooks, libraryMusic, libraryVideos, libraryMembers);
			break;
		case 6:
			checkInPublicationMenu(libraryBooks, libraryMusic, libraryVideos);
			break;
		case 7:
			displayOverduePublications(libraryBooks, libraryMusic, libraryVideos);
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
#pragma endregion

#pragma region helperFunctions
template <class T>
///<summary> Initializes test data for library publications. </summary>
///<param name="collection"> Vector of objects that is populated with test data. </param>
///<param name="size"> Number of elements in test data array. </param>
///<returns> Nothing. </returns>
void initializeTestData(vector<T> &collection, int size)
{
	T temp;
	T* tempArr = temp.testData();
	for (int i = 0; i < size; i++)
	{
		collection.push_back(*(tempArr + i));
	}
}

///<summary> Prompts user for string input and returns it. Will re-prompt if the user enters a null string. </summary>
///<param name="prompt"> String to display to the user. </param>
///<returns> The string the user entered. </returns>
string getStringInput(string prompt)
{
	bool done = false;
	string input;

	while (!done)
	{
		cout << prompt;
		getline(cin, input);

		if (input.empty())
		{
			cout << "Invalid input, please re-enter." << endl;
			continue;
		}
		done = true;
	}

	return input;
}

///<summary> Prompts user for integer input. Handles incorrect input for min, max, and other input. </summary>
///<param name="prompt"> String to display to the user about entering the appropriate number. </param>
///<param name="max"> Maximum integer value user should be allowed to enter. </param>
///<param name="min"> Minimum integer value user should be allowed to enter. Default is 1.</param>
///<param name="isArray"> Whether the output is meant for a 0-based array or not. Default is true.</param>
///<returns> An integer the user entered (will be subtracted by one if isArray is true). </returns>
int getIntInput(string prompt, int max, int min, bool isArray)
{
	bool done = false;
	int choice = 0;

	while (!done)
	{
		cout << prompt;
		cin >> choice;

		if (cin.fail() || choice < min || choice > max)
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

	if (isArray)
	{
		return choice - 1;
	}
	else
	{
		return choice;
	}
}
#pragma endregion helperFunctions

#pragma region editFunctions
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
	int choice = getIntInput("Enter the number of the member to edit: ", members.size());

	//edit the attributes of a current member
	editMemberAttributes(members[choice]);
	cout << "Library member edited" << endl;
}

///<summary> Sets the library member's new name and email after prompting for them.</summary>
///<param name="member"> Person object for the member to be edited. </param>
///<returns> Nothing. </returns>
void editMemberAttributes(Person &member)
{
	string name, email;
	cin.ignore();
	name = getStringInput("Please enter the library member's full name: ");
	email = getStringInput("Please enter the library member's email address: ");
	member.setName(name);
	member.setEmail(email);
}

///<summary> Prompts the user for the kind of publication to edit then goes to the specific edit handler to edit a specific publication. </summary>
///<param name="books"> Collection of Book objects. </param>
///<param name="member"> Collection of Music objects. </param>
///<param name="member"> Collection of Video objects. </param>
///<returns> Nothing. </returns>
void editPublicationMenu(vector<Book> &books, vector<Music> &music, vector<Video> &videos)
{
	system("cls");
	cout << "Select publication type to check in" << endl;
	cout << "1. Book" << endl;
	cout << "2. Music" << endl;
	cout << "3. Video" << endl;
	int typeChoice = getIntInput("Enter the number of the type of publication to edit: ", 3, 1, false);
	switch (typeChoice)
	{
	case 1:
		editLibraryBook(books);
		break;
	case 2:
		editLibraryMusic(music);
		break;
	case 3:
		editLibraryVideo(videos);
		break;
	default:
		// Shouldn't ever get here since getIntInput should handle invalid input
		break;
	}
}

template <class T>
///<summary> Generic handler for setting the common member variables of a Publication or Publication derived class. Prompts the user and then sets the variables. </summary>
///<param name="publication"> Object to edit. </param>
///<remarks> T should be a Publication or Publication derived class </remarks>
///<returns> Nothing. </returns>
void editPublicationAttributes(T &publication)
{
	string title = getStringInput("Please enter the publication's title: ");
	string author = getStringInput("Please enter the publication's author: ");
	publication.setTitle(title);
	publication.setAuthor(author);
}

///<summary> Main handler for editing a Book object. </summary>
///<param name="books"> Collection of Book objects. </param>
///<returns> Nothing. </returns>
void editLibraryBook(vector<Book> &books)
{
	system("cls");
	if (books.size() < 1)
	{
		cout << "No current books." << endl;
		return;
	}

	displayLibraryBooks(books);
	int choice = getIntInput("Enter the number of the book to edit: ", books.size());

	cin.ignore();
	editBookAttributes(books[choice]);
	cout << "Library book edited" << endl;
}

///<summary> Prompts user for all relevant member variables and sets them into Book object. </summary>
///<param name="book"> Book object to be edited. </param>
///<returns> Nothing. </returns>
void editBookAttributes(Book &book)
{
	editPublicationAttributes<Book>(book);
	int pages = getIntInput("Please enter the number of pages in the book: ", INT_MAX, 1, false);
	const string* formatStrs = book.getFormatStrings();
	cout << "Please select a format" << endl;
	cout << "1. " << *formatStrs << endl;
	cout << "2. " << *(formatStrs + 1) << endl;
	cout << "3. " << *(formatStrs + 2) << endl;
	int format = getIntInput("Please enter the format number: ", 3, 1, true);
	book.setPages(pages);
	book.setFormat(static_cast<Book::Format>(format));
}

///<summary> Main handler for editing a Music object. </summary>
///<param name="music"> Collection of Music objects. </param>
///<returns> Nothing. </returns>
void editLibraryMusic(vector<Music> &music)
{
	system("cls");
	if (music.size() < 1)
	{
		cout << "No current music." << endl;
		return;
	}

	displayLibraryMusicAll(music);
	int choice = getIntInput("Enter the number of the album to edit: ", music.size());

	cin.ignore();
	editMusicAttributes(music[choice]);
	cout << "Library album edited" << endl;
}

///<summary> Prompts user for all relevant member variables and sets them into Music object. </summary>
///<param name="album"> Single Music object to be edited. </param>
///<returns> Nothing. </returns>
void editMusicAttributes(Music &album)
{
	editPublicationAttributes<Music>(album);
	int duration = getIntInput("Please enter the duration of the album in seconds: ", INT_MAX, 1, false);
	const string* formatStrs = album.getFormatStrings();
	cout << "Please select a format" << endl;
	cout << "1. " << *formatStrs << endl;
	cout << "2. " << *(formatStrs + 1) << endl;
	cout << "3. " << *(formatStrs + 2) << endl;
	int format = getIntInput("Please enter the format number: ", 3, 1, true);
	album.setDuration(duration);
	album.setFormat(static_cast<Music::Format>(format));
}

///<summary> Main handler for editing a Video object. </summary>
///<param name="videos"> Collection of Video objects. </param>
///<returns> Nothing. </returns>
void editLibraryVideo(vector<Video> &videos)
{
	system("cls");
	if (videos.size() < 1)
	{
		cout << "No current videos." << endl;
		return;
	}

	displayLibraryVideos(videos);
	int choice = getIntInput("Enter the number of the video to edit: ", videos.size());

	cin.ignore();
	editVideoAttributes(videos[choice]);
	cout << "Library video edited" << endl;

}

///<summary> Prompts user for all relevant member variables and sets them into Video object. </summary>
///<param name="video"> Single Video object to be edited. </param>
///<returns> Nothing. </returns>
void editVideoAttributes(Video &video)
{
	editPublicationAttributes<Video>(video);
	string producer = getStringInput("Enter the producer of the video: ");
	const string* resStrs = video.getResolutionStrings();
	cout << "Please select a format" << endl;
	cout << "1. " << *resStrs << endl;
	cout << "2. " << *(resStrs + 1) << endl;
	cout << "3. " << *(resStrs + 2) << endl;
	int resolution = getIntInput("Please enter the format number: ", 3, 1, true);
	video.setProducer(producer);
	video.setResolution(static_cast<Video::Resolution>(resolution));
}
#pragma endregion editFunctions

#pragma region displayFunctions
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

///<summary> Displays all library Publications to the prompt.</summary>
///<param name="Publications"> Vector of library Publications. </param>
///<returns> Nothing. </returns>
void displayLibraryPublications(vector<Book> const &books, vector<Music> const &music, vector<Video> const &videos)
{
	// Display all current members
	system("cls");

	if (books.size() < 1 && music.size() < 1 && videos.size() < 1)
	{
		cout << "No library Publications listed." << endl;
		return;
	}

	cout << "Current Library Publications" << endl;
	displayLibraryBooks(books);
	displayLibraryMusicAll(music);
	displayLibraryVideos(videos);
	
}

template <class T>
///<summary> Displays a single library Publication or derived class to the prompt including the title, author, and copies/statuses.</summary>
///<param name="libraryItem"> A Publication or derived object. </param>
///<returns> Nothing. </returns>
void displayLibraryPublication(T libraryItem)
{
	vector<Person*> borrowers = libraryItem.getBorrowers();
	vector<bool> checkedOutStatuses = libraryItem.getCheckedOutStatuses();
	vector<Date> checkOutDates = libraryItem.getCheckOutDates();
	cout << "Title: " << libraryItem.getTitle() << endl;
	cout << "Author: " << libraryItem.getAuthor() << endl;
	cout << "Copies:" << endl;
	cout << "   " << setw(14) << left << "Checked Out?" << setw(16) << "Check Out Date" << setw(10) << left << "Overdue?" << setw(10) << "Borrower" << endl;
	cout << "   " << setw(14) << left << "============" << setw(16) << "==============" << setw(10) << left << "========" << setw(10) << "========" << endl;
	for (int i = 0; i < libraryItem.getNumCopies(); i++)
	{
		string checkedOut;
		string borrowerName;
		string dateString;
		string overdue;

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
			borrowerName = "-";
		}

		if (!checkOutDates[i].isNullDate())
		{
			dateString = checkOutDates[i].toString();
			if (libraryItem.isCopyOverdue(i))
			{
				overdue = "Yes";
			}
			else
			{
				overdue = "No";
			}
		}
		else
		{
			dateString = "-";
			overdue = "-";
		}
		cout << i + 1 << ". " << setw(14) << left << checkedOut << setw(16) << dateString << setw(10) << overdue << setw(borrowerName.length()) << left << borrowerName << endl;
	}

}

///<summary> Displays all library books to the prompt.</summary>
///<param name="books"> Vector of library Book objects. </param>
///<returns> Nothing. </returns>
void displayLibraryBooks(vector<Book> const &books)
{
	int count = 1;
	cout << "  ____              _        " << endl;
	cout << " |  _ \\            | |       " << endl;
	cout << " | |_) | ___   ___ | | _____ " << endl;
	cout << " |  _ < / _ \\ / _ \\| |/ / __|" << endl;
	cout << " | |_) | (_) | (_) |   <\\__ \\" << endl;
	cout << " |____/ \\___/ \\___/|_|\\_\\___/" << endl;
	cout << endl;
	for (Book book : books)
	{
		cout << "#" << count << endl;
		displayLibraryBook(book);
		count++;
	}
}

///<summary> Displays a single library book including the number of pages and format of the book.</summary>
///<param name="book"> A Book object used to display data. </param>
///<returns> Nothing. </returns>
void displayLibraryBook(Book book)
{
	displayLibraryPublication<Book>(book);
	const string* formatArr = book.getFormatStrings();
	cout << "Pages: " << book.getPages() << endl;
	cout << "Format: " << *(formatArr + static_cast<int>(book.getFormat())) << endl;
	cout << endl;
	
}

///<summary> Displays all library music to the prompt.</summary>
///<param name="music"> Vector of library Music objects. </param>
///<returns> Nothing. </returns>
void displayLibraryMusicAll(vector<Music> const &music)
{
	int count = 1;
	cout << "  __  __           _      " << endl;
	cout << " |  \\/  |         (_)     " << endl;
	cout << " | \\  / |_   _ ___ _  ___ " << endl;
	cout << " | |\\/| | | | / __| |/ __|" << endl;
	cout << " | |  | | |_| \\__ \\ | (__ " << endl;
	cout << " |_|  |_|\\__,_|___/_|\\___|" << endl;
	cout << endl;
	for (Music album : music)
	{

		cout << "#" << count << endl;
		displayLibraryMusic(album);
		count++;
	}
}

///<summary> Displays a single library album (Music object) including the duration in seconds and format of the recording.</summary>
///<param name="music"> A Music object used to display data. </param>
///<returns> Nothing. </returns>
void displayLibraryMusic(Music music)
{
	displayLibraryPublication<Music>(music);
	const string* formatArr = music.getFormatStrings();
	cout << "Duration: " << music.getDuration() << " seconds" << endl;
	cout << "Format: " << *(formatArr + static_cast<int>(music.getFormat())) << endl;
	cout << endl;
}

///<summary> Displays all library videos to the prompt.</summary>
///<param name="videos"> Vector of library Video objects. </param>
///<returns> Nothing. </returns>
void displayLibraryVideos(vector<Video> const &videos)
{
	int count = 1;
	cout << " __      ___     _                " << endl;
	cout << " \\ \\    / (_)   | |               " << endl;
	cout << "  \\ \\  / / _  __| | ___  ___  ___ " << endl;
	cout << "   \\ \\/ / | |/ _` |/ _ \\/ _ \\/ __|" << endl;
	cout << "    \\  /  | | (_| |  __/ (_) \\__ \\" << endl;
	cout << "     \\/   |_|\\__,_|\\___|\\___/|___/" << endl;
	cout << endl;
	for (Video video : videos)
	{

		cout << "#" << count << endl;
		displayLibraryVideo(video);
		count++;
	}
}

///<summary> Displays a single library video including the producer and resolution of the video.</summary>
///<param name="video"> A Video object used to display data. </param>
///<returns> Nothing. </returns>
void displayLibraryVideo(Video video)
{
	displayLibraryPublication<Video>(video);
	const string* resolutionArr = video.getResolutionStrings();
	cout << "Producer: " << video.getProducer() << endl;
	cout << "Resolution: " << *(resolutionArr + static_cast<int>(video.getResolution())) << endl;
	cout << endl;
}

///<summary> Displays all publications that have at least one copy that is overdue.</summary>
///<param name="books"> Vector of library Book objects. </param>
///<param name="music"> Vector of library Music objects. </param>
///<param name="videos"> Vector of library Video objects. </param>
///<returns> Nothing. </returns>
void displayOverduePublications(vector<Book> &books, vector<Music> &music, vector<Video> &videos)
{
	system("cls");

	if (books.size() < 1 && music.size() < 1 && videos.size() < 1)
	{
		cout << "No library Publications listed." << endl;
		return;
	}
	cout << "Overdue Publications" << endl;
	int count = 1;
	bool overdue = false;

	for (int i = 0; i < books.size(); i++)
	{
		for (int j = 0; j < books[i].getNumCopies(); j++)
		{
			if (books[i].isCopyOverdue(j))
			{
				overdue = true;
				cout << "#" << count << endl;
				displayLibraryBook(books[i]);
				count++;
				break;
			}
		}
	}

	for (int i = 0; i < music.size(); i++)
	{
		for (int j = 0; j < music[i].getNumCopies(); j++)
		{
			if (music[i].isCopyOverdue(j))
			{
				overdue = true;
				cout << "#" << count << endl;
				displayLibraryMusic(music[i]);
				count++;
				break;
			}
		}
	}

	for (int i = 0; i < videos.size(); i++)
	{
		for (int j = 0; j < videos[i].getNumCopies(); j++)
		{
			if (videos[i].isCopyOverdue(j))
			{
				overdue = true;
				cout << "#" << count << endl;
				displayLibraryVideo(videos[i]);
				count++;
				break;
			}
		}
	}

	if (!overdue)
	{
		cout << "No overdue publications currently." << endl;
	}
}
#pragma endregion displayFunctions

#pragma region checkInAndOut
///<summary> Prompts a user for the type of library item to check in. </summary>
///<param name="books"> Vector of Book objects. </param>
///<param name="music"> Vector of Music objects. </param>
///<param name="videos"> Vector of Video objects. </param>
///<returns> Nothing. </returns>
void checkInPublicationMenu(vector<Book> &books, vector<Music> &music, vector<Video> &videos)
{
	system("cls");
	cout << "Select publication type to check in" << endl;
	cout << "1. Book" << endl;
	cout << "2. Music" << endl;
	cout << "3. Video" << endl;
	int typeChoice = getIntInput("Enter the number of the type of publication to check in: ", 3);
	switch (typeChoice)
	{
		// The case numbers are 1 less than the menu above because of how getIntInput is designed for array selection
	case 0:
		displayLibraryBooks(books);
		checkInOnePublication<Book>(books);
		break;
	case 1:
		displayLibraryMusicAll(music);
		checkInOnePublication<Music>(music);
		break;
	case 2:
		displayLibraryVideos(videos);
		checkInOnePublication<Video>(videos);
		break;
	default:
		// Shouldn't ever get here since getIntInput should handle invalid input
		break;
	}
}

template <class T>
///<summary> Prompts a user for a library item and copy of that item to check in.</summary>
///<param name="collection"> Vector of objects to use to find one to check in. </param>
///<returns> Nothing. </returns>
void checkInOnePublication(vector<T> &collection)
{
	int choice = getIntInput("Enter the number of the publication to check in: ", collection.size());
	int copyIndex = getIntInput("Enter the copy number to check in: ", collection[choice].getNumCopies());

	if (collection[choice].checkIn(copyIndex))
	{
		cout << "Publication checked in" << endl;
	}
	else
	{
		cout << "Publication was not able to be checked in" << endl;
	}
}

///<summary> Prompts a user for the type of library item to check out. </summary>
///<param name="books"> Vector of Book objects. </param>
///<param name="music"> Vector of Music objects. </param>
///<param name="videos"> Vector of Video objects. </param>
///<param name="members"> Vector of library members. </param>
///<returns> Nothing. </returns>
void checkOutPublicationMenu(vector<Book> &books, vector<Music> &music, vector<Video> &videos, vector<Person> &members)
{
	system("cls");
	cout << "Select publication type to check out" << endl;
	cout << "1. Book" << endl;
	cout << "2. Music" << endl;
	cout << "3. Video" << endl;
	int typeChoice = getIntInput("Enter the number of the type of publication to check out: ", 3);

	switch (typeChoice)
	{
	case 0:
		displayLibraryBooks(books);
		checkOutOnePublication<Book>(books, members);
		break;
	case 1:
		displayLibraryMusicAll(music);
		checkOutOnePublication<Music>(music, members);
		break;
	case 2:
		displayLibraryVideos(videos);
		checkOutOnePublication<Video>(videos, members);
		break;
	default:
		// We should never get here since getIntInput should handle invalid input
		cout << "Invalid choice." << endl;
		break;
	}
}

template <class T>
///<summary> Prompts a user for the library item to check out. </summary>
///<param name="collection"> Vector of library related objects for check out. </param>
///<param name="members"> Vector of library members. </param>
///<returns> Nothing. </returns>
void checkOutOnePublication(vector<T> &collection, vector<Person> &members)
{
	bool available = false;
	int copyIndex = 0;
	int publicationChoice = getIntInput("Enter the number of the publication to check out: ", collection.size());
	vector<bool> checkedOutStatuses = collection[publicationChoice].getCheckedOutStatuses();
	int numCopies = collection[publicationChoice].getNumCopies();

	for (int i = 0; i < numCopies; i++)
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
		cout << "Publication not currently available for check out. Please try again later." << endl;
		return;
	}

	displayLibraryMembers(members);
	int leapDay;
	int memberChoice = getIntInput("Enter the number of the member checking out the publication: ", members.size());
	int year = getIntInput("Enter the year of publication check out: ", INT_MAX, 0, false);
	int month = getIntInput("Enter the numeric month of publication check out (1 - 12): ", 12, 1, false);

	if (Date::isLeapYear(year))
	{
		leapDay = 1;
	}
	else
	{
		leapDay = 0;
	}

	const int* monthDays = Date::getMonthDays();
	int day = getIntInput("Enter the day of of publication check out: ", *(monthDays + month - 1) + leapDay, 1, false);

	available = collection[publicationChoice].checkOut(&members[memberChoice], copyIndex, Date(month, day, year));
	if (!available)
	{
		cout << "Publication not currently available for check out. Please try again later." << endl;
	}
}
#pragma endregion checkInAndOut
