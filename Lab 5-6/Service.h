#pragma once
#include "Repository.h"
#include "StandardUserDatabase.h"
class Service
{
private:
	Repository& repository;
	StandardUserDatabase& standardUserDatabase;
	char accessMode;

public:

	static int indexOfNextEvidenceToBeDisplayed; 

	Service(Repository& repository, StandardUserDatabase& userDatabase) : repository{ repository }, standardUserDatabase{ userDatabase }, accessMode{ 'B' } {}

	int addEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph);

	DynamicVector<Evidence> getAllEvidenceService();

	int deleteEvidence(const std::string& evidenceID);

	int updateEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph);

	char getAccessMode();

	void setAccessMode(char accessMode);

	DynamicVector<Evidence> getAllPhysicalCopiesService();

	Evidence getNextEvidence();

	Evidence getNextEvidenceWithIterator();

	int saveEvidenceToUserDatabase(const std::string& evidenceID);

	DynamicVector<Evidence> filterByMeasurementAndQuantity(const std::string& measurement, const int quantity);
};

