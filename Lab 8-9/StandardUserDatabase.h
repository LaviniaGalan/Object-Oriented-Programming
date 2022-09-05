#pragma once
#include "Domain.h"
#include "Exception.h"
#include <vector>

class StandardUserDatabase
{
public:
	StandardUserDatabase() {}

	virtual void saveEvidenceToDatabase(const Evidence& evidenceToBeSaved) = 0;

	virtual std::vector<Evidence> getAllEvidencesFromUserDatabase() = 0;

	virtual void openFileInApplication() = 0;

	virtual ~StandardUserDatabase() {}
};

class CSVStandardUserDatabase : public StandardUserDatabase
{
private:
	std::string fileName;
public:
	CSVStandardUserDatabase(const std::string& fileName = "");

	void saveEvidenceToDatabase(const Evidence& evidenceToBeSaved) override;
	std::vector<Evidence> getAllEvidencesFromUserDatabase() override;
	
	bool databaseHasEvidenceID(const std::string& evidenceID);
	void openFileInApplication() override;
};


class HTMLStandardUserDatabase : public StandardUserDatabase
{
private:
	std::string fileName;
public:
	HTMLStandardUserDatabase(const std::string& fileName = "");

	void saveEvidenceToDatabase(const Evidence& evidenceToBeSaved) override;
	std::vector<Evidence> getAllEvidencesFromUserDatabase() override;
	bool databaseHasEvidenceID(const std::string& evidenceID);
	void saveDataInFile(std::vector<Evidence> listOfPhysicalCopies);
	void openFileInApplication() override;

	Evidence createEvidenceWithGivenAttributes(std::vector<std::string> listOfAttributes);
};
