#ifndef PERSON_H
#define PERSON_H
#include <string>

///<summary> Pesron class used to represent library members. </summary>
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

///<summary> Default constructor for Person class. For basic instantiation, no actions taken. </summary>
///<returns> Nothing. </returns>
Person::Person()
{
}

///<summary> Constructor for Person object that sets all available variables of class. </summary>
///<param name="name"> Name of person. </param>
///<param name="id"> Numeric identifier for person. </param>
///<param name="email"> Email for person. </param>
///<returns> Nothing. </returns>
Person::Person(std::string name, int id, std::string email)
{
	m_name = name;
	m_identifier = id;
	m_email = email;
}

///<summary> Default destructor for Person class. No special actions taken. </summary>
///<returns> Nothing. </returns>
Person::~Person()
{
}

///<summary> Getter method for the name of the person. </summary>
///<returns> The name of the person. </returns>
inline std::string Person::getName()
{
	return m_name;
}

///<summary> Getter method for the identifier of the person. </summary>
///<returns> The identifier of the person. </returns>
inline int Person::getId()
{
	return m_identifier;
}

///<summary> Getter method for the email of the person. </summary>
///<returns> The email of the person. </returns>
inline std::string Person::getEmail()
{
	return m_email;
}

///<summary> Setter method for the name of the person. </summary>
///<param name="name"> Name of the person. </param>
///<returns> The name of the person. </returns>
inline void Person::setName(std::string name)
{
	m_name = name;
}

///<summary> Setter method for the identifier of the person. </summary>
///<param name="id"> Identifier for the person. </param>
///<returns> The identifier of the person. </returns>
inline void Person::setId(int id)
{
	m_identifier = id;
}

///<summary> Setter method for the email of the person. </summary>
///<param name="email"> Email for the person. </param>
///<returns> The email of the person. </returns>
inline void Person::setEmail(std::string email)
{
	m_email = email;
}

///<summary> Method used to help create a test library to see that the Person class works appropriately. </summary>
///<returns> Pointer to array holding Person objects with pre-populated data. </returns>
Person * Person::testData()
{
	static Person testPeople[] = { Person("John Smith", 1, "jsmith@comcast.net"),
		Person("Ashley Thompson", 2, "aThompson@gmail.com"),
		Person("Ralph Moore", 3, "testEmail@outlook.com"),
		Person("Kimberley Ericson", 4, "Kim_Ericson@yahoo.com") };
	return testPeople;
}

#endif // !PERSON_H

