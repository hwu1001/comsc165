#include <iostream>
#include <cstring>
#include <string>
#include <cctype>

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
	bool len = true , num = true, up = true, low = true, spec = true;
	
	cout << "Enter your password (max length 100): ";
	cin.getline(password, 100);
	
	bool validPass = true;
	if (!isCorrectLength(password))
	{
		validPass = false;
		len = false;
	}
	if (!hasOneNumeric(password))
	{
		validPass = false;
		num = false;
	}
	if (!hasOneUpper(password))
	{
		validPass = false;
		up = false;
	}
	if (!hasOneLower(password))
	{
		validPass = false;
		low = false;
	}
	if (!hasOneSpecialChar(password))
	{
		validPass = false;
		spec = false;
	}

	if (validPass)
	{
		cout << "Password is valid." << '\n';
	}
	else
	{
		cout << "Password is not valid." << '\n';
		cout << "Reasons: " << '\n';
		if (!len)
		{
			cout << "Password length is less than 8 characters." << '\n';
		}
		if (!num)
		{
			cout << "Password does not contain at least one numeric character." << '\n';
		}
		if (!up)
		{
			cout << "Password does not have at least one upper case character." << '\n';
		}
		if (!low)
		{
			cout << "Password does not have at least one lower case character." << '\n';
		}
		if (!spec)
		{
			cout << "Password does not have at least one of the special characters of '!@#$%&*:;'" << '\n';
		}
	}

	delete [] password;
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
		return false;
	}
}

bool hasOneNumeric(char * password)
{
	bool numeric = cStrContainsAnyInArray(password, "1234567890");
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
	return found;
}

bool hasOneSpecialChar(char * password)
{
	bool found = cStrContainsAnyInArray(password, "!@#$%&*:;");
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
