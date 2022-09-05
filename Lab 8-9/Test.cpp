#include "Test.h"
#include "Service.h"
#include <assert.h>

//--------- MemoryRepository
void Test::AddEvidenceToRepository_ValidInput_EvidenceAddedToList()
{
	MemoryRepository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	try
	{
		repository.addEvidenceToRepository(evidenceToBeAdded);
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::AddEvidenceToRepository_DuplicatedID_ThrowsException()
{
	MemoryRepository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	Evidence invalidEvidence{ "12sd23", "15X14X10", 0.34, 10, "DSC15741.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	try
	{
		repository.addEvidenceToRepository(invalidEvidence);
		assert(false);
	}
	catch (InvalidIDException)
	{
		assert(true);
	}
}

void Test::DeleteEvidenceFromRepository_ValidInput_EvidenceDeletedFromList()
{
	MemoryRepository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	try
	{
		repository.deleteEvidenceFromRepository("12sd23");
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::DeleteEvidenceFromRepository_NonexistentID_ThrowsException()
{
	MemoryRepository repository{};
	try
	{
		repository.deleteEvidenceFromRepository("12sd23");
		assert(false);
	}
	catch (InvalidIDException)
	{
		assert(true);
	}
}

void Test::UpdateEvidenceInRepository_ValidInput_EvidenceUpdated()
{
	MemoryRepository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	Evidence newEvidence{ "12sd23", "12X10X16", 0.12, 5, "DSC6431.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	try
	{
		repository.updateEvidenceInRepository(newEvidence);
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::UpdateEvidenceInRepository_NonExistentEvidence_ThrowsException()
{
	MemoryRepository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	Evidence newEvidence{ "12ts18", "12X10X16", 0.12, 5, "DSC6431.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	try
	{
		repository.updateEvidenceInRepository(newEvidence);
		assert(false);
	}
	catch (InvalidIDException)
	{
		assert(true);
	}
}

void Test::FindEvidenceIndexByID_ValidInput_ReturnsIndex()
{
	MemoryRepository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	assert(repository.findEvidenceIndexByID("12sd23") == 0);
}

void Test::FindEvidenceIndexByID_NonExistentID_ReturnsError()
{
	MemoryRepository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	assert(repository.findEvidenceIndexByID("12ssh23") == -1);
}

void Test::runTestsMemoryRepository()
{
	this->AddEvidenceToRepository_ValidInput_EvidenceAddedToList();
	this->AddEvidenceToRepository_DuplicatedID_ThrowsException();
	this->DeleteEvidenceFromRepository_ValidInput_EvidenceDeletedFromList();
	this->DeleteEvidenceFromRepository_NonexistentID_ThrowsException();
	this->UpdateEvidenceInRepository_ValidInput_EvidenceUpdated();
	this->UpdateEvidenceInRepository_NonExistentEvidence_ThrowsException();
	this->FindEvidenceIndexByID_ValidInput_ReturnsIndex();
	this->FindEvidenceIndexByID_NonExistentID_ReturnsError();

}

//-------- FileRepository
void Test::AddEvidenceToRepository_ValidInput_EvidenceAddedToFile()
{
	FileRepository repository{ "TestFile.txt" };
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	try
	{
		repository.addEvidenceToRepository(evidenceToBeAdded);
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
	repository.deleteEvidenceFromRepository("12sd23");
}


void Test::AddEvidenceToRepository_IDExistentInTheFile_ThrowsException()
{
	FileRepository repository{ "TestFile.txt" };
	std::vector<Evidence> listOfEvidence = repository.getAllEvidenceFromRepository();
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	Evidence invalidEvidence{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	try
	{
		repository.addEvidenceToRepository(invalidEvidence);
		assert(false);
	}
	catch (InvalidIDException)
	{
		assert(true);
	}
	repository.deleteEvidenceFromRepository("12sd23");
}

void Test::DeleteEvidenceFromRepository_ValidInput_EvidenceDeletedFromFile()
{
	FileRepository repository{ "TestFile.txt" };
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	try
	{
		repository.deleteEvidenceFromRepository("12sd23");
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::DeleteEvidenceFromRepository_NonexistentIDInFile_ThrowsException()
{
	FileRepository repository{ "TestFile.txt" };
	try
	{
		repository.deleteEvidenceFromRepository("dummyID");
		assert(false);
	}
	catch (InvalidIDException)
	{
		assert(true);
	}
}

void Test::UpdateEvidenceInRepository_ValidInput_EvidenceUpdatedInFile()
{
	FileRepository repository{ "TestFile.txt" };
	Evidence evidenceToBeAdded{ "105", "12X30X40", 0.23, 13, "abcd.png" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	Evidence updatedEvidence{ "105", "20X20X20", 0.6, 10, "new.png" };
	try
	{	
		repository.updateEvidenceInRepository(updatedEvidence);
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
	repository.deleteEvidenceFromRepository("105");
}

void Test::UpdateEvidenceInRepository_NonExistentEvidenceInFile_ThrowsException()
{
	FileRepository repository{ "TestFile.txt" };
	repository.deleteEvidenceFromRepository("105");
	Evidence updatedEvidence{ "105", "20X20X20", 0.6, 10, "new.png" };
	try
	{
		repository.updateEvidenceInRepository(updatedEvidence);
		assert(false);
	}
	catch (InvalidIDException)
	{
		assert(true);
	}
}


void Test::FindEvidenceIndexByID_ValidInput_ReturnsIndexInFile()
{
	FileRepository repository{ "TestFile.txt" };
	Evidence evidenceToBeAdded{ "105", "20X20X20", 0.6, 10, "new.png" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	assert(repository.findEvidenceIndexByID("105") != -1);
	repository.deleteEvidenceFromRepository("105");
}

void Test::FindEvidenceIndexByID_NonExistentIDInFile_ReturnsError()
{
	FileRepository repository{ "TestFile.txt" };
	repository.deleteEvidenceFromRepository("105");
	assert(repository.findEvidenceIndexByID("105") == -1);
}


void Test::runTestsFileRepository()
{
	this->AddEvidenceToRepository_ValidInput_EvidenceAddedToFile();
	this->AddEvidenceToRepository_IDExistentInTheFile_ThrowsException();
	this->DeleteEvidenceFromRepository_ValidInput_EvidenceDeletedFromFile();
	this->DeleteEvidenceFromRepository_NonexistentIDInFile_ThrowsException();
	this->UpdateEvidenceInRepository_ValidInput_EvidenceUpdatedInFile();
	this->UpdateEvidenceInRepository_NonExistentEvidenceInFile_ThrowsException();
	this->FindEvidenceIndexByID_ValidInput_ReturnsIndexInFile();
	this->FindEvidenceIndexByID_NonExistentIDInFile_ReturnsError();
}

//---------Domain

void Test::GetMeasurement_ValidInput_ReturnsMeasurementOfEvidence()
{
	Evidence newEvidence{ "105", "20X20X20", 0.6, 10, "new.png" };
	assert(newEvidence.getMeasurement() == "20X20X20");
}

void Test::GetImageClarityLevel_ValidInput_ReturnsClarityLevelOfEvidence()
{
	Evidence newEvidence{ "105", "20X20X20", 0.6, 10, "new.png" };
	assert(newEvidence.getImageClarityLevel() == 0.6);
}

void Test::GetQuantity_ValidInput_ReturnsQuantityOfEvidence()
{
	Evidence newEvidence{ "105", "20X20X20", 0.6, 10, "new.png" };
	assert(newEvidence.getQuantity() == 10);
}

void Test::GetPhotograph_ValidInput_ReturnsPhotographOfEvidence()
{
	Evidence newEvidence{ "105", "20X20X20", 0.6, 10, "new.png" };
	assert(newEvidence.getPhotograph() == "new.png");
}

void Test::EvidenceDataToString_ValidInput_ReturnsFormattedEvidence()
{
	Evidence newEvidence{ "105", "20X20X20", 0.6, 10, "new.png" };
	assert(newEvidence.evidenceDataToString() == "105 - 20X20X20 - 0.600000 - 10 - new.png");

}

void Test::runTestsDomain()
{
	this->GetMeasurement_ValidInput_ReturnsMeasurementOfEvidence();
	this->GetImageClarityLevel_ValidInput_ReturnsClarityLevelOfEvidence();
	this->GetQuantity_ValidInput_ReturnsQuantityOfEvidence();
	this->GetPhotograph_ValidInput_ReturnsPhotographOfEvidence();
	this->EvidenceDataToString_ValidInput_ReturnsFormattedEvidence();
}


//--------Service

void Test::AddEvidence_ValidInput_EvidenceAdded()
{
	Service service{ nullptr, nullptr };
	service.setMemoryRepository();
	try
	{
		service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::AddEvidence_DuplicateID_ThrowsException()
{
	Service service{ nullptr, nullptr };
	service.setMemoryRepository();
	service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
	try
	{
		service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::DeleteEvidence_ValidInput_EvidenceDeleted()
{
	Service service{ nullptr, nullptr };
	service.setMemoryRepository();
	service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
	try
	{
		service.deleteEvidence("12sd23");
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::DeleteEvidence_NonExistentEvidence_ThrowsException()
{
	Service service{ nullptr, nullptr };
	service.setMemoryRepository();
	try
	{
		service.deleteEvidence("12sd23");
		assert(false);
	}
	catch (InvalidIDException)
	{
		assert(true);
	}
}

void Test::UpdateEvidence_ValidInput_EvidenceUpdated()
{
	Service service{ nullptr, nullptr };
	service.setMemoryRepository();
	service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
	try
	{
		service.updateEvidence("12sd23", "15X16X23", 0.21, 10, "DSC86587.jpg");
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::UpdateEvidence_NonExistentEvidence_ThrowsException()
{
	Service service{ nullptr, nullptr };
	service.setMemoryRepository(); 
	try
	{
		service.updateEvidence("12sd23", "15X16X23", 0.21, 10, "DSC86587.jpg");
		assert(false);
	}
	catch (InvalidIDException)
	{
		assert(true);
	}
}

void Test::GetNextEvidence_ValidInput_ReturnsNextEvidence()
{
	Service service{ nullptr, nullptr };
	service.setFileRepository("TestFile.txt");
	service.addEvidence("200", "10X14X30", 0.21, 1, "DSC311.png");
	assert(service.getNextEvidence().getEvidenceID() == "100");
	assert(service.getNextEvidence().getEvidenceID() == "200");
	assert(service.getNextEvidence().getEvidenceID() == "100");
	service.deleteEvidence("200");
}

void Test::GetNextEvidence_EmptyRepository_ThrowsException()
{
	Service service{ nullptr, nullptr };
	service.setFileRepository("EmptyFileTest.txt");
	try
	{
		service.getNextEvidence();
	}
	catch (std::length_error)
	{
		assert(true);
	}
}

void Test::SaveEvidenceToUserDatabase_ValidInput_AddsEvidenceToCSVUserDatabase()
{
	Service service{ nullptr, nullptr };
	service.setStandardUserDatabase("TestEvidence.csv");
	service.setMemoryRepository();
	service.addEvidence("12sd23", "12X13X14", 0.1, 13, "DSC455.png");
	try
	{
		service.saveEvidenceToUserDatabase("12sd23");
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::SaveEvidenceToUserDatabase_ValidInput_AddsEvidenceToHTMLUserDatabase()
{
	Service service{ nullptr, nullptr };
	service.setStandardUserDatabase("TestEvidence.html");
	service.setMemoryRepository();
	service.addEvidence("12sd23", "12X13X14", 0.1, 13, "DSC455.png");
	try
	{
		service.saveEvidenceToUserDatabase("12sd23");
		assert(true);
	}
	catch (InvalidIDException)
	{
		assert(false);
	}
}

void Test::SaveEvidenceToUserDatabase_DuplicateID_ThrowsException()
{
	Service service{ nullptr, nullptr };
	service.setStandardUserDatabase("TestEvidence.csv");
	service.setMemoryRepository();
	service.addEvidence("12sd23", "12X13X14", 0.1, 13, "DSC455.png");
	service.saveEvidenceToUserDatabase("12sd23");
	try
	{
		service.saveEvidenceToUserDatabase("12sd23");
		assert(false);
	}
	catch (DuplicateIDException)
	{
		assert(true);
	}
}

void Test::FilterByMeasurementAndQuantity_ValidInputNoMeasurement_FiltersListOfEvidence()
{
	Service service{ nullptr, nullptr };
	service.setMemoryRepository();
	service.addEvidence("12sd23", "12X13X14", 0.1, 13, "DSC455.png");
	service.addEvidence("11pm45", "10X14X30", 0.21, 13, "DSC311.png");
	assert(service.filterByMeasurementAndQuantity("", 13).size() == 2);
}

void Test::FilterByMeasurementAndQuantity_ValidInputWithMeasurement_FiltersListOfEvidence()
{
	Service service{ nullptr, nullptr };
	service.setMemoryRepository();
	service.addEvidence("12sd23", "12X13X14", 0.1, 13, "DSC455.png");
	service.addEvidence("11pm45", "10X14X30", 0.21, 13, "DSC311.png");
	assert(service.filterByMeasurementAndQuantity("12X13X14", 13).size() == 1);
}

void Test::runTestsService()
{
	this->AddEvidence_ValidInput_EvidenceAdded();
	this->AddEvidence_DuplicateID_ThrowsException();
	this->DeleteEvidence_ValidInput_EvidenceDeleted();
	this->DeleteEvidence_NonExistentEvidence_ThrowsException();
	this->UpdateEvidence_ValidInput_EvidenceUpdated();
	this->UpdateEvidence_NonExistentEvidence_ThrowsException();
	this->GetNextEvidence_ValidInput_ReturnsNextEvidence();
	this->GetNextEvidence_EmptyRepository_ThrowsException();
	this->SaveEvidenceToUserDatabase_ValidInput_AddsEvidenceToCSVUserDatabase();
	this->SaveEvidenceToUserDatabase_ValidInput_AddsEvidenceToHTMLUserDatabase();
	this->SaveEvidenceToUserDatabase_DuplicateID_ThrowsException();
	this->FilterByMeasurementAndQuantity_ValidInputNoMeasurement_FiltersListOfEvidence();
	this->FilterByMeasurementAndQuantity_ValidInputWithMeasurement_FiltersListOfEvidence();
}


//--------AllTests
void Test::runAllTests()
{
	this->runTestsDomain();
	this->runTestsFileRepository();
	this->runTestsMemoryRepository();
	this->runTestsService();
}