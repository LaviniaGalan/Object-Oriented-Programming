#include "Domain.h"
#include <string>
#include <sstream>
#include <vector>

Evidence::Evidence() : evidenceID(""), measurement(""), imageClarityLevel(0), quantity(0), photograph("") {}

Evidence::Evidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph)
{
	this->evidenceID = evidenceID;
	this->measurement = measurement;
	this->imageClarityLevel = imageClarityLevel;
	this->quantity = quantity;
	this->photograph = photograph;
}

bool Evidence::operator==(const Evidence& evidence)
{
	if (this->evidenceID == evidence.getEvidenceID() && this->measurement == evidence.getMeasurement() && this->imageClarityLevel == evidence.getImageClarityLevel() && this->quantity == evidence.getQuantity() && this->photograph == evidence.getPhotograph())
		return true;
	return false;
}

std::string Evidence::evidenceDataToString()
{
	return this->evidenceID + " - " + this->measurement + " - " + std::to_string(this->imageClarityLevel) + " - " + std::to_string(this->quantity) + " - " + this->photograph;
}

std::string Evidence::getEvidenceID() const
{
	return this->evidenceID;
}

std::string Evidence::getMeasurement() const
{
	return this->measurement;
}

double Evidence::getImageClarityLevel() const
{
	return this->imageClarityLevel;
}

int Evidence::getQuantity() const
{
	return this->quantity;
}

std::string Evidence::getPhotograph() const
{
	return this->photograph;
}


std::vector<std::string> splitListOfAttributes(std::string listOfArguments, char delimiter)
{
	std::vector<std::string> vectorWithSplitArguments;
	std::string argumentOfCommand;
	std::stringstream streamForSplitting(listOfArguments);
	while (getline(streamForSplitting, argumentOfCommand, delimiter))
	{
		int indexOfWhiteCharacterAtBegining = 0;
		while (argumentOfCommand.at(indexOfWhiteCharacterAtBegining) == ' ' && indexOfWhiteCharacterAtBegining < argumentOfCommand.size())
			indexOfWhiteCharacterAtBegining++;
		argumentOfCommand.erase(0, indexOfWhiteCharacterAtBegining);

		int indexOfWhiteCharacterAtEnd = argumentOfCommand.size() - 1;
		while (argumentOfCommand.at(indexOfWhiteCharacterAtEnd) == ' ' && indexOfWhiteCharacterAtEnd > 0)
			indexOfWhiteCharacterAtEnd--;
		if (indexOfWhiteCharacterAtEnd != argumentOfCommand.size() - 1)
			argumentOfCommand.erase(indexOfWhiteCharacterAtEnd + 1, argumentOfCommand.size());

		vectorWithSplitArguments.push_back(argumentOfCommand);
	}
	return vectorWithSplitArguments;
}


std::istream& operator>>(std::istream& inputStream, Evidence& evidence)
{
	std::string listOfAttributesOfEvidence;
	std::getline(inputStream, listOfAttributesOfEvidence);

	std::vector<std::string> vectorWithAttributes = splitListOfAttributes(listOfAttributesOfEvidence, ',');
	if (vectorWithAttributes.size() != NUMBER_OF_TOTAL_ATTRIBUTES)
		return inputStream;
	evidence.evidenceID = vectorWithAttributes[INDEX_OF_EVIDENCE_ID];
	evidence.measurement = vectorWithAttributes[INDEX_OF_MEASUREMENT];
	evidence.imageClarityLevel = strtod(vectorWithAttributes[INDEX_OF_CLARITY_LEVEL].c_str(), 0);
	evidence.quantity = atoi(vectorWithAttributes[INDEX_OF_QUANTITY].c_str());
	evidence.photograph = vectorWithAttributes[INDEX_OF_PHOTOGRAPH];

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Evidence& evidence)
{
	outputStream << evidence.evidenceID << ", " << evidence.measurement << ", " << evidence.imageClarityLevel << ", " << evidence.quantity << ", " << evidence.photograph << '\n';
	return outputStream;
}


