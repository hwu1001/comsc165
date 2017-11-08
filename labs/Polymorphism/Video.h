#ifndef VIDEO_H
#define VIDEO_H
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <string>

class Video : public Publication
{
public:
	Video();
	Video(std::string title, char* resolution);
	~Video();
	char* getResolution();
	virtual void showData();

private:
	char m_resolution[2];

};

Video::Video()
{
}

inline Video::Video(std::string title, char * resolution)
{
	m_title = title;
	for (int i = 0; i < 2; i++)
	{
		m_resolution[i] = resolution[i];
	}
	m_resolution[2] = '\0';
}

Video::~Video()
{
}
inline char * Video::getResolution()
{
	return m_resolution;
}
inline void Video::showData()
{
	std::string resolution = m_resolution;
	//int len = this->m_title.length();
	//std::cout << std::left << std::setw(10) << "Video" << std::setw(20) << this->m_title << resolution << '\n';
	std::cout << std::left << std::setw(10) << "Video" << std::setw(20) << m_title << std::setw(8) << "-" << std::setw(11) << resolution << "-" << '\n';
}
#endif // !VIDEO_H

