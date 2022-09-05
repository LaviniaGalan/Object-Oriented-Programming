#include "Validator.h"
#include <iostream>

ValidationException::ValidationException(std::string messageOfException) 
{
	this->messageOfException = messageOfException;
}

std::string ValidationException::getMessageOfException() const
{
	return this->messageOfException;
}



void EvidenceValidator::validateEvidence(const Evidence& evidence)
{
	std::string errors;
	if (evidence.getEvidenceID().size() == 0)
		errors += std::string("The evidence ID cannot be empty. \n");
	if (evidence.getMeasurement().size() == 0)
		errors += std::string("The evidence measurements cannot be empty. \n");
	if (evidence.getImageClarityLevel() < 0)
		errors += std::string("The image clarity level cannot be negative. \n");
	if (evidence.getQuantity() < 0)
		errors += std::string("The quantity cannot be negative. \n");
	if (evidence.getPhotograph().size() == 0)
		errors += std::string("The evidence photograph cannot be empty. \n");

	if (errors.size() > 0)
		throw ValidationException(errors);
}


void StandardFileNameValidator::validateFileName(const std::string& fileName)
{
	std::string errors;
	if (fileName == "")
		errors += std::string("File name cannot be empty. \n");
	else
		if ((fileName.substr(fileName.size() - DIMENSION_OF_CSV_EXTENSION, fileName.size() - 1) != ".csv") && //if the last 4 characters of the file name are different from the ".cvs" extension
			(fileName.substr(fileName.size() - DIMENSION_OF_HTML_EXTENSION, fileName.size() - 1) != ".html")) //if the last 5 characters of the file name are different from the ".html" extension
					errors += std::string("The given filename does not have a valid extension. \n");

	if (errors.size() > 0)
		throw ValidationException(errors);
}

void ModeAFileNameValidator::validateFileName(const std::string& fileName)
{
	std::string errors;
	if (fileName == "")
		errors += std::string("File name cannot be empty. \n");
	//else
	//	if (fileName.substr(fileName.size() - DIMENSION_OF_CSV_EXTENSION, fileName.size() - 1) != ".txt") //if the last 4 characters of the file name are different from the ".cvs" extension
	//		errors += std::string("The given filename does not have a valid extension. \n");

	if (errors.size() > 0)
		throw ValidationException(errors);
}


