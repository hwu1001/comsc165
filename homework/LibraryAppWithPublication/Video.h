#ifndef VIDEO_H
#define VIDEO_H
#include <string>

class Video
{
public:
	Video();
	~Video();
	enum Resolution
	{
		low,
		high,
		fourK
	};
	Video::Resolution getResolution();
	std::string getProducer();
	void setResolution(Video::Resolution resolution);
	void setProducer(std::string producer);

private:
	Resolution m_resolution;
	std::string m_producer;

};

Video::Video()
{
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

inline void Video::setResolution(Video::Resolution resolution)
{
	m_resolution = resolution;
}

inline void Video::setProducer(std::string producer)
{
	m_producer = producer;
}
#endif // !VIDEO_H