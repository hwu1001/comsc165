#include <iostream>
#include <iomanip>
#include "Publication.h"
#include "Book.h"
#include "Video.h"
#include "Music.h"

using namespace std;

int main()
{
	Publication* pubPointers[6] = {
	new Book("War and Peace", 908),
	new Book("Harry Potter", 324),
	new Video("Dunkirk", "HD"),
	new Video("Toy Story", "Lo"),
	new Music("Someone Like You", Music::Format::MP3),
	new Music("Happy", Music::Format::WAV)};

	/*std::cout << std::left << std::setw(10) << "Type" << std::setw(20) << "Title" << "Other" << '\n';
	std::cout << std::left << std::setw(10) << "----" << std::setw(20) << "-----" << "-----" << '\n';*/
	std::cout << std::left << std::setw(10) << "Type" << std::setw(20) << "Title" << setw(8) << "Pages" << setw(11) << "Resolution" << "Format" << '\n';
	std::cout << std::left << std::setw(10) << "----" << std::setw(20) << "-----" << setw(8) << "-----" << setw(11) << "----------" << "------" << '\n';
	for (int i = 0; i < 6; i++)
	{
		// Apparently this is the polymorphic way
		pubPointers[i]->showData();
	}

	/*Book* bookPtr;
	Video* videoPtr;
	Music* musicPtr;
	std::cout << std::left << std::setw(10) << "Type" << std::setw(20) << "Title" << setw(8) << "Pages" << setw(11) << "Resolution" << "Format" << '\n';
	std::cout << std::left << std::setw(10) << "----" << std::setw(20) << "-----" << setw(8) << "-----" << setw(11) << "----------" << "------" << '\n';
	for (int i = 0; i < 6; i++)
	{
		if ((bookPtr = dynamic_cast<Book*>(pubPointers[i])))
		{
			std::cout << std::left << std::setw(10) << "Book" << std::setw(20) << pubPointers[i]->getTitle() << setw(8) << static_cast<Book*>(pubPointers[i])->getPages() << setw(11) << "-" << "-" << '\n';
		}
		else if (videoPtr = dynamic_cast<Video*>(pubPointers[i]))
		{
			string resolution = static_cast<Video*>(pubPointers[i])->getResolution();
			std::cout << std::left << std::setw(10) << "Video" << std::setw(20) << pubPointers[i]->getTitle() << setw(8) << "-" << setw(11) << resolution << "-" << '\n';
		}
		else if (musicPtr = dynamic_cast<Music*>(pubPointers[i]))
		{
			string* formatStrs = static_cast<Music*>(pubPointers[i])->getFormatStrings();
			Music::Format format = static_cast<Music*>(pubPointers[i])->getFormat();			
			std::cout << std::left << std::setw(10) << "Music" << std::setw(20) << pubPointers[i]->getTitle() << setw(8) << "-" << setw(11) << "-" << *(formatStrs + static_cast<int>(format)) << '\n';
		}
	}*/
	return 0;
}
