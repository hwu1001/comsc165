#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <vector>
#include "Person.h"

class Book
{
public:
	Book();
	Book(std::string title, std::string author, int copies);
	~Book();
	std::string getTitle();
	std::string getAuthor();
	std::vector<bool> getCheckedOutStatus();
	std::vector<Person*> getBorrower();
	int getNumCopies();
	void setTitle(std::string title);
	void setAuthor(std::string author);
	bool setCheckedOutStatus(bool checkedOut, int copyIndex);
	bool setBorrower(Person* borrower, int copyIndex);
	void setNumCopies();
	bool checkOut(Person* borrower, int copyIndex);
	bool checkIn(int copyIndex);
	Book* testData();

private:
	std::string m_title;
	std::string m_author;
	std::vector<bool> m_checkedOut;
	std::vector<Person*> m_pBorrower;
	int m_numCopies;

};

Book::Book()
{
}

Book::Book(std::string title, std::string author, int copies)
{
	m_title = title;
	m_author = author;
	m_numCopies = copies;

	for (int i = 0; i < copies; i++)
	{
		m_checkedOut.push_back(false);
		m_pBorrower.push_back(nullptr);
	}
}

Book::~Book()
{
}

inline std::string Book::getTitle()
{
	return m_title;
}

inline std::string Book::getAuthor()
{
	return m_author;
}
inline std::vector<bool> Book::getCheckedOutStatus()
{
	return m_checkedOut;
}

inline std::vector<Person*> Book::getBorrower()
{
	return m_pBorrower;
}

inline int Book::getNumCopies()
{
	return m_numCopies;
}

inline void Book::setTitle(std::string title)
{
	m_title = title;
}

inline void Book::setAuthor(std::string author)
{
	m_author = author;
}

inline bool Book::setCheckedOutStatus(bool checkedOut, int copyIndex)
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

inline bool Book::setBorrower(Person* borrower, int copyIndex)
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

inline void Book::setNumCopies()
{
	m_numCopies = m_checkedOut.size();
}

inline bool Book::checkOut(Person* borrower, int copyIndex)
{
	if (m_checkedOut[copyIndex])
	{
		return false;
	}
	else
	{
		m_checkedOut[copyIndex] = true;
		m_pBorrower[copyIndex] = borrower;
		return true;
	}
}

inline bool Book::checkIn(int copyIndex)
{
	if (copyIndex < m_checkedOut.size() && copyIndex >= 0)
	{
		m_checkedOut[copyIndex] = false;
		m_pBorrower[copyIndex] = nullptr;
		return true;
	}
	else
	{
		return false;
	}
}

Book * Book::testData()
{
	static Book testBooks[] = {
		Book("To Kill A Mockingbird", "Harper Lee", 1),
		Book("Nineteen Eighty-Four", "George Orwell", 3),
		Book("The Great Gatsby", "F. Scott Fitzgerald", 2),
		Book("The Catcher In the Rye", "J.D. Salinger", 1),
		Book("Adventures of Huckleberry Finn", "Mark Twain", 5),
		Book("Brave New World", "Aldous Huxley", 3) };

	return testBooks;
}

#endif // !BOOK_H

