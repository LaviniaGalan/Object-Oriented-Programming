#pragma once
#include "Service.h"
#include <vector>

#define INDEX_OF_EVIDENCE_ID 0
#define INDEX_OF_MEASUREMENT 1
#define INDEX_OF_CLARITY_LEVEL 2
#define INDEX_OF_QUANTITY 3
#define INDEX_OF_PHOTOGRAPH 4

#define INDEX_OF_QUANTITY_IN_FILTERING_NO_MEASUREMENT 0
#define INDEX_OF_QUANTITY_IN_FILTERING 1
#define INDEX_OF_MEASUREMENT_IN_FILTERING 0

class UserInterface
{
private:
	Service service;
public:
	UserInterface(const Service& service) : service(service) {}

	void runProgram();
	void listEvidenceUI();
	void addEvidenceUI(std::string argumentsOfAdding);
	void deleteEvidenceUI(std::string argumentsOfDeleting);
	void updateEvidenceUI(std::string argumentsOfUpdating);

	std::vector<std::string> splitListOfArguments(std::string listOfArguments);

	void listNextEvidenceUI();
	void listNextEvidenceUIIteratorVersion();
	void listAllPhysicalCopiesUI();

	void saveEvidenceToUserDatabaseUI(std::string argumentsOfSaving);
	void filterByMeasurementAndQuantityUI(std::string argumentsOfFiltering);
};


