#pragma once
#include <iostream>

#define INDEX_OF_EVIDENCE_ID 0
#define INDEX_OF_MEASUREMENT 1
#define INDEX_OF_CLARITY_LEVEL 2
#define INDEX_OF_QUANTITY 3
#define INDEX_OF_PHOTOGRAPH 4

#define INDEX_OF_QUANTITY_IN_FILTERING_NO_MEASUREMENT 0
#define INDEX_OF_QUANTITY_IN_FILTERING 1
#define INDEX_OF_MEASUREMENT_IN_FILTERING 0

#define NUMBER_OF_TOTAL_ATTRIBUTES 5


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

	friend std::istream& operator>>(std::istream& inputStream, Evidence& evidence);
	friend std::ostream& operator<<(std::ostream& outputStream, const Evidence& evidence);
};

