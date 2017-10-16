#ifndef DATE_H
#define DATE_H
#include <string>
#include <cmath>
#include <ctime>

///<summary> Date class used to handle date information and functions related to a calendar.</summary>
class Date
{
public:
	Date();
	Date(int month, int day, int year);
	~Date();
	int getMonth();
	int getDay();
	int getYear();
	void getDate(int &month, int &day, int &year);
	bool isNullDate();
	void setMonth(int month);
	void setDay(int day);
	void setYear(int year);
	void setDate(int month, int day, int year);
	Date getCurrentDate();
	static bool isLeapYear(int year);
	static const int* getMonthDays();
	std::string toString();
	bool operator>(const Date &rightDate);
	int operator-(const Date &rightDate);

private:
	int m_month;
	int m_day;
	int m_year;
	bool m_isNullDate;
	int countLeapYears();
	static const std::string m_monthName[];
	static const int m_monthDays[];

};

///<summary> Default constructor for Date class. For basic instantiation. </summary>
///<returns> Nothing. </returns>
Date::Date()
{
	m_isNullDate = true;
}

///<summary> Constructor for Date object that sets all available variables of class. </summary>
///<param name="month"> Month of the date. </param>
///<param name="day"> Day of the date. </param>
///<param name="year"> Year of the date. </param>
///<returns> Nothing. </returns>
Date::Date(int month, int day, int year)
{
	m_month = month;
	m_day = day;
	m_year = year;
	m_isNullDate = false;
}

///<summary> Default destructor for Date class. No special actions taken. </summary>
///<returns> Nothing. </returns>
Date::~Date()
{
}

///<summary> Getter method for variable holding month of the date. </summary>
///<returns> The month of the date. </returns>
inline int Date::getMonth()
{
	return m_month;
}

///<summary> Getter method for variable holding day of the date. </summary>
///<returns> The day of the date. </returns>
inline int Date::getDay()
{
	return m_day;
}

///<summary> Getter method for variable holding year of the date. </summary>
///<returns> The year of the date. </returns>
inline int Date::getYear()
{
	return m_year;
}

///<summary> Getter for all relevant Date variables. </summary>
///<param name="month"> Output of month. </param>
///<param name="day"> Output of day. </param>
///<param name="year"> Output of year. </param>
///<returns> Nothing. </returns>
inline void Date::getDate(int &month, int &day, int &year)
{
	month = m_month;
	day = m_day;
	year = m_year;
}

///<summary> Says if the current date object is a null date or not. </summary>
///<returns> True if the Date object is null, otherwise false. </returns>
inline bool Date::isNullDate()
{
	return m_isNullDate;
}

///<summary> Setter method for the month of the date. </summary>
///<param name="month"> Month of the date. </param>
///<returns> Nothing. </returns>
inline void Date::setMonth(int month)
{
	m_month = month;
}

///<summary> Setter method for the day of the date. </summary>
///<param name="day"> Day of the date. </param>
///<returns> Nothing. </returns>
inline void Date::setDay(int day)
{
	m_day = day;
}

///<summary> Setter method for the year of the date. </summary>
///<param name="year"> Year of the date. </param>
///<returns> Nothing. </returns>
inline void Date::setYear(int year)
{
	m_year = year;
}

///<summary> Setter method for the month, day, and year. </summary>
///<param name="month"> Month of the date. </param>
///<param name="day"> Day of the date. </param>
///<param name="year"> Year of the date. </param>
///<returns> Nothing. </returns>
void Date::setDate(int month, int day, int year)
{
	m_month = month;
	m_day = day;
	m_year = year;
}

///<summary> Returns a Date object containing the current date (today's date). </summary>
///<returns> A Date object with the current date. </returns>
Date Date::getCurrentDate()
{
	time_t t = time(0);
	//struct tm* now = localtime(&t);
	struct tm now;
	localtime_s(&now, &t);
	return Date(now.tm_mon + 1, now.tm_mday, now.tm_year + 1900);
}

///<summary> Determines whether a given date is a leap year or not. </summary>
///<param name="year"> Year of the date. </param>
///<returns> True if year is a leap year, otherwise false. </returns>
inline bool Date::isLeapYear(int year)
{
	bool leapYear;
	if (year % 4 != 0)
	{
		leapYear = false;
	}
	else if (year % 100 != 0)
	{
		leapYear = true;
	}
	else if (year % 400 != 0)
	{
		leapYear = false;
	}
	else
	{
		leapYear = true;
	}
	return leapYear;
}

///<summary> Getter method for array with days associated with each month. </summary>
///<returns> Pointer to array that contains days associated with each month. </returns>
inline const int* Date::getMonthDays()
{
	return m_monthDays;
}

///<summary> Converts a Date object into a string in the form of month/day/year. </summary>
///<returns> A string in the form of month/day/year. </returns>
inline std::string Date::toString()
{
	std::string dateString;
	dateString = std::to_string(m_month) + "/" + std::to_string(m_day) + "/" + std::to_string(m_year);
	return dateString;
}

///<summary> Operator overload for ">" operator. </summary>
///<returns> True if the date to the left of the ">" operator is closer to the present, otherwise false. </returns>
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

///<summary> Operator overload for "-" binary operator. </summary>
///<returns> The absolute value number of days between the date to the left of the "-" operator and the date to the right. </returns>
inline int Date::operator-(const Date & rightDate)
{
	// TODO: Update this method for leap years
	// http://www.geeksforgeeks.org/find-number-of-days-between-two-given-dates/

	// Get total number of days before first date, we'll do the same with the second date
	long int num1 = m_year * 365 + m_day;
	for (int i = 0; i < m_month - 1; i++)
	{
		num1 += Date::m_monthDays[i];
	}
	// Add a day for every leap year
	num1 += this->countLeapYears();

	long int num2 = rightDate.m_year * 365 + rightDate.m_day;
	for (int i = 0; i < rightDate.m_month - 1; i++)
	{
		num2 += Date::m_monthDays[i];
	}
	// Since the rightDate is a const we can't use a private method on it, so copy into temporary object
	Date tempDate = rightDate;
	num2 += tempDate.countLeapYears();

	return abs(num1 - num2);
}

///<summary> Counts the number of leap years before the date in the Date object. </summary>
///<returns> The number of leap years before the date in the Date object. </returns>
inline int Date::countLeapYears()
{
	int years = m_year;
	if (m_month <= 2)
	{
		years--;
	}
	return years / 4 - years / 100 + years / 400;
}

const std::string Date::m_monthName[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const int Date::m_monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

#endif // !DATE_H