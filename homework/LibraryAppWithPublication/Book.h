#ifndef BOOK_H
#define BOOK_H
#include "Publication.h"

///<summary> Book class used to create books in a library. A derived class of Publication. </summary>
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
	Book(std::string title, std::string author, int copies, int pages, Format format);
	~Book();
	int getPages();
	Book::Format getFormat();
	const std::string* getFormatStrings();
	void setPages(int pages);
	void setFormat(Book::Format format);
	Book* testData();
	

private:
	int m_pages;
	Format m_format;
	static const std::string m_formatStrings[];


};

///<summary> Default constructor for Book class. For basic instantiation, no actions taken. </summary>
///<returns> Nothing. </returns>
Book::Book()
{
}

///<summary> Constructor for Book object that sets all available variables of class. Uses Publication constructor within it. </summary>
///<param name="title"> Title of the book. </param>
///<param name="author"> Author of the book. </param>
///<param name="copies"> Number of copies available for the book. </param>
///<param name="pages"> Number of pages in the book. </param>
///<param name="format"> Format of the book. See Book::Format enum for possible options. </param>
///<returns> Nothing. </returns>
Book::Book(std::string title, std::string author, int copies, int pages, Format format) : Publication(title, author, copies)
{
	m_pages = pages;
	m_format = format;
}

///<summary> Default destructor for Book class. No special actions taken. </summary>
///<returns> Nothing. </returns>
Book::~Book()
{
}

///<summary> Getter method for variable holding number of pages in the book. </summary>
///<returns> The number of pages in the book. </returns>
inline int Book::getPages()
{
	return m_pages;
}

///<summary> Getter method for variable holding the format of the book. </summary>
///<returns> The format of the book. </returns>
inline Book::Format Book::getFormat()
{
	return m_format;
}

///<summary> Getter method for the strings associated with the Book::Format enum. </summary>
///<returns> A pointer to the array holding the strings associated with Book::Format enum. </returns>
inline const std::string* Book::getFormatStrings()
{
	return Book::m_formatStrings;
}

///<summary> Setter method for the number of pages in the book. </summary>
///<param name="pages"> Number of pages in the book. </param>
///<returns> Nothing. </returns>
inline void Book::setPages(int pages)
{
	m_pages = pages;
}

///<summary> Setter method for the format of the book. </summary>
///<param name="format"> Format of the book. See Book::Format enum for possible options. </param>
///<returns> Nothing. </returns>
inline void Book::setFormat(Book::Format format)
{
	m_format = format;
}

///<summary> Method used to help create a test library to see that the Book class works appropriately. </summary>
///<returns> Pointer to array holding Book objects with pre-populated data. </returns>
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

const std::string Book::m_formatStrings[] = { "Hardcover", "Softcover", "Digital" };
#endif // !BOOK_H