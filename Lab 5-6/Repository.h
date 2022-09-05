#pragma once
#include "DynamicVector.h"
#include "Domain.h"

class Repository
{
private:
	DynamicVector<Evidence> listOfEvidences;
	DynamicVector<Evidence>::iterator iteratorOfListOfEvidences;
public:
	Repository();

	int addEvidenceToRepository(const Evidence& evidenceToBeAdded);

	int findEvidenceIndexByID(std::string evidenceID);

	int deleteEvidenceFromRepository(std::string evidenceID);

	int updateEvidenceInRepository(const Evidence& evidenceToBeAdded);

	DynamicVector<Evidence> getAllEvidenceFromRepository() const;

	Evidence getNextEvidence();

};
