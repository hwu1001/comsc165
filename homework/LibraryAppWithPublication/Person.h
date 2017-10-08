#ifndef PERSON_H
#define PERSON_H
#include <string>

class Person
{
public:
	Person();
	Person(std::string name, int id, std::string email);
	~Person();
	std::string getName();
	int getId();
	std::string getEmail();
	void setName(std::string name);
	void setId(int id);
	void setEmail(std::string email);
	Person* testData();

private:
	std::string m_name;
	int m_identifier;
	std::string m_email;

};

Person::Person()
{
}

Person::Person(std::string name, int id, std::string email)
{
	m_name = name;
	m_identifier = id;
	m_email = email;
}

Person::~Person()
{
}

inline std::string Person::getName()
{
	return m_name;
}

inline int Person::getId()
{
	return m_identifier;
}

inline std::string Person::getEmail()
{
	return m_email;
}

inline void Person::setName(std::string name)
{
	m_name = name;
}

inline void Person::setId(int id)
{
	m_identifier = id;
}

inline void Person::setEmail(std::string email)
{
	m_email = email;
}

Person * Person::testData()
{
	static Person testPeople[] = { Person("John Smith", 1, "jsmith@comcast.net"),
		Person("Ashley Thompson", 2, "aThompson@gmail.com"),
		Person("Ralph Moore", 3, "testEmail@outlook.com"),
		Person("Kimberley Ericson", 4, "Kim_Ericson@yahoo.com") };

	return testPeople;
}

#endif // !PERSON_H

