#include "UI.h"
#include <sstream>

void UserInterface::runProgram()
{

	std::string keyWordOfCommand, fullInputCommand, argumentsOfCommand;
	char accessMode;
	bool repositoryFileWasSet = false;
	while (true)
	{
		std::getline(std::cin, fullInputCommand);
		std::stringstream streamForSplitting(fullInputCommand);
		std::getline(streamForSplitting, keyWordOfCommand, ' ');
		if (keyWordOfCommand == "exit") return;
		else if (keyWordOfCommand == "fileLocation")
		{
			argumentsOfCommand = fullInputCommand.erase(0, keyWordOfCommand.length() + 1);
			std::string fileName = this->splitListOfArguments(argumentsOfCommand).at(0);
			try {
				this->service.setFileRepository(fileName);
				repositoryFileWasSet = true;
			}
			catch (ValidationException & exception)
			{
				std::cout << exception.getMessageOfException();
			}
		}
		else if (keyWordOfCommand == "mylistLocation")
		{
			argumentsOfCommand = fullInputCommand.erase(0, keyWordOfCommand.length() + 1);
			std::string fileName = this->splitListOfArguments(argumentsOfCommand).at(0);
			try {
				this->service.setStandardUserDatabase(fileName);
			}
			catch (ValidationException & exception)
			{
				std::cout << exception.getMessageOfException();
			}
		}
		else if (keyWordOfCommand == "mode")
		{
			accessMode = fullInputCommand.at(keyWordOfCommand.size() + 1);
			this->service.setAccessMode(accessMode);

			if (repositoryFileWasSet == false)
				this->service.setMemoryRepository();

			if (this->service.getAccessMode() == 'A')
				this->runModeA();

			else if (this->service.getAccessMode() == 'B')
				this->runModeB();

			return;
		}
	}
}


void UserInterface::runModeA()
{
	std::string keyWordOfCommand, fullInputCommand, argumentsOfCommand;
	char accessMode;
	while (true)
	{
		std::getline(std::cin, fullInputCommand);
		std::stringstream streamForSplitting(fullInputCommand);
		std::getline(streamForSplitting, keyWordOfCommand, ' ');
		if (keyWordOfCommand == "exit") return;
		if (keyWordOfCommand == "mode")
		{
			this->runModeB();
			return;
		}
		if (keyWordOfCommand == "list") this->listAllEvidence();
		argumentsOfCommand = fullInputCommand.erase(0, keyWordOfCommand.length() + 1);
		if (keyWordOfCommand == "add")
			this->addEvidence(argumentsOfCommand);
		else if (keyWordOfCommand == "delete")
			this->deleteEvidence(argumentsOfCommand);
		else if (keyWordOfCommand == "update")
			this->updateEvidence(argumentsOfCommand);
	}
}

void UserInterface::runModeB()
{
	std::string keyWordOfCommand, fullInputCommand, argumentsOfCommand;
	char accessMode;
	while (true)
	{
		std::getline(std::cin, fullInputCommand);
		std::stringstream streamForSplitting(fullInputCommand);
		std::getline(streamForSplitting, keyWordOfCommand, ' ');
		if (keyWordOfCommand == "exit") return;

		if (keyWordOfCommand == "mylist")
		{
			this->listAllPhysicalCopies();
			this->openDataInApplication();
		}
		else if (keyWordOfCommand == "next") this->listNextEvidence();
		else if (keyWordOfCommand == "mode")
		{
			this->runModeA();
			return;
		}
		else
		{
			argumentsOfCommand = fullInputCommand.erase(0, keyWordOfCommand.length() + 1);
			if (keyWordOfCommand == "save")
				this->saveEvidenceToUserDatabase(argumentsOfCommand);
			else if (keyWordOfCommand == "list")
				this->filterByMeasurementAndQuantity(argumentsOfCommand);
		}
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
		while (indexOfWhiteCharacterAtBegining < argumentOfCommand.size() && argumentOfCommand.at(indexOfWhiteCharacterAtBegining) == ' ')
			indexOfWhiteCharacterAtBegining++;
		argumentOfCommand.erase(0, indexOfWhiteCharacterAtBegining);

		int indexOfWhiteCharacterAtEnd = argumentOfCommand.size() - 1;
		while (indexOfWhiteCharacterAtEnd > 0 && argumentOfCommand.at(indexOfWhiteCharacterAtEnd) == ' ')
			indexOfWhiteCharacterAtEnd--;
		if (indexOfWhiteCharacterAtEnd != argumentOfCommand.size() - 1)
			argumentOfCommand.erase(indexOfWhiteCharacterAtEnd, argumentOfCommand.size());

		vectorWithSplitArguments.push_back(argumentOfCommand);
	}
	return vectorWithSplitArguments;
}



void UserInterface::listAllEvidence()
{
	std::vector<Evidence> listOfEvidence = this->service.getAllEvidenceService();
	for (Evidence evidenceFromList : listOfEvidence)
		std::cout << evidenceFromList;

}

void UserInterface::addEvidence(std::string argumentsOfAdding)
{
	std::vector<std::string> vectorWithArgumentsOfAdding = this->splitListOfArguments(argumentsOfAdding);
	std::string evidenceID, measurement, photograph;

	evidenceID = vectorWithArgumentsOfAdding[INDEX_OF_EVIDENCE_ID];
	measurement = vectorWithArgumentsOfAdding[INDEX_OF_MEASUREMENT];
	double imageClarityLevel = strtod(vectorWithArgumentsOfAdding[INDEX_OF_CLARITY_LEVEL].c_str(), 0);
	int quantity = atoi(vectorWithArgumentsOfAdding[INDEX_OF_QUANTITY].c_str());
	photograph = vectorWithArgumentsOfAdding[INDEX_OF_PHOTOGRAPH];

	try
	{
		this->service.addEvidence(evidenceID, measurement, imageClarityLevel, quantity, photograph);
	}
	catch (InvalidIDException& exception)
	{
		std::cout << exception.what();
	}
	catch (ValidationException & exception)
	{
		std::cout << exception.getMessageOfException();
	}
}


void UserInterface::deleteEvidence(std::string argumentsOfDeleting)
{
	std::string evidenceID = argumentsOfDeleting;
	try
	{
		this->service.deleteEvidence(evidenceID);
	}
	catch (InvalidIDException& exception)
	{
		std::cout << exception.what();
	}
}

void UserInterface::updateEvidence(std::string argumentsOfUpdating)
{
	std::vector<std::string> vectorWithArgumentsOfAdding = this->splitListOfArguments(argumentsOfUpdating);
	std::string evidenceID, newMeasurement, newPhotograph;

	evidenceID = vectorWithArgumentsOfAdding[INDEX_OF_EVIDENCE_ID];
	newMeasurement = vectorWithArgumentsOfAdding[INDEX_OF_MEASUREMENT];
	double newImageClarityLevel = strtod(vectorWithArgumentsOfAdding[INDEX_OF_CLARITY_LEVEL].c_str(), 0);
	int newQuantity = atoi(vectorWithArgumentsOfAdding[INDEX_OF_QUANTITY].c_str());
	newPhotograph = vectorWithArgumentsOfAdding[INDEX_OF_PHOTOGRAPH];

	try
	{
		this->service.updateEvidence(evidenceID, newMeasurement, newImageClarityLevel, newQuantity, newPhotograph);
	}
	catch (InvalidIDException& exception)
	{
		std::cout << exception.what();
	}
	catch (ValidationException & exception)
	{
		std::cout<<exception.getMessageOfException();
	}
}


void UserInterface::listAllPhysicalCopies()
{
	std::vector<Evidence> listOfPhysicalCopies = this->service.getAllPhysicalCopiesService();
	for (Evidence evidenceFromList : listOfPhysicalCopies)
		std::cout << evidenceFromList;
}

void UserInterface::saveEvidenceToUserDatabase(std::string argumentsOfSaving)
{
	std::vector<std::string> vectorWithArgumentsOfSaving = this->splitListOfArguments(argumentsOfSaving);
	std::string evidenceID = vectorWithArgumentsOfSaving[INDEX_OF_EVIDENCE_ID];
	try
	{
		this->service.saveEvidenceToUserDatabase(evidenceID);
	}
	catch (InvalidIDException & exception)
	{
		std::cout << exception.what();
	}
}

void UserInterface::filterByMeasurementAndQuantity(std::string argumentsOfFiltering)
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
	std::vector<Evidence> listOfFilteredEvidenceUI = this->service.filterByMeasurementAndQuantity(measurement, quantity);
	for (int index = 0; index < listOfFilteredEvidenceUI.size(); index++)
		std::cout << listOfFilteredEvidenceUI.at(index);
}

void UserInterface::openDataInApplication()
{
	this->service.openDataInApplication();
}

void UserInterface::listNextEvidence()
{
	try
	{
		Evidence evidenceToBePrinted = this->service.getNextEvidence();
		std::cout << evidenceToBePrinted;
	}
	catch (...)
	{
		std::cout << "No evidence in the database!\n";
	}
}