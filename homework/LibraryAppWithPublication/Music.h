#ifndef MUSIC_H
#define MUSIC_H
#include "Publication.h"

///<summary> Music class used to create albums in a library. A derived class of Publication. </summary>
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
	Music(std::string title, std::string author, int copies, int duration, Format format);
	~Music();
	int getDuration();
	Music::Format getFormat();
	const std::string* getFormatStrings();
	void setDuration(int duration);
	void setFormat(Music::Format format);
	Music* testData();

private:
	int m_duration;
	Format m_format;
	static const std::string m_formatStrings[];

};

///<summary> Default constructor for Music class. For basic instantiation, no actions taken. </summary>
///<returns> Nothing. </returns>
Music::Music()
{
}

///<summary> Constructor for Music object that sets all available variables of class. Uses Publication constructor within it. </summary>
///<param name="title"> Title of the album. </param>
///<param name="author"> Author of the album. Usually the band name. </param>
///<param name="copies"> Number of copies available of the album. </param>
///<param name="duration"> Duration (in seconds) of the album. </param>
///<param name="format"> Format of the album. See Music::Format enum for possible options. </param>
///<returns> Nothing. </returns>
Music::Music(std::string title, std::string author, int copies, int duration, Format format) : Publication(title, author, copies)
{
	m_duration = duration;
	m_format = format;
}

///<summary> Default destructor for Music class. No special actions taken. </summary>
///<returns> Nothing. </returns>
Music::~Music()
{
}

///<summary> Getter method for duration of the album. </summary>
///<returns> The duration (in seconds) of the album. </returns>
inline int Music::getDuration()
{
	return m_duration;
}

///<summary> Getter method for the format of the album. </summary>
///<returns> The format of the album. </returns>
inline Music::Format Music::getFormat()
{
	return m_format;
}

///<summary> Getter method for the strings associated with the Music::Format enum. </summary>
///<returns> A pointer to the array holding the strings associated with Music::Format enum. </returns>
inline const std::string* Music::getFormatStrings()
{
	return Music::m_formatStrings;
}

///<summary> Setter method for the duration of the album. </summary>
///<returns> Nothing. </returns>
inline void Music::setDuration(int duration)
{
	m_duration = duration;
}

///<summary> Setter method for the format of the album. </summary>
///<returns> Nothing. </returns>
inline void Music::setFormat(Music::Format format)
{
	m_format = format;
}

///<summary> Method used to help create a test library to see that the Music class works appropriately. </summary>
///<returns> Pointer to array holding Music objects with pre-populated data. </returns>
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