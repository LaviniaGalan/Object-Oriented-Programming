#pragma once
#include "Repository.h"

class FileRepository : public Repository
{
protected:
	std::string fileName;
public:
	FileRepository(const std::string& fileName = "");

	void addEvidenceToRepository(const Evidence& evidenceToBeAdded) override;

	int findEvidenceIndexByID(std::string evidenceID) override;
	Evidence findEvidenceByID(std::string evidenceID) override;

	void deleteEvidenceFromRepository(std::string evidenceID) override;

	void updateEvidenceInRepository(const Evidence& newEvidence) override;

	std::string getFileName();

	std::vector<Evidence> getAllEvidenceFromRepository() const override;

	virtual void writeEvidenceDataToFile(std::vector<Evidence> listOfEvidence) = 0;

};


class CSVRepository : public FileRepository
{
public:
	CSVRepository(const std::string& fileName = "");

	std::vector<Evidence> getAllEvidenceFromRepository() const override;
	void writeEvidenceDataToFile(std::vector<Evidence> listOfEvidence) override;

	bool repositoryHasEvidenceID(const std::string& evidenceID);
	void openFileInApplication() override;

};


class HTMLRepository : public FileRepository
{
public:
	HTMLRepository(const std::string& fileName = "");

	std::vector<Evidence> getAllEvidenceFromRepository() const override;
	void writeEvidenceDataToFile(std::vector<Evidence> listOfEvidence) override;

	bool repositoryHasEvidenceID(const std::string& evidenceID);
	void openFileInApplication() override;

	Evidence createEvidenceWithGivenAttributes(std::vector<std::string> listOfAttributes) const;
};