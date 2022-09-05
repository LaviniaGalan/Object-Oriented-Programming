#pragma once
#include <exception>
#include <string>

class InvalidIDException : public std::exception
{
private:
	std::string messageOfException;

public:
	InvalidIDException() {}

	InvalidIDException(const std::string& message) : messageOfException{ message } {}

	virtual const char* what() const throw() override;

	virtual ~InvalidIDException() {}
};


class DuplicateIDException : public InvalidIDException
{
public:
	const char* what() const throw() override;
};

class NonExistentIDException : public InvalidIDException
{
public:
	const char* what() const throw() override;
};