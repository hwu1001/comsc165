#ifndef STUDENT_H
#define STUDENT_H
#include <string>

class Student
{
public:
	Student();
	Student(std::string name, int id);
	~Student();
	std::string getName();
	int getId();

private:
	std::string m_name;
	int m_identifier;

};

Student::Student()
{
}

inline Student::Student(std::string name, int id)
{
	m_name = name;
	m_identifier = id;
}

Student::~Student()
{
}

inline std::string Student::getName()
{
	return m_name;
}

inline int Student::getId()
{
	return m_identifier;
}

#endif // !1

