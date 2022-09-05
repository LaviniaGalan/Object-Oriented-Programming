#pragma once
#include "Domain.h"
#include "DynamicVector.h"
class StandardUserDatabase
{
private:
	DynamicVector<Evidence> listOfPhysicalCopies;
public:
	StandardUserDatabase() {}

	void saveEvidenceToDatabase(const Evidence& evidenceToBeAdded);

	DynamicVector<Evidence> getAllEvidencesFromUserDatabase();

};


