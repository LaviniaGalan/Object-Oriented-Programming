#include "Domain.h"
#include <string>

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