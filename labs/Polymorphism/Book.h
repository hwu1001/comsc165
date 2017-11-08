#ifndef BOOK_H
#define BOOK_H
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <string>

class Book : public Publication
{
public:
	Book();
	Book(std::string title, int pages);
	~Book();
	int getPages();
	virtual void showData();

private:
	int m_pages;

};

Book::Book()
{
}

Book::Book(std::string title, int pages)
{
	m_title = title;
	m_pages = pages;
}

Book::~Book()
{
}

int Book::getPages()
{
	return m_pages;
}
inline void Book::showData()
{
	//int len = this->m_title.length();
	//std::cout << std::left << std::setw(10) << "Book" << std::setw(20) << this->m_title << m_pages << '\n';
	std::cout << std::left << std::setw(10) << "Book" << std::setw(20) << m_title << std::setw(8) << m_pages << std::setw(11) << "-" << "-" << '\n';
}
#endif // !BOOK_H

