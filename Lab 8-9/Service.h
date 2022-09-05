#pragma once
#include "MemoryRepository.h"
#include "FileRepository.h"
#include "StandardUserDatabase.h"

#define DIMENSION_OF_EXTENSION 4

class Service
{
private:
	Repository* repository;
	StandardUserDatabase* standardUserDatabase;
	char accessMode;

public:

	static int indexOfNextEvidenceToBeDisplayed;

	Service(Repository* repository, StandardUserDatabase* userDatabase) : repository{ repository }, standardUserDatabase{ userDatabase }, accessMode{ 'B' } {}

	void addEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph);

	std::vector<Evidence> getAllEvidenceService();

	void deleteEvidence(const std::string& evidenceID);

	void updateEvidence(const std::string& evidenceID, const std::string& measurement, double imageClarityLevel, int quantity, const std::string& photograph);

	char getAccessMode();

	void setAccessMode(char accessMode);

	std::vector<Evidence> getAllPhysicalCopiesService();

	Evidence getNextEvidence();

	void saveEvidenceToUserDatabase(const std::string& evidenceID);

	std::vector<Evidence> filterByMeasurementAndQuantity(const std::string& measurement, const int quantity);

	void setFileRepository(std::string fileName);

	void setMemoryRepository();

	void setStandardUserDatabase(std::string fileName);

	void openDataInApplication();

	~Service();
};
