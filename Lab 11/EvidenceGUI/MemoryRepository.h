#pragma once
#include "Repository.h"

class MemoryRepository : public Repository
{
private:
	std::vector<Evidence> listOfEvidences;
public:
	MemoryRepository();

	void addEvidenceToRepository(const Evidence& evidenceToBeAdded) override;

	int findEvidenceIndexByID(std::string evidenceID) override;

	void deleteEvidenceFromRepository(std::string evidenceID) override;

	void updateEvidenceInRepository(const Evidence& newEvidence) override;

	std::vector<Evidence> getAllEvidenceFromRepository() const override;

	void openFileInApplication() override;

	Evidence findEvidenceByID(std::string evidenceID) override;
};