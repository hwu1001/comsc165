#ifndef BOOK_H
#define BOOK_H
#include <string>
#include "Person.h"

class Book
{
public:
	Book();
	Book(std::string title, std::string author);
	Book(std::string title, std::string author, bool checkedOut, Person* borrower);
	~Book();
	std::string getTitle();
	std::string getAuthor();
	bool getCheckedOutStatus();
	Person* getBorrower();
	void setTitle(std::string title);
	void setAuthor(std::string author);
	void setCheckedOutStatus(bool checkedOut);
	void setBorrower(Person* borrower);
	bool checkOut(Person* borrower);
	void checkIn();
	Book* testData();

private:
	std::string m_title;
	std::string m_author;
	bool m_checkedOut;
	Person* m_pBorrower;


};

Book::Book()
{
	m_checkedOut = false;
}

Book::Book(std::string title, std::string author)
{
	m_title = title;
	m_author = author;
	m_checkedOut = false;
	m_pBorrower = nullptr;
}

Book::Book(std::string title, std::string author, bool checkedOut, Person* borrower)
{
	m_title = title;
	m_author = author;
	m_checkedOut = checkedOut;
	m_pBorrower = borrower;
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
inline bool Book::getCheckedOutStatus()
{
	return m_checkedOut;
}

inline Person* Book::getBorrower()
{
	return m_pBorrower;
}

inline void Book::setTitle(std::string title)
{
	m_title = title;
}

inline void Book::setAuthor(std::string author)
{
	m_author = author;
}

inline void Book::setCheckedOutStatus(bool checkedOut)
{
	m_checkedOut = checkedOut;
}

inline void Book::setBorrower(Person* borrower)
{
	m_pBorrower = borrower;
}

inline bool Book::checkOut(Person* borrower)
{
	if (m_checkedOut)
	{
		return false;
	}
	else
	{
		m_checkedOut = true;
		m_pBorrower = borrower;
		return true;
	}
}

inline void Book::checkIn()
{
	m_checkedOut = false;
	m_pBorrower = nullptr;
}

Book * Book::testData()
{
	static Book testBooks[] = { 
		Book("To Kill A Mockingbird", "Harper Lee"),
		Book("Nineteen Eighty-Four", "George Orwell"),
		Book("The Great Gatsby", "F. Scott Fitzgerald"),
		Book("The Catcher In the Rye", "J.D. Salinger"),
		Book("Adventures of Huckleberry Finn", "Mark Twain"),
		Book("Brave New World", "Aldous Huxley")};

	return testBooks;
}

#endif // !BOOK_H

