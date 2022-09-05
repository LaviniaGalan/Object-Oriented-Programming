#include "Repository.h"


Repository::Repository()
{
	this->iteratorOfListOfEvidences = this->listOfEvidences.startOfVector();
}

int Repository::addEvidenceToRepository(const Evidence& evidenceToBeAdded)
{
	if (this->findEvidenceIndexByID(evidenceToBeAdded.getEvidenceID()) != -1)
		return -1;
	this->listOfEvidences.addElement(evidenceToBeAdded);
	return 0;
}

int Repository::findEvidenceIndexByID(std::string evidenceID)
{
	for (int index = 0; index < this->listOfEvidences.getSizeOfVector(); index++)
	{
		if (this->listOfEvidences.getElementFromIndex(index).getEvidenceID() == evidenceID)
			return index;
	}
	return -1;
}

int Repository::deleteEvidenceFromRepository(std::string evidenceID)
{
	int indexToDeleteFrom = this->findEvidenceIndexByID(evidenceID);
	if (indexToDeleteFrom == -1)
		return -1;
	this->listOfEvidences.deleteElementFromIndex(indexToDeleteFrom);
	return 0;
}

int Repository::updateEvidenceInRepository(const Evidence& newEvidence)
{
	int indexToBeUpdated = this->findEvidenceIndexByID(newEvidence.getEvidenceID());
	if (indexToBeUpdated == -1)
		return -1;
	this->listOfEvidences.updateElementFromIndex(indexToBeUpdated, newEvidence);
	return 0;
}

DynamicVector<Evidence> Repository::getAllEvidenceFromRepository() const
{
	return this->listOfEvidences;
}

Evidence Repository::getNextEvidence()
{
	Evidence currentEvidence = *this->iteratorOfListOfEvidences;
	++this->iteratorOfListOfEvidences;
	if (this->iteratorOfListOfEvidences == this->listOfEvidences.endOfVector())
		this->iteratorOfListOfEvidences = this->listOfEvidences.startOfVector();
	return currentEvidence;
}
