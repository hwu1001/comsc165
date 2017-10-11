#ifndef DATE_H
#define DATE_H
#include <string>
#include <cmath>

class Date
{
public:
	Date();
	Date(int month, int day, int year);
	~Date();
	int getMonth();
	int getDay();
	int getYear();
	void setMonth(int month);
	void setDay(int day);
	void setYear(int year);
	Date operator++(int);
	Date operator--(int);
	bool operator>(const Date &rightDate);
	int operator-(const Date &rightDate);

private:
	int m_month;
	int m_day;
	int m_year;
	static const std::string m_monthName[];
	static const int m_monthDays[];

};

Date::Date()
{
}

Date::Date(int month, int day, int year)
{
	m_month = month;
	m_day = day;
	m_year = year;
}

Date::~Date()
{
}
inline int Date::getMonth()
{
	return m_month;
}
inline int Date::getDay()
{
	return m_day;
}
inline int Date::getYear()
{
	return m_year;
}
inline void Date::setMonth(int month)
{
	m_month = month;
}
inline void Date::setDay(int day)
{
	m_day = day;
}
inline void Date::setYear(int year)
{
	m_year = year;
}

inline Date Date::operator++(int)
{
	Date temp = *this;
	m_day++;
	if (m_day > Date::m_monthDays[m_month - 1])
	{
		m_day = 1;
		m_month++;
		if (m_month > 12)
		{
			m_month = 1;
			m_year++;
		}
	}
	return temp;
}

inline Date Date::operator--(int)
{
	Date temp = *this;
	m_day--;
	if (m_day < 1)
	{
		m_month--;
		if (m_month < 1)
		{
			m_month = 12;
			m_year--;
		}
		m_day = Date::m_monthDays[m_month - 1];
	}
	return temp;
}

inline bool Date::operator>(const Date & rightDate)
{
	if (m_year > rightDate.m_year)
	{
		return true;
	}
	else if ((m_year == rightDate.m_year) && (m_month > rightDate.m_month))
	{
		return true;
	}
	else if ((m_year == rightDate.m_year) && (m_month == rightDate.m_month) && (m_day > rightDate.m_day))
	{
		return true;
	}

	return false;
}

inline int Date::operator-(const Date & rightDate)
{
	// http://www.geeksforgeeks.org/find-number-of-days-between-two-given-dates/

	long int num1 = m_year * 365 + m_day;
	for (int i = 0; i < m_month - 1; i++)
	{
		num1 += Date::m_monthDays[i];
	}

	long int num2 = rightDate.m_year * 365 + rightDate.m_day;
	for (int i = 0; i < rightDate.m_month - 1; i++)
	{
		num2 += Date::m_monthDays[i];
	}
	return abs(num1 - num2);
}

const std::string Date::m_monthName[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const int Date::m_monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

#endif // !DATE_H

