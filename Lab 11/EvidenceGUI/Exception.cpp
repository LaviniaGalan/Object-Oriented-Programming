#include "Exception.h"

const char* InvalidIDException::what() const throw()
{
	return this->messageOfException.c_str();
}


const char* DuplicateIDException::what() const throw()
{
	return "Evidence with given ID already exists in the database!\n";
}

const char* NonExistentIDException::what() const throw()
{
	return "Evidence with given ID isn't in the database!\n";
}