#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

class Employee
{
private:
	std::string lastName;
	double hourlyPay;
	double numHoursWorked;

public:
	Employee(std::string lName, double hPay = 0.0, double nHrWorked = 0.0)
	{
		lastName = lName;
		hourlyPay = hPay;
		numHoursWorked = nHrWorked;
	}
	Employee()
	{
		// do nothing in default
	}
	std::string getLastName()
	{
		return lastName;
	}
	double getHourlyPay()
	{
		return hourlyPay;
	}
	double getNumHoursWorked()
	{
		return numHoursWorked;
	}
	void setLastName(std::string lName)
	{
		lastName = lName;
	}
	void setHourlyPay(double hPay)
	{
		hourlyPay = hPay;
	}
	void setNumHoursWorked(double nHrWorked)
	{
		numHoursWorked = nHrWorked;
	}
	double totalPay()
	{
		return (numHoursWorked * hourlyPay);
	}


};

#endif // !EMPLOYEE_H

