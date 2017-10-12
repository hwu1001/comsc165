#ifndef VIDEO_H
#define VIDEO_H
#include <string>
#include "Publication.h"

///<summary> Video class used to create videos in a library. A derived class of Publication. </summary>
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

///<summary> Default constructor for Video class. For basic instantiation, no actions taken. </summary>
///<returns> Nothing. </returns>
Video::Video()
{
}

///<summary> Constructor for Music object that sets all available variables of class. Uses Publication constructor within it. </summary>
///<param name="title"> Title of the video. </param>
///<param name="author"> Author of the video. Usually the person that wrote the screenplay. </param>
///<param name="copies"> Number of copies available of the video. </param>
///<param name="resolution"> Resolution of the video. See Video::Resolution enum for possible options. </param>
///<param name="producer"> Producer of the video. </param>
///<returns> Nothing. </returns>
Video::Video(std::string title, std::string author, int copies, Resolution resolution, std::string producer) : Publication(title, author, copies)
{
	m_resolution = resolution;
	m_producer = producer;
}

///<summary> Default destructor for Video class. No special actions taken. </summary>
///<returns> Nothing. </returns>
Video::~Video()
{
}

///<summary> Getter method for the resolution of the video. </summary>
///<returns> The resultion of the video. </returns>
inline Video::Resolution Video::getResolution()
{
	return m_resolution;
}

///<summary> Getter method for producer of the video. </summary>
///<returns> The producer of the video. </returns>
inline std::string Video::getProducer()
{
	return m_producer;
}

///<summary> Getter method for the strings associated with the Video::Resolution enum. </summary>
///<returns> A pointer to the array holding the strings associated with Video::Resolution enum. </returns>
inline const std::string* Video::getResolutionStrings()
{
	return Video::m_resolutionStrings;
}

///<summary> Setter method for the resolution of the video. </summary>
///<param name="resolution"> Resolution of the video. See Video::Resolution enum for possible options. </param>
///<returns> Nothing. </returns>
inline void Video::setResolution(Video::Resolution resolution)
{
	m_resolution = resolution;
}

///<summary> Setter method for the producer of the video. </summary>
///<param name="producer"> Producer of the video. </param>
///<returns> Nothing. </returns>
inline void Video::setProducer(std::string producer)
{
	m_producer = producer;
}

///<summary> Method used to help create a test library to see that the Video class works appropriately. </summary>
///<returns> Pointer to array holding Video objects with pre-populated data. </returns>
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