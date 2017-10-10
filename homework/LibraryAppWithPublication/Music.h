#ifndef MUSIC_H
#define MUSIC_H
#include "Publication.h"

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
	Music(std::string title, std::string author, int copies, int duration, Format format) : Publication(title, author, copies) 
	{
		m_duration = duration;
		m_format = format;
	};
	~Music();
	int getDuration();
	Music::Format getFormat();
	void setDuration(int duration);
	void setFormat(Music::Format format);
	Music* testData();

private:
	int m_duration;
	Format m_format;
	static const std::string m_formatStrings[];

};

Music::Music()
{
}

Music::~Music()
{
}

inline int Music::getDuration()
{
	return m_duration;
}

inline Music::Format Music::getFormat()
{
	return m_format;
}

inline void Music::setDuration(int duration)
{
	m_duration = duration;
}

inline void Music::setFormat(Music::Format format)
{
	m_format = format;
}

Music* Music::testData()
{
	static Music testMusic[] =
	{
		Music("Help!", "The Beatles", 3, 2060, Music::Format::MP3),
		Music("Let It Bleed", "The Rolling Stones", 2, 2541, Music::Format::AAV),
		Music("Green River", "Creedence Clearwater Revival", 3, 1765, Music::Format::WAV)
	};
	return testMusic;
}

const std::string Music::m_formatStrings[] = { "MP3", "AAV", "WAV" };
#endif // !MUSIC_H