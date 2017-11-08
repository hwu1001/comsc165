#ifndef MUSIC_H
#define MUSIC_H
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <string>

class Music : public Publication
{
public:
	enum class Format
	{
		MP3,
		AAV,
		WAV
	};
	Music();
	Music(std::string title, Music::Format format);
	~Music();
	Music::Format getFormat();
	std::string* getFormatStrings();
	virtual void showData();

private:
	Music::Format m_format;
	static std::string m_formatStrings[];

};

Music::Music()
{
}

inline Music::Music(std::string title, Music::Format format)
{
	m_title = title;
	m_format = format;
}

Music::~Music()
{
}

inline Music::Format Music::getFormat()
{
	return m_format;
}

inline void Music::showData()
{
	//int len = this->m_title.length();
	//std::cout << std::left << std::setw(10) << "Music" << std::setw(20) << this->m_title << m_formatStrings[static_cast<int>(m_format)] << '\n';
	std::cout << std::left << std::setw(10) << "Music" << std::setw(20) << m_title << std::setw(8) << "-" << std::setw(11) << "-" << m_formatStrings[static_cast<int>(m_format)] << '\n';
}

std::string* Music::getFormatStrings()
{
	return m_formatStrings;
}

std::string Music::m_formatStrings[] = { "MP3", "AAV", "WAV" };
#endif // !MUSIC_H

