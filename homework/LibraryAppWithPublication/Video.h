#ifndef VIDEO_H
#define VIDEO_H
#include <string>
#include "Publication.h"

class Video : public Publication
{
public:
	enum class Resolution
	{
		LOW,
		HIGH,
		FOURK
	};
	Video();
	Video(std::string title, std::string author, int copies, Resolution resolution, std::string producer);
	~Video();
	Video::Resolution getResolution();
	std::string getProducer();
	const std::string* getResolutionStrings();
	void setResolution(Video::Resolution resolution);
	void setProducer(std::string producer);
	Video* testData();

private:
	Resolution m_resolution;
	std::string m_producer;
	static const std::string m_resolutionStrings[];

};

Video::Video()
{
}

Video::Video(std::string title, std::string author, int copies, Resolution resolution, std::string producer) : Publication(title, author, copies)
{
	m_resolution = resolution;
	m_producer = producer;
}

Video::~Video()
{
}

inline Video::Resolution Video::getResolution()
{
	return m_resolution;
}

inline std::string Video::getProducer()
{
	return m_producer;
}

inline const std::string* Video::getResolutionStrings()
{
	return Video::m_resolutionStrings;
}

inline void Video::setResolution(Video::Resolution resolution)
{
	m_resolution = resolution;
}

inline void Video::setProducer(std::string producer)
{
	m_producer = producer;
}

Video* Video::testData()
{
	static Video testVideos[] =
	{
		Video("Pulp Fiction", "Quentin Tarantino", 3, Video::Resolution::HIGH, "Lawrence Bender"),
		Video("Star Wars: Episode IV - A New Hope", "George Lucas", 4, Video::Resolution::FOURK, "Gary Kurtz"),
		Video("Seven Samurai", "Akira Kurasawa", 2, Video::Resolution::LOW, "Sojiro Motoki")
	};

	return testVideos;
}

const std::string Video::m_resolutionStrings[] = { "Low", "High", "4K" };
#endif // !VIDEO_H