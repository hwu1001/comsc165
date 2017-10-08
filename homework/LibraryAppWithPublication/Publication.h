#ifndef PUBLICATION_H
#define PUBLICATION_H
#include <string>
#include <vector>
#include "Person.h"

class Publication
{
public:
	Publication();
	Publication(std::string title, std::string author, int copies);
	~Publication();
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
	Publication* testData();

private:
	std::string m_title;
	std::string m_author;
	std::vector<bool> m_checkedOut;
	std::vector<Person*> m_pBorrower;
	int m_numCopies;

};

Publication::Publication()
{
}

Publication::Publication(std::string title, std::string author, int copies)
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

Publication::~Publication()
{
}

inline std::string Publication::getTitle()
{
	return m_title;
}

inline std::string Publication::getAuthor()
{
	return m_author;
}
inline std::vector<bool> Publication::getCheckedOutStatus()
{
	return m_checkedOut;
}

inline std::vector<Person*> Publication::getBorrower()
{
	return m_pBorrower;
}

inline int Publication::getNumCopies()
{
	return m_numCopies;
}

inline void Publication::setTitle(std::string title)
{
	m_title = title;
}

inline void Publication::setAuthor(std::string author)
{
	m_author = author;
}

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

inline void Publication::setNumCopies()
{
	m_numCopies = m_checkedOut.size();
}

inline bool Publication::checkOut(Person* borrower, int copyIndex)
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

inline bool Publication::checkIn(int copyIndex)
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

