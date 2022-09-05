#include "UI.h"
#include <iostream>
#include <string>
#include <sstream>


void UserInterface::runProgram()
{
	std::string keyWordOfCommand, fullInputCommand, argumentsOfCommand;
	char accessMode;
	while (true)
	{
		std::getline(std::cin, fullInputCommand);
		std::stringstream streamForSplitting(fullInputCommand);
		std::getline(streamForSplitting, keyWordOfCommand, ' ');
		if (keyWordOfCommand == "exit") return;
		else if (keyWordOfCommand == "mode")
		{
			accessMode = fullInputCommand.at(keyWordOfCommand.size() + 1);
			this->service.setAccessMode(accessMode);
		}
		else
		{
			if (this->service.getAccessMode() == 'A')
			{
				if (keyWordOfCommand == "list") this->listEvidenceUI();
				argumentsOfCommand = fullInputCommand.erase(0, keyWordOfCommand.length() + 1);
				if (keyWordOfCommand == "add")
					this->addEvidenceUI(argumentsOfCommand);
				else if (keyWordOfCommand == "delete")
					this->deleteEvidenceUI(argumentsOfCommand);
				else if (keyWordOfCommand == "update")
					this->updateEvidenceUI(argumentsOfCommand);
			}
			else if (this->service.getAccessMode() == 'B')
			{
				if (keyWordOfCommand == "mylist") this->listAllPhysicalCopiesUI();
				else if (keyWordOfCommand == "next") this->listNextEvidenceUIIteratorVersion();
				else
				{
					argumentsOfCommand = fullInputCommand.erase(0, keyWordOfCommand.length() + 1);
					if (keyWordOfCommand == "save")
						this->saveEvidenceToUserDatabaseUI(argumentsOfCommand);
					else if (keyWordOfCommand == "list")
						this->filterByMeasurementAndQuantityUI(argumentsOfCommand);
				}

			}

		}

	}
}

void UserInterface::listEvidenceUI()
{
	DynamicVector<Evidence> listOfEvidenceUI = this->service.getAllEvidenceService();
	Evidence evidenceFromList;
	for (int index = 0; index < listOfEvidenceUI.getSizeOfVector(); index++)
	{
		evidenceFromList = listOfEvidenceUI.getElementFromIndex(index);
		std::cout << evidenceFromList.evidenceDataToString() << "\n";
	}

}

std::vector<std::string> UserInterface::splitListOfArguments(std::string listOfArguments)
{
	std::vector<std::string> vectorWithSplitArguments;
	std::string argumentOfCommand;
	std::stringstream streamForSplitting(listOfArguments);
	while (getline(streamForSplitting, argumentOfCommand, ','))
	{
		int indexOfWhiteCharacterAtBegining = 0;
		while (argumentOfCommand.at(indexOfWhiteCharacterAtBegining) == ' ' && indexOfWhiteCharacterAtBegining < argumentOfCommand.size())
			indexOfWhiteCharacterAtBegining++;
		argumentOfCommand.erase(0, indexOfWhiteCharacterAtBegining);

		int indexOfWhiteCharacterAtEnd = argumentOfCommand.size() - 1;
		while (argumentOfCommand.at(indexOfWhiteCharacterAtEnd) == ' ' && indexOfWhiteCharacterAtBegining > 0)
			indexOfWhiteCharacterAtEnd--;
		if (indexOfWhiteCharacterAtEnd != argumentOfCommand.size() - 1)
			argumentOfCommand.erase(indexOfWhiteCharacterAtEnd, argumentOfCommand.size());

		vectorWithSplitArguments.push_back(argumentOfCommand);
	}
	return vectorWithSplitArguments;
}


void UserInterface::addEvidenceUI(std::string argumentsOfAdding)
{
	std::vector<std::string> vectorWithArgumentsOfAdding = this->splitListOfArguments(argumentsOfAdding);
	std::string evidenceID, measurement, photograph;

	evidenceID = vectorWithArgumentsOfAdding[INDEX_OF_EVIDENCE_ID];
	measurement = vectorWithArgumentsOfAdding[INDEX_OF_MEASUREMENT];
	double imageClarityLevel = strtod(vectorWithArgumentsOfAdding[INDEX_OF_CLARITY_LEVEL].c_str(), 0);
	int quantity = atoi(vectorWithArgumentsOfAdding[INDEX_OF_QUANTITY].c_str());
	photograph = vectorWithArgumentsOfAdding[INDEX_OF_PHOTOGRAPH];

	int resultOfAdding = this->service.addEvidence(evidenceID, measurement, imageClarityLevel, quantity, photograph);
	if (resultOfAdding == -1) std::cout << "No!\n";
}


void UserInterface::deleteEvidenceUI(std::string argumentsOfDeleting)
{
	std::string evidenceID = argumentsOfDeleting;

	int resultOfDeleting = this->service.deleteEvidence(evidenceID);

	if (resultOfDeleting == -1) std::cout << "No!\n";
}

void UserInterface::updateEvidenceUI(std::string argumentsOfUpdating)
{
	std::vector<std::string> vectorWithArgumentsOfAdding = this->splitListOfArguments(argumentsOfUpdating);
	std::string evidenceID, newMeasurement, newPhotograph;

	evidenceID = vectorWithArgumentsOfAdding[INDEX_OF_EVIDENCE_ID];
	newMeasurement = vectorWithArgumentsOfAdding[INDEX_OF_MEASUREMENT];
	double newImageClarityLevel = strtod(vectorWithArgumentsOfAdding[INDEX_OF_CLARITY_LEVEL].c_str(), 0);
	int newQuantity = atoi(vectorWithArgumentsOfAdding[INDEX_OF_QUANTITY].c_str());
	newPhotograph = vectorWithArgumentsOfAdding[INDEX_OF_PHOTOGRAPH];

	int resultOfUpdating = this->service.updateEvidence(evidenceID, newMeasurement, newImageClarityLevel, newQuantity, newPhotograph);
	if (resultOfUpdating == -1) std::cout << "No! \n";
}

void UserInterface::listNextEvidenceUI()
{
	try
	{
		Evidence evidenceToBePrinted = this->service.getNextEvidence();
		std::cout << evidenceToBePrinted.evidenceDataToString() << '\n';
	}
	catch (...)
	{
		std::cout << "No evidence in the database!\n";
	}
}

void UserInterface::listNextEvidenceUIIteratorVersion()
{
	try
	{
		Evidence evidenceToBePrinted = this->service.getNextEvidenceWithIterator();
		std::cout << evidenceToBePrinted.evidenceDataToString() << '\n';
	}
	catch (...)
	{
		std::cout << "No evidence in the database!\n";
	}
}

void UserInterface::listAllPhysicalCopiesUI()
{
	DynamicVector<Evidence> listOfPhysicalCopies = this->service.getAllPhysicalCopiesService();
	Evidence evidenceFromList;
	for (int index = 0; index < listOfPhysicalCopies.getSizeOfVector(); index++)
	{
		evidenceFromList = listOfPhysicalCopies.getElementFromIndex(index);
		std::cout << evidenceFromList.evidenceDataToString() << '\n';
	}
}

void UserInterface::saveEvidenceToUserDatabaseUI(std::string argumentsOfSaving)
{
	std::vector<std::string> vectorWithArgumentsOfSaving = this->splitListOfArguments(argumentsOfSaving);
	std::string evidenceID = vectorWithArgumentsOfSaving[INDEX_OF_EVIDENCE_ID];
	int resultOfSaving = this->service.saveEvidenceToUserDatabase(evidenceID);
	if (resultOfSaving == -1)
		std::cout << "Invalid ID! \n";
}

void UserInterface::filterByMeasurementAndQuantityUI(std::string argumentsOfFiltering)
{
	std::vector<std::string> vectorWithArgumentsOfSaving = this->splitListOfArguments(argumentsOfFiltering);
	std::string measurement;
	int quantity;
	if (vectorWithArgumentsOfSaving.size() == 1)
	{
		measurement = "";
		quantity = atoi(vectorWithArgumentsOfSaving[INDEX_OF_QUANTITY_IN_FILTERING_NO_MEASUREMENT].c_str());
	}
	else if (vectorWithArgumentsOfSaving.size() == 2)
	{
		measurement = vectorWithArgumentsOfSaving[INDEX_OF_MEASUREMENT_IN_FILTERING];
		quantity = atoi(vectorWithArgumentsOfSaving[INDEX_OF_QUANTITY_IN_FILTERING].c_str());
	}
	DynamicVector<Evidence> listOfFilteredEvidenceUI = this->service.filterByMeasurementAndQuantity(measurement, quantity);
	for (int index = 0; index < listOfFilteredEvidenceUI.getSizeOfVector(); index++)
		std::cout << listOfFilteredEvidenceUI.getElementFromIndex(index).evidenceDataToString() << "\n";
	

}