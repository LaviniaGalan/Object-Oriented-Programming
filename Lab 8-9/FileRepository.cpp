#include "FileRepository.h"
#include <iostream>
#include <fstream>

FileRepository::FileRepository(const std::string& fileName)
{
	this->fileName = fileName;
}

void FileRepository::addEvidenceToRepository(const Evidence& evidenceToBeAdded)
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
	std::ofstream fileOutputStream;
	fileOutputStream.open(this->fileName.c_str(), std::ios_base::app);
	fileOutputStream << evidenceToBeAdded;
	fileOutputStream.close();
}

int FileRepository::findEvidenceIndexByID(std::string evidenceID)
{
	int indexOfEvidenceInFileRepository = 0;
	std::ifstream fileInputStream(this->fileName.c_str());
	Evidence readEvidence;
	while (fileInputStream >> readEvidence)
	{
		if (readEvidence.getEvidenceID() == evidenceID)
		{
			fileInputStream.close();
			return indexOfEvidenceInFileRepository;
		}
		indexOfEvidenceInFileRepository++;
	}
	fileInputStream.close();
	return -1;
}

void FileRepository::deleteEvidenceFromRepository(std::string evidenceID)
{
	std::vector<Evidence> listOfEvidence = this->getAllEvidenceFromRepository();
	int indexToBeRemoved = 0;
	for (Evidence evidenceFromList : listOfEvidence)
	{
		if (evidenceFromList.getEvidenceID() != evidenceID)
			indexToBeRemoved++;
		else
			break;
	}
	if (indexToBeRemoved == listOfEvidence.size())
		throw NonExistentIDException();
	listOfEvidence.erase(listOfEvidence.begin() + indexToBeRemoved);
	this->writeListOfEvidenceToFile(listOfEvidence);
}

std::vector<Evidence> FileRepository::getAllEvidenceFromRepository() const
{
	std::vector<Evidence> listOfEvidence;
	std::ifstream fileInputStream(this->fileName.c_str());
	Evidence readEvidence;
	while (fileInputStream >> readEvidence)
	{
		listOfEvidence.push_back(readEvidence);
	}
	fileInputStream.close();
	return listOfEvidence;
}

void FileRepository::updateEvidenceInRepository(const Evidence& newEvidence)
{
	try
	{
		EvidenceValidator::validateEvidence(newEvidence);
	}
	catch (ValidationException & exception)
	{
		throw ValidationException(exception.getMessageOfException());
	}

	std::vector<Evidence> listOfEvidence = this->getAllEvidenceFromRepository();
	int indexToBeUpdated = 0;
	for (Evidence evidenceFromList : listOfEvidence)
	{
		if (evidenceFromList.getEvidenceID() != newEvidence.getEvidenceID())
			indexToBeUpdated++;
		else
			break;
	}
	if (indexToBeUpdated == listOfEvidence.size())
		throw NonExistentIDException();
	listOfEvidence.at(indexToBeUpdated) = newEvidence;
	this->writeListOfEvidenceToFile(listOfEvidence);
}


void FileRepository::writeListOfEvidenceToFile(std::vector<Evidence> listOfEvidence)
{
	std::ofstream fileOutputStream(this->fileName.c_str());
	for (Evidence evidenceToBeWritten : listOfEvidence)
		fileOutputStream << evidenceToBeWritten;
	fileOutputStream.close();
}

std::string FileRepository::getFileName()
{
	return this->fileName;
}
