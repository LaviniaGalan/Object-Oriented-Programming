#include "StandardUserDatabase.h"

void StandardUserDatabase::saveEvidenceToDatabase(const Evidence& evidenceToBeAdded)
{
	this->listOfPhysicalCopies.addElement(evidenceToBeAdded);
}

DynamicVector<Evidence> StandardUserDatabase::getAllEvidencesFromUserDatabase()
{
	return this->listOfPhysicalCopies;
}
