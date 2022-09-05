#pragma once
#include "Service.h"
#include "Validator.h"
class UserInterface
{
private:
	Service service;
public:
	UserInterface(Service& service) : service(service) {};


	void runProgram();
	void runModeA();
	void runModeB();

	std::vector<std::string> splitListOfArguments(std::string listOfArguments);

	void listAllEvidence();
	void addEvidence(std::string argumentsOfAdding);
	void deleteEvidence(std::string argumentsOfDeleting);
	void updateEvidence(std::string argumentsOfUpdating);

	void listNextEvidence();
	void listAllPhysicalCopies();

	void saveEvidenceToUserDatabase(std::string argumentsOfSaving);
	void filterByMeasurementAndQuantity(std::string argumentsOfFiltering);

	void openDataInApplication();
};

