#pragma once
#include <iostream>
class Evidence
{
private:
	std::string evidenceID;
	std::string measurement;
	double imageClarityLevel;
	int quantity;
	std::string photograph;

public:
	Evidence();
	Evidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph);
	bool operator==(const Evidence& evidence);

	std::string getEvidenceID() const;
	std::string getMeasurement() const;
	double getImageClarityLevel() const;
	int getQuantity() const;
	std::string getPhotograph() const;

	std::string evidenceDataToString();
};

