#ifndef PUBLICATION_H
#define PUBLICATION_H
#include <string>

class Publication
{
protected:
	std::string m_title;
public:
	Publication();
	~Publication();
	std::string getTitle();
	virtual void showData()=0;

private:

};

Publication::Publication()
{
}

Publication::~Publication()
{
}

inline std::string Publication::getTitle()
{
	return m_title;
}

#endif // !PUBLICATION_H

