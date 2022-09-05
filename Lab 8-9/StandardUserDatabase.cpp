#include "StandardUserDatabase.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <shellapi.h>
#include <string.h>


CSVStandardUserDatabase::CSVStandardUserDatabase(const std::string& fileName)
{
	this->fileName = fileName;
}

void CSVStandardUserDatabase::saveEvidenceToDatabase(const Evidence& evidenceToBeSaved)
{
	if (this->databaseHasEvidenceID(evidenceToBeSaved.getEvidenceID()) == true)
		throw DuplicateIDException();
	std::ofstream fileOutputStream;
	fileOutputStream.open(this->fileName.c_str(), std::ios_base::app);
	fileOutputStream << evidenceToBeSaved;
	fileOutputStream.close();
}

bool CSVStandardUserDatabase::databaseHasEvidenceID(const std::string& evidenceID)
{
	std::vector<Evidence> listOfPhysicalCopies = this->getAllEvidencesFromUserDatabase();
	for (Evidence evidence : listOfPhysicalCopies)
		if (evidence.getEvidenceID() == evidenceID)
			return true;
	return false;
}

std::vector<Evidence> CSVStandardUserDatabase::getAllEvidencesFromUserDatabase()
{
	std::vector<Evidence> listOfPhysicalCopies;
	std::ifstream fileInputStream(this->fileName.c_str());
	Evidence readEvidence;
	while (fileInputStream >> readEvidence)
	{
		listOfPhysicalCopies.push_back(readEvidence);
	}
	fileInputStream.close();
	return listOfPhysicalCopies;
}


void CSVStandardUserDatabase::openFileInApplication()
{
	ShellExecuteA(NULL, NULL, "notepad.exe", this->fileName.c_str(), NULL, SW_SHOWMAXIMIZED);
}

//--------------------------------------------------------------------------------------------------------------

HTMLStandardUserDatabase::HTMLStandardUserDatabase(const std::string& fileName)
{
	this->fileName = fileName;
}

void HTMLStandardUserDatabase::saveEvidenceToDatabase(const Evidence& evidenceToBeSaved)
{
	if (this->databaseHasEvidenceID(evidenceToBeSaved.getEvidenceID()) == true)
		throw DuplicateIDException();
	std::vector<Evidence> listOfPhysicalCopies = this->getAllEvidencesFromUserDatabase();
	listOfPhysicalCopies.push_back(evidenceToBeSaved);
	this->saveDataInFile(listOfPhysicalCopies);
}

bool HTMLStandardUserDatabase::databaseHasEvidenceID(const std::string& evidenceID)
{
	std::vector<Evidence> listOfPhysicalCopies = this->getAllEvidencesFromUserDatabase();
	for (Evidence evidence : listOfPhysicalCopies)
		if (evidence.getEvidenceID() == evidenceID)
			return true;
	return false;
}

std::vector<Evidence> HTMLStandardUserDatabase::getAllEvidencesFromUserDatabase()
{
	std::vector<Evidence> listOfPhysicalCopies;
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
			listOfPhysicalCopies.push_back(readEvidence);
			fileInputStream >> readLineOfTheFile; // reading the </tr> label
		}
		else
			break;
	}
	fileInputStream.close();
	return listOfPhysicalCopies;
}

void HTMLStandardUserDatabase::saveDataInFile(std::vector<Evidence> listOfPhysicalCopies)
{
	std::ofstream fileOutputStream(this->fileName.c_str());
	fileOutputStream << "<!DOCTYPE html> \n" <<
						"<html> \n" <<
						"\t<head> \n" <<
						"\t \t <title>Evidences</title> \n" <<
						"\t </head> \n" <<
						"\t <body> \n"<<
						"\t <table border=\"1\"> \n \t <tr> \n"<<
						"\t \t <td> Evidence ID </td> \n"<<
						"\t \t <td> Measurement </td> \n"<<
						"\t \t <td> Image Clarity Level </td> \n"<<
						"\t \t <td> Quantity </td> \n" <<
						"\t \t <td> Photograph </td> \n" << "\t </tr> \n";
	for (Evidence evidence : listOfPhysicalCopies)
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

void HTMLStandardUserDatabase::openFileInApplication()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->fileName.c_str(), NULL, SW_SHOWMAXIMIZED);
}

Evidence HTMLStandardUserDatabase::createEvidenceWithGivenAttributes(std::vector<std::string> listOfAttributes)
{
	std::string evidenceID = listOfAttributes[INDEX_OF_EVIDENCE_ID];
	std::string measurement = listOfAttributes[INDEX_OF_MEASUREMENT];
	double imageClarityLevel = strtod(listOfAttributes[INDEX_OF_CLARITY_LEVEL].c_str(), 0);
	int quantity = atoi(listOfAttributes[INDEX_OF_QUANTITY].c_str());
	std::string photograph = listOfAttributes[INDEX_OF_PHOTOGRAPH];

	Evidence createdEvidence { evidenceID, measurement, imageClarityLevel, quantity, photograph };
	return createdEvidence;
}
