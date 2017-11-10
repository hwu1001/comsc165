#ifndef BADPASSWORD_H
#define BADPASSWORD_H
#include <string>

class BadPassword
{
public:
	enum class ExceptionType
	{
		AT_LEAST_8_CHAR,
		ONE_NUMERIC,
		ONE_UPPER_CHAR,
		ONE_LOWER_CHAR,
		SPECIAL_CHAR
	};
	BadPassword();
	BadPassword(BadPassword::ExceptionType exception);
	~BadPassword();
	std::string getErrorDescription();

private:
	BadPassword::ExceptionType m_exception;
	std::string m_errorDescription;
};

BadPassword::BadPassword()
{
}

BadPassword::BadPassword(BadPassword::ExceptionType exception)
{
	m_exception = exception;
	switch (m_exception)
	{
	case BadPassword::ExceptionType::AT_LEAST_8_CHAR:
		m_errorDescription = "Password length is less than 8 characters.";
		break;
	case BadPassword::ExceptionType::ONE_NUMERIC:
		m_errorDescription = "Password does not contain at least one numeric character.";
		break;
	case BadPassword::ExceptionType::ONE_UPPER_CHAR:
		m_errorDescription = "Password does not have at least one upper case character.";
		break;
	case BadPassword::ExceptionType::ONE_LOWER_CHAR:
		m_errorDescription = "Password does not have at least one lower case character.";
		break;
	case BadPassword::ExceptionType::SPECIAL_CHAR:
		m_errorDescription = "Password does not have at least one of the special characters of '!@#$%&*:;'";
		break;
	default:
		break;
	}
}

BadPassword::~BadPassword()
{
}
inline std::string BadPassword::getErrorDescription()
{
	return m_errorDescription;
}
#endif // !BADPASSWORD_H

