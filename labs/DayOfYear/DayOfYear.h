#ifndef DAYOFYEAR_H
#define DAYOFYEAR_H
#include <string>
#include <iostream>

class DayOfYear
{
public:
	DayOfYear();
	DayOfYear(int day);
	~DayOfYear();
	int getDay();
	void setDay(int day);
	static std::string translate(int day);
	void print();

private:
	int m_day;
	static const std::string m_monthName[];
	static const int m_monthDays[];

};

DayOfYear::DayOfYear()
{
}

DayOfYear::DayOfYear(int day)
{
	m_day = day;
}

DayOfYear::~DayOfYear()
{
}

inline int DayOfYear::getDay()
{
	return m_day;
}

inline void DayOfYear::setDay(int day)
{
	m_day = day;
}

std::string DayOfYear::translate(int day)
{
	std::string monthDay;
	int count = 0;

	while (day > 0)
	{
		day -= m_monthDays[count];
		count++;
	}
	day = day + m_monthDays[count - 1];
	monthDay = m_monthName[count - 1] + " " + std::to_string(day);

	return monthDay;
}

inline void DayOfYear::print()
{
	std::cout << translate(m_day) << std::endl;
}

const std::string DayOfYear::m_monthName[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const int DayOfYear::m_monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

#endif // !DAYOFYEAR_H

