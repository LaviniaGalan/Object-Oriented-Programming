#pragma once
class Test
{
public:
	void AddEvidenceToRepository_ValidInput_EvidenceAddedToList();
	void AddEvidenceToRepository_DuplicatedID_ThrowsException();
	void DeleteEvidenceFromRepository_ValidInput_EvidenceDeletedFromList();
	void DeleteEvidenceFromRepository_NonexistentID_ThrowsException();
	void UpdateEvidenceInRepository_ValidInput_EvidenceUpdated();
	void UpdateEvidenceInRepository_NonExistentEvidence_ThrowsException();
	void FindEvidenceIndexByID_ValidInput_ReturnsIndex();
	void FindEvidenceIndexByID_NonExistentID_ReturnsError();
	void runTestsMemoryRepository();

	void AddEvidenceToRepository_ValidInput_EvidenceAddedToFile();
	void AddEvidenceToRepository_IDExistentInTheFile_ThrowsException();
	void DeleteEvidenceFromRepository_ValidInput_EvidenceDeletedFromFile();
	void DeleteEvidenceFromRepository_NonexistentIDInFile_ThrowsException();
	void UpdateEvidenceInRepository_ValidInput_EvidenceUpdatedInFile();
	void UpdateEvidenceInRepository_NonExistentEvidenceInFile_ThrowsException();
	void FindEvidenceIndexByID_ValidInput_ReturnsIndexInFile();
	void FindEvidenceIndexByID_NonExistentIDInFile_ReturnsError();
	void runTestsFileRepository();

	void GetMeasurement_ValidInput_ReturnsMeasurementOfEvidence();
	void GetImageClarityLevel_ValidInput_ReturnsClarityLevelOfEvidence();
	void GetQuantity_ValidInput_ReturnsQuantityOfEvidence();
	void GetPhotograph_ValidInput_ReturnsPhotographOfEvidence();
	void EvidenceDataToString_ValidInput_ReturnsFormattedEvidence();
	void runTestsDomain();

	void AddEvidence_ValidInput_EvidenceAdded();
	void AddEvidence_DuplicateID_ThrowsException();
	void DeleteEvidence_ValidInput_EvidenceDeleted();
	void DeleteEvidence_NonExistentEvidence_ThrowsException();
	void UpdateEvidence_ValidInput_EvidenceUpdated();
	void UpdateEvidence_NonExistentEvidence_ThrowsException();
	void GetNextEvidence_ValidInput_ReturnsNextEvidence();
	void GetNextEvidence_EmptyRepository_ThrowsException();
	void SaveEvidenceToUserDatabase_ValidInput_AddsEvidenceToCSVUserDatabase();
	void SaveEvidenceToUserDatabase_ValidInput_AddsEvidenceToHTMLUserDatabase();
	void SaveEvidenceToUserDatabase_DuplicateID_ThrowsException();
	void FilterByMeasurementAndQuantity_ValidInputNoMeasurement_FiltersListOfEvidence();
	void FilterByMeasurementAndQuantity_ValidInputWithMeasurement_FiltersListOfEvidence();
	void runTestsService();

	void runAllTests();
};

