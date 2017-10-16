#ifndef PUBLICATION_H
#define PUBLICATION_H
#include <string>
#include <vector>
#include <ctime>
#include "Person.h"
#include "Date.h"

///<summary> Publication class used to create items in a library. Parent class of Book, Video, and Music. </summary>
class Publication
{
public:
	Publication();
	Publication(std::string title, std::string author, int copies);
	~Publication();
	std::string getTitle();
	std::string getAuthor();
	std::vector<bool> getCheckedOutStatuses();
	std::vector<Person*> getBorrowers();
	std::vector<Date> getCheckOutDates();
	int getNumCopies();
	void setTitle(std::string title);
	void setAuthor(std::string author);
	bool setCheckedOutStatus(bool checkedOut, int copyIndex);
	bool setBorrower(Person* borrower, int copyIndex);
	bool setCheckOutDate(Date checkOutDate, int copyIndex);
	void setNumCopies();
	bool checkOut(Person* borrower, int copyIndex, Date checkOutDate);
	bool checkIn(int copyIndex);
	bool isCopyOverdue(int copyIndex);
	Publication* testData();

private:
	std::string m_title;
	std::string m_author;
	std::vector<bool> m_checkedOut;
	std::vector<Person*> m_pBorrower;
	std::vector<Date> m_checkOutDates;
	int m_numCopies;

};

///<summary> Default constructor for Publication class. For basic instantiation, no actions taken. </summary>
///<returns> Nothing. </returns>
Publication::Publication()
{
}

///<summary> Constructor for Publication object that sets all available variables of class. </summary>
///<param name="title"> Title of the publication. </param>
///<param name="author"> Author of the publication. </param>
///<param name="copies"> Number of copies available of the publication. </param>
///<returns> Nothing. </returns>
Publication::Publication(std::string title, std::string author, int copies)
{
	m_title = title;
	m_author = author;
	m_numCopies = copies;

	for (int i = 0; i < copies; i++)
	{
		Date temp = Date();
		m_checkedOut.push_back(false);
		m_pBorrower.push_back(nullptr);
		m_checkOutDates.push_back(temp);
	}
}

///<summary> Default destructor for Publication class. No special actions taken. </summary>
///<returns> Nothing. </returns>
Publication::~Publication()
{
}

///<summary> Getter method for the title of the publication. </summary>
///<returns> The title of the publication. </returns>
inline std::string Publication::getTitle()
{
	return m_title;
}

///<summary> Getter method for the author of the publication. </summary>
///<returns> The author of the publication. </returns>
inline std::string Publication::getAuthor()
{
	return m_author;
}

///<summary> Getter method for the checked out statuses of the copies of each publication. </summary>
///<returns> A vector of the checked out statuses. </returns>
inline std::vector<bool> Publication::getCheckedOutStatuses()
{
	return m_checkedOut;
}

///<summary> Getter method for the borrowers of each publication copy. </summary>
///<returns> A vector of the borrowers. </returns>
inline std::vector<Person*> Publication::getBorrowers()
{
	return m_pBorrower;
}

///<summary> Getter method for the check out dates of each publication copy. </summary>
///<returns> A vector of the check out dates. </returns>
inline std::vector<Date> Publication::getCheckOutDates()
{
	return m_checkOutDates;
}

///<summary> Getter method for the number of copies of the publication. </summary>
///<returns> The number of copies of the publication. </returns>
inline int Publication::getNumCopies()
{
	return m_numCopies;
}

///<summary> Getter method for the title of the publication. </summary>
///<param name="title"> Title of the publication. </param>
///<returns> The title of the publication. </returns>
inline void Publication::setTitle(std::string title)
{
	m_title = title;
}

///<summary> Getter method for the author of the publication. </summary>
///<param name="author"> Author of the publication. </param>
///<returns> The author of the publication. </returns>
inline void Publication::setAuthor(std::string author)
{
	m_author = author;
}

///<summary> Setter method for the checked out status of the publication copy. </summary>
///<param name="checkedOut"> The status of the publication. True to say the publication is checked out, otherwise false. </param>
///<param name="copyIndex"> The index in the copy vector to denote which copy is being set. </param>
///<returns> True if checked out status is set, otherwise false. </returns>
inline bool Publication::setCheckedOutStatus(bool checkedOut, int copyIndex)
{
	if (copyIndex < m_checkedOut.size() && copyIndex > 0)
	{
		m_checkedOut[copyIndex] = checkedOut;
		return true;
	}
	else
	{
		return false;
	}
}

///<summary> Setter method for the borrower of the publication copy. </summary>
///<param name="borrower"> The pointer to a Person class representing the borrower of the publication. </param>
///<param name="copyIndex"> The index in the copy vector to denote which copy is being set. </param>
///<returns> True if borrower is set, otherwise false. </returns>
inline bool Publication::setBorrower(Person* borrower, int copyIndex)
{
	if (copyIndex < m_pBorrower.size() && copyIndex >= 0)
	{
		m_pBorrower[copyIndex] = borrower;
		return true;
	}
	else
	{
		return false;
	}
}

///<summary> Setter method for the check out date of the publication copy. </summary>
///<param name="checkOutDate"> The check out date of a particular publication copy. </param>
///<param name="copyIndex"> The index in the copy vector to denote which copy is being set. </param>
///<returns> True if check out date is set, otherwise false. </returns>
bool Publication::setCheckOutDate(Date checkOutDate, int copyIndex)
{
	if (copyIndex < m_checkOutDates.size() && copyIndex >= 0)
	{
		m_checkOutDates[copyIndex] = checkOutDate;
		return true;
	}
	else
	{
		return false;
	}
}

///<summary> Setter method for the number of copies of the publication. Note that the only real way to set copies is in the constructor of the Publication class. 
///This method sets the number of copies to the size of the checked out vector so that copies and vector size stays in sync.</summary>
///<returns> Nothing. </returns>
inline void Publication::setNumCopies()
{
	m_numCopies = m_checkedOut.size();
}

///<summary> Method used to check out a single publication copy. </summary>
///<param name="borrower"> The pointer to a Person class representing the borrower of the publication. </param>
///<param name="copyIndex"> The index in the copy vector to denote which copy is being checked out. </param>
///<param name="checkOutDate"> Date class representing the check out date. </param>
///<returns> True if publication copy is available for check out, otherwise false. </returns>
inline bool Publication::checkOut(Person* borrower, int copyIndex, Date checkOutDate)
{
	if (m_checkedOut[copyIndex])
	{
		return false;
	}
	else
	{
		m_checkedOut[copyIndex] = true;
		m_pBorrower[copyIndex] = borrower;
		m_checkOutDates[copyIndex] = checkOutDate;
		return true;
	}
}

///<summary> Method used to check in a single publication copy. </summary>
///<param name="copyIndex"> The index in the copy vector to denote which copy is being checked in. </param>
///<returns> True if publication copy is checked in successfully, otherwise false. </returns>
inline bool Publication::checkIn(int copyIndex)
{
	if (copyIndex < m_checkedOut.size() && copyIndex >= 0)
	{
		m_checkedOut[copyIndex] = false;
		m_pBorrower[copyIndex] = nullptr;
		m_checkOutDates[copyIndex] = Date();
		return true;
	}
	else
	{
		return false;
	}
}

///<summary> 
///Method used to check whether a publication is overdue at the library or not. Assumes validation of dates has already occurred so that check out dates are 
///not in the future. Publications checked out for longer than 21 days are considered overdue. If the copyIndex is invalid, the method returns false. 
///</summary>
///<param name="copyIndex"> The index in the copy vector check if it is overdue or not. If the copyIndex is invalid, the method returns false. </param>
///<returns> True if publication copy is overdue, otherwise false. </returns>
inline bool Publication::isCopyOverdue(int copyIndex)
{
	int diff = 0;

	if (copyIndex < m_checkOutDates.size() && copyIndex >= 0)
	{
		if (m_checkOutDates[copyIndex].isNullDate())
		{
			diff = 0;
		}
		else
		{
			Date today = m_checkOutDates[copyIndex].getCurrentDate();
			diff = today - m_checkOutDates[copyIndex];
		}
	}
	
	if (diff > 21)
	{
		return true;
	}
	else
	{
		return false;
	}
}

///<summary> Method used to help create a test library to see that the Publication class works appropriately. </summary>
///<returns> Pointer to array holding Video objects with pre-populated data. </returns>
Publication * Publication::testData()
{
	static Publication testPublications[] = {
		Publication("To Kill A Mockingbird", "Harper Lee", 1),
		Publication("Nineteen Eighty-Four", "George Orwell", 3),
		Publication("The Great Gatsby", "F. Scott Fitzgerald", 2),
		Publication("The Catcher In the Rye", "J.D. Salinger", 1),
		Publication("Adventures of Huckleberry Finn", "Mark Twain", 5),
		Publication("Brave New World", "Aldous Huxley", 3) };
	return testPublications;
}

#endif // !PUBLICATION_H

