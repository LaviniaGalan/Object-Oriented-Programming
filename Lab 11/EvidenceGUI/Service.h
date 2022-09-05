#pragma once
#include "MemoryRepository.h"
#include "FileRepository.h"
#include "Action.h"
#include "Observer.h"
#include <memory>

#define DIMENSION_OF_EXTENSION 4

class Service : public Observable
{
private:
	Repository* repository;
	Repository* standardUserDatabase;
	char accessMode;
	std::vector<std::unique_ptr<Action>> undoStack;
	std::vector<std::unique_ptr<Action>> redoStack;

	std::vector<std::unique_ptr<Action>> mylistUndoStack;
	std::vector<std::unique_ptr<Action>> mylistRedoStack;
public:

	static int indexOfNextEvidenceToBeDisplayed;

	Service(Repository* repository, Repository* userDatabase) : repository{ repository }, standardUserDatabase{ userDatabase }, accessMode{ 'B' } {}

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

	void setFileStandardUserDatabase(std::string fileName);
	void setMemoryStandardUserDatabase();

	void openDataInApplication();

	void undo();
	void redo();

	void mylistUndo();
	void mylistRedo();

	~Service();
};
