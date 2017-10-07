#include <iostream>
#include "Student.h"

using namespace std;
int ID_COUNTER = 1;

Student* createStudent();
void displayStudent(Student* studentPtr);
Student* deleteStudent(Student* studentPtr);

int main()
{
	Student* studentPtr = nullptr;
	int choice;
	const int SELECT_MIN = 1, SELECT_MAX = 3;

	do
	{
		choice = 0;
		cout << "1. Create student" << endl;
		cout << "2. Display student" << endl;
		cout << "3. Delete student" << endl;
		cout << "What would you like to do? (q to quit) ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			if (studentPtr != nullptr)
			{
				studentPtr = deleteStudent(studentPtr);
			}
			cin.ignore();
			studentPtr = createStudent();
			break;
		case 2:
			displayStudent(studentPtr);
			break;
		case 3:
			studentPtr = deleteStudent(studentPtr);
			break;
		default:
			if ((choice > SELECT_MAX || choice < SELECT_MIN) && !cin.fail())
			{
				cout << "Invalid selection, please enter again" << endl;
			}
			break;
		}

	} while (!cin.fail());

	delete studentPtr;
	studentPtr = nullptr;

	return 0;
}

Student * createStudent()
{
	Student* studentPtr = nullptr;
	string name;
	bool done = false;

	while (!done)
	{
		cout << "Please enter the student's full name: ";
		getline(cin, name);

		if (name.empty())
		{
			cout << "Name not entered, please re-enter" << endl;
			continue;
		}
		done = true;
	}

	studentPtr = new Student(name, ID_COUNTER++);

	return studentPtr;
}

void displayStudent(Student * studentPtr)
{
	if (studentPtr == nullptr)
	{
		cout << "No existing student to display." << endl;
	}
	else
	{
		cout << "Student Information" << endl;
		cout << "Name: " << studentPtr->getName() << endl;
		cout << "ID: " << studentPtr->getId() << endl;
	}
}

Student* deleteStudent(Student * studentPtr)
{
	if (studentPtr == nullptr)
	{
		cout << "No existing student to delete." << endl;
	}
	else
	{
		delete studentPtr;
	}
	return nullptr;
}
