#include "Service.h"
#include "Validator.h"
#include <string>
#include <sstream>
#include <exception>
#include <algorithm>


void Service::addEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph)
{
	Evidence evidenceToBeAdded{ evidenceID, measurement, imageClarityLevel, quantity, photograph };
	try
	{
		this->repository->addEvidenceToRepository(evidenceToBeAdded);
	}
	catch (DuplicateIDException)
	{
		throw DuplicateIDException();
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}
}

std::vector<Evidence> Service::getAllEvidenceService()
{
	return this->repository->getAllEvidenceFromRepository();
}

void Service::deleteEvidence(const std::string& evidenceID)
{
	try
	{
		this->repository->deleteEvidenceFromRepository(evidenceID);
	}
	catch (NonExistentIDException)
	{
		throw NonExistentIDException();
	}
}

void Service::updateEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph)
{
	Evidence newEvidence{ evidenceID, measurement, imageClarityLevel, quantity, photograph };
	try
	{
		this->repository->updateEvidenceInRepository(newEvidence);
	}
	catch (NonExistentIDException)
	{
		throw NonExistentIDException();
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}
}

void Service::setAccessMode(char accessMode)
{
	this->accessMode = accessMode;
	indexOfNextEvidenceToBeDisplayed = 0;
}

char Service::getAccessMode()
{
	return this->accessMode;
}

int Service::indexOfNextEvidenceToBeDisplayed = 0;

std::vector<Evidence> Service::getAllPhysicalCopiesService()
{
	return this->standardUserDatabase->getAllEvidencesFromUserDatabase();
}

Evidence Service::getNextEvidence()
{
	int numberOfEvidencesInRepository = this->getAllEvidenceService().size();
	if (numberOfEvidencesInRepository == 0)
		throw std::length_error("No evidence in the database!");
	Evidence nextEvidence = this->getAllEvidenceService().at(indexOfNextEvidenceToBeDisplayed);
	indexOfNextEvidenceToBeDisplayed++;
	if (indexOfNextEvidenceToBeDisplayed == numberOfEvidencesInRepository)
		indexOfNextEvidenceToBeDisplayed = 0;
	return nextEvidence;
}

void Service::saveEvidenceToUserDatabase(const std::string& evidenceID)
{
	int indexOfEvidenceInRepository = this->repository->findEvidenceIndexByID(evidenceID);
	if (indexOfEvidenceInRepository == -1)
		throw NonExistentIDException();
	Evidence evidenceToBeAddedInDatabase = this->getAllEvidenceService().at(indexOfEvidenceInRepository);
	try
	{
		this->standardUserDatabase->saveEvidenceToDatabase(evidenceToBeAddedInDatabase);
	}
	catch (DuplicateIDException)
	{
		throw DuplicateIDException();
	}
}

std::vector<Evidence> Service::filterByMeasurementAndQuantity(const std::string& measurement, const int quantity)
{
	std::vector<Evidence> listOfFilteredEvidence;
	std::vector<Evidence> listOfAllEvidence = this->getAllEvidenceService();
	std::copy_if(listOfAllEvidence.begin(), listOfAllEvidence.end(), std::back_inserter(listOfFilteredEvidence),
		[quantity, measurement](Evidence evidenceFromList)
		{ return evidenceFromList.getQuantity() >= quantity && (measurement == "" || evidenceFromList.getMeasurement() == measurement); });
	return listOfFilteredEvidence;
}

void Service::setFileRepository(std::string fileName)
{
	try 
	{
		ModeAFileNameValidator::validateFileName(fileName);
		Repository* repository = new FileRepository{ fileName };
		this->repository = repository;
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}
}

void Service::setMemoryRepository()
{
	Repository* repository = new MemoryRepository{};
	this->repository = repository;
}

void Service::setStandardUserDatabase(std::string fileName)
{
	try
	{
		StandardFileNameValidator::validateFileName(fileName);
		std::string fileExtension = fileName.substr(fileName.size() - DIMENSION_OF_EXTENSION, fileName.size() - 1);
		if ( fileExtension == ".csv")
		{
			CSVStandardUserDatabase* newStandardUserDatabase = new CSVStandardUserDatabase{ fileName };
			this->standardUserDatabase = newStandardUserDatabase;
		}
		else
		{
			HTMLStandardUserDatabase* newStandardUserDatabase = new HTMLStandardUserDatabase{ fileName };
			this->standardUserDatabase = newStandardUserDatabase;
		}
			
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}
}

void Service::openDataInApplication()
{
	this->standardUserDatabase->openFileInApplication();
}

Service::~Service()
{
	delete this->repository;
	delete this->standardUserDatabase;
}
