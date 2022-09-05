#include "Service.h"
#include <string>
#include <sstream>
#include <exception>



int Service::addEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph)
{
	Evidence evidenceToBeAdded{ evidenceID, measurement, imageClarityLevel, quantity, photograph };
	int resultOfAdding = this->repository.addEvidenceToRepository(evidenceToBeAdded);
	return resultOfAdding;
}

DynamicVector<Evidence> Service::getAllEvidenceService()
{
	return this->repository.getAllEvidenceFromRepository();
}

int Service::deleteEvidence(const std::string& evidenceID)
{
	int resultOfDeleting = this->repository.deleteEvidenceFromRepository(evidenceID);
	return resultOfDeleting;
}

int Service::updateEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph)
{
	Evidence newEvidence{ evidenceID, measurement, imageClarityLevel, quantity, photograph };
	int resultOfUpdating = this->repository.updateEvidenceInRepository(newEvidence);
	return resultOfUpdating;
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

DynamicVector<Evidence> Service::getAllPhysicalCopiesService()
{
	return this->standardUserDatabase.getAllEvidencesFromUserDatabase();
}

Evidence Service::getNextEvidence()
{
	int numberOfEvidencesInRepository = this->getAllEvidenceService().getSizeOfVector();
	if (numberOfEvidencesInRepository == 0)
		throw std::length_error("No evidence in the database!");
	Evidence nextEvidence = this->getAllEvidenceService().getElementFromIndex(indexOfNextEvidenceToBeDisplayed);
	indexOfNextEvidenceToBeDisplayed++;
	if (indexOfNextEvidenceToBeDisplayed == numberOfEvidencesInRepository)
		indexOfNextEvidenceToBeDisplayed = 0;
	return nextEvidence;
}

Evidence Service::getNextEvidenceWithIterator()
{
	if (this->getAllEvidenceService().getSizeOfVector() == 0)
		throw std::length_error("No evidence in the database!");
	Evidence currentEvidence = this->repository.getNextEvidence();
	return currentEvidence;
}

int Service::saveEvidenceToUserDatabase(const std::string& evidenceID)
{
	int indexOfEvidenceInRepository = this->repository.findEvidenceIndexByID(evidenceID);
	if (indexOfEvidenceInRepository == -1) 
		return -1;
	Evidence evidenceToBeAddedInDatabase = this->getAllEvidenceService().getElementFromIndex(indexOfEvidenceInRepository);
	this->standardUserDatabase.saveEvidenceToDatabase(evidenceToBeAddedInDatabase);
	return 0;
}

DynamicVector<Evidence> Service::filterByMeasurementAndQuantity(const std::string& measurement, const int quantity)
{
	DynamicVector<Evidence> listOfFilteredEvidence;
	DynamicVector<Evidence> listOfAllEvidence = this->getAllEvidenceService();
	Evidence evidenceFromOriginalList;
	for (int index = 0; index < listOfAllEvidence.getSizeOfVector(); index++)
	{
		evidenceFromOriginalList = listOfAllEvidence.getElementFromIndex(index);
		if (evidenceFromOriginalList.getQuantity() >= quantity)
		{
			if (measurement == "" || evidenceFromOriginalList.getMeasurement() == measurement)
				listOfFilteredEvidence.addElement(evidenceFromOriginalList);
		}
	}
	return listOfFilteredEvidence;
}
