#pragma once
#include <vector>
#include "Domain.h"
#include "Exception.h"
#include "Validator.h"

class Repository
{
public:
	virtual void addEvidenceToRepository(const Evidence& evidenceToBeAdded) = 0;


	virtual int findEvidenceIndexByID(std::string evidenceID) = 0;


	virtual void deleteEvidenceFromRepository(std::string evidenceID) = 0;
	

	virtual void updateEvidenceInRepository(const Evidence& newEvidence) = 0;
	

	virtual std::vector<Evidence> getAllEvidenceFromRepository() const = 0;
	

	virtual ~Repository() {};

};


