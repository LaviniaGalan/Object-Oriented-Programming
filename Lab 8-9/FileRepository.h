#pragma once
#include "Repository.h"

class FileRepository : public Repository
{
private:
	std::string fileName;
public:
	FileRepository(const std::string& fileName = "");

	void addEvidenceToRepository(const Evidence& evidenceToBeAdded) override;

	int findEvidenceIndexByID(std::string evidenceID) override;

	void deleteEvidenceFromRepository(std::string evidenceID) override;

	void updateEvidenceInRepository(const Evidence& newEvidence) override;

	std::vector<Evidence> getAllEvidenceFromRepository() const override;

	void writeListOfEvidenceToFile(std::vector<Evidence> listOfEvidence);

	std::string getFileName();
};