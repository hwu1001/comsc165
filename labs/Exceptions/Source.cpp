#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
#include "BadPassword.h"

using namespace std;

bool isCorrectLength(char* password);
bool hasOneNumeric(char* password);
bool hasOneUpper(char* password);
bool hasOneLower(char* password);
bool hasOneSpecialChar(char* password);
bool cStrContainsAnyInArray(char* cStr, char* charArr);

int main()
{
	char* password = new char[100];
	bool len = true, num = true, up = true, low = true, spec = true, validPass = true;
	string errorDesc;

	cout << "Enter your password (max length 100): ";
	cin.getline(password, 100);

	// Obviously, shouldn't actually do it like this but doing it to use try/catch
	try
	{
		if (!isCorrectLength(password))
		{
			// nothing to do if this is false because of throw
		}
	}
	catch (BadPassword& bp)
	{
		errorDesc = bp.getErrorDescription() + '\n';
		validPass = false;
	}
	try
	{
		if (!hasOneNumeric(password))
		{
			// nothing to do if this is false because of throw
		}
	}
	catch (BadPassword& bp)
	{
		errorDesc = errorDesc + bp.getErrorDescription() + '\n';
		validPass = false;
	}
	try
	{
		if (!hasOneUpper(password))
		{
			// nothing to do if this is false because of throw
		}
	}
	catch (BadPassword& bp)
	{
		errorDesc = errorDesc + bp.getErrorDescription() + '\n';
		validPass = false;
	}
	try
	{
		if (!hasOneLower(password))
		{
			// nothing to do if this is false because of throw
		}
	}
	catch (BadPassword& bp)
	{
		errorDesc = errorDesc + bp.getErrorDescription() + '\n';
		validPass = false;
	}
	try
	{
		if (!hasOneSpecialChar(password))
		{
			// nothing to do if this is false because of throw
		}
	}
	catch (BadPassword& bp)
	{
		errorDesc = errorDesc + bp.getErrorDescription() + '\n';
		validPass = false;
	}
	//	if (isCorrectLength(password) && hasOneNumeric(password) && hasOneUpper(password) && hasOneLower(password) && hasOneSpecialChar(password))
	//	{
	//		validPass = true;
	//	}
	//	else
	//	{
	//		validPass = false;
	//	}
	//}
	//catch (BadPassword& bp)
	//{
	//	cout << "Invalid password." << '\n';
	//	cout << bp.getErrorDescription() << '\n';
	//}

	if (validPass)
	{
		cout << "Password is valid." << '\n';
	}
	else
	{
		cout << "Invalid password." << '\n';
		cout << errorDesc;
	}

	delete[] password;
	password = nullptr;
	return 0;
}

bool isCorrectLength(char * password)
{
	if (strlen(password) >= 8)
	{
		return true;
	}
	else
	{
		throw BadPassword(BadPassword::ExceptionType::AT_LEAST_8_CHAR);
		return false;
	}
}

bool hasOneNumeric(char * password)
{
	bool numeric = cStrContainsAnyInArray(password, "1234567890");
	if (!numeric)
	{
		throw BadPassword(BadPassword::ExceptionType::ONE_NUMERIC);
	}
	return numeric;
}

bool hasOneUpper(char * password)
{
	bool found = false;
	for (int i = 0; i < strlen(password); i++)
	{
		if (isupper(*(password + i)))
		{
			found = true;
			break;
		}
	}
	if (!found)
	{
		throw BadPassword(BadPassword::ExceptionType::ONE_UPPER_CHAR);
	}
	return found;
}

bool hasOneLower(char * password)
{
	bool found = false;
	for (int i = 0; i < strlen(password); i++)
	{
		if (islower(*(password + i)))
		{
			found = true;
			break;
		}
	}
	if (!found)
	{
		throw BadPassword(BadPassword::ExceptionType::ONE_LOWER_CHAR);
	}
	return found;
}

bool hasOneSpecialChar(char * password)
{
	bool found = cStrContainsAnyInArray(password, "!@#$%&*:;");
	if (!found)
	{
		throw BadPassword(BadPassword::ExceptionType::SPECIAL_CHAR);
	}
	return found;
}

bool cStrContainsAnyInArray(char * cStr, char * charArr)
{
	char* ptr = nullptr;
	bool found = false;
	for (int i = 0; i < strlen(charArr); i++)
	{
		ptr = strchr(cStr, *(charArr + i));
		if (ptr != NULL)
		{
			found = true;
			break;
		}
	}
	return found;
}
