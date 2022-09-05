#include "FileRepository.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <shellapi.h>

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

	std::vector<Evidence> listOfEvidence = this->getAllEvidenceFromRepository();
	listOfEvidence.push_back(evidenceToBeAdded);
	this->writeEvidenceDataToFile(listOfEvidence);
}

int FileRepository::findEvidenceIndexByID(std::string evidenceID)
{
	std::vector<Evidence> listOfEvidence = this->getAllEvidenceFromRepository();
	int indexOfEvidenceInFileRepository = 0;
	for (Evidence evidenceFromList : listOfEvidence)
	{
		if (evidenceFromList.getEvidenceID() == evidenceID)
		{
			return indexOfEvidenceInFileRepository;
		}
		indexOfEvidenceInFileRepository++;
	}
	return -1;
}

Evidence FileRepository::findEvidenceByID(std::string evidenceID)
{
	std::vector<Evidence> listOfEvidence = this->getAllEvidenceFromRepository();
	for (Evidence evidenceFromList : listOfEvidence)
	{
		if (evidenceFromList.getEvidenceID() == evidenceID)
		{
			return evidenceFromList;
		}
	}
	return Evidence();
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
	this->writeEvidenceDataToFile(listOfEvidence);
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
	this->writeEvidenceDataToFile(listOfEvidence);
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


std::string FileRepository::getFileName()
{
	return this->fileName;
}


//void FileRepository::writeEvidenceDataToFile(std::vector<Evidence> listOfEvidence)
//{
//	std::ofstream fileOutputStream(this->fileName.c_str());
//	for (Evidence evidenceToBeWritten : listOfEvidence)
//		fileOutputStream << evidenceToBeWritten;
//	fileOutputStream.close();
//}

//-------

CSVRepository::CSVRepository(const std::string& fileName)
{
	this->fileName = fileName;
}

std::vector<Evidence> CSVRepository::getAllEvidenceFromRepository() const
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

void CSVRepository::writeEvidenceDataToFile(std::vector<Evidence> listOfEvidence)
{
	std::ofstream fileOutputStream(this->fileName.c_str());
	for (Evidence evidenceToBeWritten : listOfEvidence)
			fileOutputStream << evidenceToBeWritten;
	fileOutputStream.close();
}

bool CSVRepository::repositoryHasEvidenceID(const std::string& evidenceID)
{
	std::vector<Evidence> listOfEvidence = this->getAllEvidenceFromRepository();
	for (Evidence evidence : listOfEvidence)
		if (evidence.getEvidenceID() == evidenceID)
			return true;
	return false;
}

void CSVRepository::openFileInApplication()
{
	ShellExecuteA(NULL, NULL, "notepad.exe", this->fileName.c_str(), NULL, SW_SHOWMAXIMIZED);
}

//--------

HTMLRepository::HTMLRepository(const std::string& fileName)
{
	this->fileName = fileName;
}

std::vector<Evidence> HTMLRepository::getAllEvidenceFromRepository() const
{
	std::vector<Evidence> listOfEvidence;
	std::ifstream fileInputStream(this->fileName.c_str());
	std::string readLineOfTheFile;
	bool dataOfEvidenceWasMet = false;
	while (dataOfEvidenceWasMet == false && fileInputStream >> readLineOfTheFile)
	{
		if (readLineOfTheFile.find("</tr>") != std::string::npos)
			dataOfEvidenceWasMet = true;
	}

	while (fileInputStream >> readLineOfTheFile)
	{
		if (readLineOfTheFile.find("<tr>") != std::string::npos)
		{
			// read the attributes of evidence
			std::vector<std::string> listOfAttributesOfEvidence;
			for (int counter = 0; counter < NUMBER_OF_TOTAL_ATTRIBUTES; counter++)
			{
				fileInputStream >> readLineOfTheFile;
				unsigned beginPositionOfAttribute = readLineOfTheFile.find("<td>") + std::strlen("<td>");
				unsigned endPositionOfAttribute = readLineOfTheFile.find("</td>");
				std::string readAttribute = readLineOfTheFile.substr(beginPositionOfAttribute, endPositionOfAttribute - beginPositionOfAttribute);
				listOfAttributesOfEvidence.push_back(readAttribute);
			}
			Evidence readEvidence = this->createEvidenceWithGivenAttributes(listOfAttributesOfEvidence);
			listOfEvidence.push_back(readEvidence);
			fileInputStream >> readLineOfTheFile; // reading the </tr> label
		}
		else
			break;
	}
	fileInputStream.close();
	return listOfEvidence;
}

void HTMLRepository::writeEvidenceDataToFile(std::vector<Evidence> listOfEvidence)
{
	std::ofstream fileOutputStream(this->fileName.c_str());
	fileOutputStream << "<!DOCTYPE html> \n" <<
		"<html> \n" <<
		"\t<head> \n" <<
		"\t \t <title>Evidences</title> \n" <<
		"\t </head> \n" <<
		"\t <body> \n" <<
		"\t <table border=\"1\"> \n \t <tr> \n" <<
		"\t \t <td> Evidence ID </td> \n" <<
		"\t \t <td> Measurement </td> \n" <<
		"\t \t <td> Image Clarity Level </td> \n" <<
		"\t \t <td> Quantity </td> \n" <<
		"\t \t <td> Photograph </td> \n" << "\t </tr> \n";
	for (Evidence evidence : listOfEvidence)
	{
		fileOutputStream << "\t <tr> \n " <<
			"\t \t <td>" << evidence.getEvidenceID() << "</td> \n" <<
			"\t \t <td>" << evidence.getMeasurement() << "</td> \n" <<
			"\t \t <td>" << evidence.getImageClarityLevel() << "</td> \n" <<
			"\t \t <td>" << evidence.getQuantity() << "</td> \n" <<
			"\t \t <td>" << evidence.getPhotograph() << "</td> \n" <<
			"\t </tr> \n";
	}
	fileOutputStream << " \t \t </table> \n \t </body> \n </html>";
	fileOutputStream.close();
}

bool HTMLRepository::repositoryHasEvidenceID(const std::string& evidenceID)
{
	std::vector<Evidence> listOfEvidence = this->getAllEvidenceFromRepository();
	for (Evidence evidence : listOfEvidence)
		if (evidence.getEvidenceID() == evidenceID)
			return true;
	return false;
}

void HTMLRepository::openFileInApplication()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->fileName.c_str(), NULL, SW_SHOWMAXIMIZED);
}

Evidence HTMLRepository::createEvidenceWithGivenAttributes(std::vector<std::string> listOfAttributes) const
{
	std::string evidenceID = listOfAttributes[INDEX_OF_EVIDENCE_ID];
	std::string measurement = listOfAttributes[INDEX_OF_MEASUREMENT];
	double imageClarityLevel = strtod(listOfAttributes[INDEX_OF_CLARITY_LEVEL].c_str(), 0);
	int quantity = atoi(listOfAttributes[INDEX_OF_QUANTITY].c_str());
	std::string photograph = listOfAttributes[INDEX_OF_PHOTOGRAPH];

	Evidence createdEvidence{ evidenceID, measurement, imageClarityLevel, quantity, photograph };
	return createdEvidence;
}
