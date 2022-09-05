#pragma once
#include <string>
#include "Domain.h"

#define DIMENSION_OF_CSV_EXTENSION 4
#define DIMENSION_OF_HTML_EXTENSION 5

class ValidationException
{
private:
	std::string messageOfException;

public:
	ValidationException(std::string messageOfException);
	std::string getMessageOfException() const;
};


class EvidenceValidator
{
public:
	static void validateEvidence(const Evidence& evidence);
};


class StandardFileNameValidator
{
public:
	static void validateFileName(const std::string& fileName);
};

class ModeAFileNameValidator
{
public:
	static void validateFileName(const std::string& fileName);
};


