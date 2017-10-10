#ifndef BOOK_H
#define BOOK_H
#include "Publication.h"

class Book : public Publication
{
public:
	enum class Format
	{
		HARDCOVER,
		SOFTCOVER,
		DIGITAL
	};
	Book();
	Book(std::string title, std::string author, int copies, int pages, Format format) : Publication(title, author, copies)
	{
		m_pages = pages;
		m_format = format;
	};
	~Book();
	int getPages();
	Book::Format getFormat();
	void setPages(int pages);
	void setFormat(Book::Format format);
	Book* testData();

private:
	int m_pages;
	Format m_format;
	static const std::string m_formatStrings[];


};

Book::Book()
{
}

Book::~Book()
{
}

inline int Book::getPages()
{
	return m_pages;
}

inline Book::Format Book::getFormat()
{
	return m_format;
}

inline void Book::setPages(int pages)
{
	m_pages = pages;
}

inline void Book::setFormat(Book::Format format)
{
	m_format = format;
}

Book* Book::testData()
{
	static Book testBooks[] = 
	{
		Book("To Kill A Mockingbird", "Harper Lee", 1, 281, Book::Format::SOFTCOVER),
		Book("Nineteen Eighty-Four", "George Orwell", 3, 328, Book::Format::SOFTCOVER),
		Book("The Great Gatsby", "F. Scott Fitzgerald", 2, 180, Book::Format::DIGITAL),
		Book("The Catcher In the Rye", "J.D. Salinger", 1, 214, Book::Format::HARDCOVER),
		Book("Adventures of Huckleberry Finn", "Mark Twain", 5, 366, Book::Format::SOFTCOVER),
		Book("Brave New World", "Aldous Huxley", 3, 311, Book::Format::DIGITAL)
	};

	return testBooks;

}

const std::string Book::m_formatStrings[] = { "hardcover", "softcover", "digital" };
#endif // !BOOK_H