#include "MemoryRepository.h"

MemoryRepository::MemoryRepository()
{
}

void MemoryRepository::addEvidenceToRepository(const Evidence& evidenceToBeAdded)
{
	try
	{
		EvidenceValidator::validateEvidence(evidenceToBeAdded);
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}

	if (this->findEvidenceIndexByID(evidenceToBeAdded.getEvidenceID()) != -1)
		throw DuplicateIDException();
	this->listOfEvidences.push_back(evidenceToBeAdded);
}

int MemoryRepository::findEvidenceIndexByID(std::string evidenceID)
{
	int index = 0;
	for (Evidence evidenceFromList : listOfEvidences)
	{
		if (evidenceFromList.getEvidenceID() == evidenceID)
			return index;
		index++;
	}
	return -1;
}

void MemoryRepository::deleteEvidenceFromRepository(std::string evidenceID)
{
	int indexToDeleteFrom = this->findEvidenceIndexByID(evidenceID);
	if (indexToDeleteFrom == -1)
		throw NonExistentIDException();
	this->listOfEvidences.erase(listOfEvidences.begin() + indexToDeleteFrom);
}

void MemoryRepository::updateEvidenceInRepository(const Evidence& newEvidence)
{
	try
	{
		EvidenceValidator::validateEvidence(newEvidence);
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}

	int indexToBeUpdated = this->findEvidenceIndexByID(newEvidence.getEvidenceID());
	if (indexToBeUpdated == -1)
		throw NonExistentIDException();
	this->listOfEvidences.at(indexToBeUpdated) = newEvidence;
}

std::vector<Evidence> MemoryRepository::getAllEvidenceFromRepository() const
{
	return this->listOfEvidences;
}

void MemoryRepository::openFileInApplication()
{
}

Evidence MemoryRepository::findEvidenceByID(std::string evidenceID)
{
	for (Evidence evidenceFromList : this->listOfEvidences)
	{
		if (evidenceFromList.getEvidenceID() == evidenceID)
			return evidenceFromList;
	}
	return Evidence();
}

