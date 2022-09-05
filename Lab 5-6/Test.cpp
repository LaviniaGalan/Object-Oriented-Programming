#include "Test.h"
#include <assert.h>
#include <string>


void GetSizeOfVector_ValidInput_ReturnsSize()
{
	DynamicVector<int> vectorForTest{};
	vectorForTest.addElement(2);
	vectorForTest.addElement(5);
	assert(vectorForTest.getSizeOfVector() == 2);
}

void GetElementFromIndex_ValidInput_ReturnsElement()
{
	DynamicVector<int> vectorForTest{};
	vectorForTest.addElement(1);
	vectorForTest.addElement(2);
	assert(vectorForTest.getElementFromIndex(0) == 1);
}

void FindEvidenceIndexByID_ValidInput_ReturnsIndex()
{
	Repository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	assert(repository.findEvidenceIndexByID("12sd23") == 0);
}

void FindEvidenceIndexByID_NonExistentID_ReturnsError()
{
	Repository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	assert(repository.findEvidenceIndexByID("12ssh23") == -1);
}

void AddEvidenceToRepository_ValidInput_EvidenceAdded()
{
	Repository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	assert(repository.addEvidenceToRepository(evidenceToBeAdded) == 0);
}

void AddEvidenceToRepository_DuplicateID_ReturnsError()
{
	Repository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	Evidence evidenceWithDuplicateID{ "12sd23", "12X10X16", 0.12, 5, "DSC6431.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	assert(repository.addEvidenceToRepository(evidenceWithDuplicateID) == -1);
}

void DeleteEvidenceFromRepository_ValidInput_EvidenceDeleted()
{
	Repository repository{};
	Evidence firstEvidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	Evidence secondEvidenceToBeAdded{ "13sf24", "12X10X16", 0.12, 5, "DSC6431.jpg" };
	repository.addEvidenceToRepository(firstEvidenceToBeAdded);
	repository.addEvidenceToRepository(secondEvidenceToBeAdded);
	assert(repository.deleteEvidenceFromRepository("12sd23") == 0);
}


void DeleteEvidenceFromRepository_NonExistentEvidence_ReturnsError()
{
	Repository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	assert(repository.deleteEvidenceFromRepository("12oh12") == -1);

}
void UpdateEvidenceInRepository_ValidInput_EvidenceUpdated()
{
	Repository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	Evidence newEvidence{ "12sd23", "12X10X16", 0.12, 5, "DSC6431.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	assert(repository.updateEvidenceInRepository(newEvidence) == 0);
	assert(repository.getAllEvidenceFromRepository().getElementFromIndex(0).getMeasurement() == "12X10X16");
}
void UpdateEvidenceInRepository_NonExistentEvidence_ReturnsError()
{
	Repository repository{};
	Evidence evidenceToBeAdded{ "12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg" };
	Evidence newEvidence{ "12ts18", "12X10X16", 0.12, 5, "DSC6431.jpg" };
	repository.addEvidenceToRepository(evidenceToBeAdded);
	assert(repository.updateEvidenceInRepository(newEvidence) == -1);
}





//---------------------------
void AddEvidence_ValidInput_EvidenceAdded()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	assert(service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg") == 0);
}
void AddEvidence_DuplicateID_ReturnsError()
{
	Repository repository{}; 
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
	assert(service.addEvidence("12sd23", "20X11X10", 0.15, 8, "DSC34441.jpg") == -1);
}
void DeleteEvidence_ValidInput_EvidenceDeleted()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
	assert(service.deleteEvidence("12sd23") == 0);
}
void DeleteEvidence_NonExistentEvidence_ReturnsError()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
	assert(service.deleteEvidence("12oh23") == -1);
}
void UpdateEvidence_ValidInput_EvidenceUpdated()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
	assert(service.updateEvidence("12sd23", "15X16X23", 0.21, 10, "DSC86587.jpg") == 0);
}
void UpdateEvidence_NonExistentEvidence_ReturnsError()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.addEvidence("12sd23", "23X12X10", 0.2452, 13, "DSC13241.jpg");
	assert(service.updateEvidence("12ds23", "15X16X23", 0.21, 10, "DSC86587.jpg") == -1);
}

void GetAccessMode_ValidInput_ReturnsAccessMode()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	assert(service.getAccessMode() == 'B');
}

void SetAccessMode_ValidInput_ModifiesAccesMode()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.setAccessMode('A');
	assert(service.getAccessMode() == 'A');
}

void GetNextEvidence_ValidInput_ReturnsNextEvidece()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.addEvidence("100", "12X13X14", 0.1, 13, "DSC455.png");
	service.addEvidence("200", "10X14X30", 0.21, 1, "DSC311.png");
	assert(service.getNextEvidence().getEvidenceID() == "100");
	assert(service.getNextEvidence().getEvidenceID() == "200");
	assert(service.getNextEvidence().getEvidenceID() == "100");
}

void GetNextEvidence_EmptyRepository_ThrowsException()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	try
	{
		service.getNextEvidence();
	}
	catch (std::length_error)
	{
		assert(true);
	}
}

void SaveEvidenceToUserDatabase_ValidInput_AddsEvidenceToUserDatabase()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.addEvidence("100", "12X13X14", 0.1, 13, "DSC455.png");
	assert(service.saveEvidenceToUserDatabase("100") == 0);
	assert(service.getAllPhysicalCopiesService().getSizeOfVector() == 1);

}

void SaveEvidenceToUserDatabase_InvalidID_ReturnsError()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	assert(service.saveEvidenceToUserDatabase("100") == -1);
}

void FilterByMeasurementAndQuantity_ValidInputNoMeasurement_FiltersListOfEvidence()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.addEvidence("100", "12X13X14", 0.1, 13, "DSC455.png");
	service.addEvidence("200", "10X14X30", 0.21, 13, "DSC311.png");
	assert(service.filterByMeasurementAndQuantity("", 13).getSizeOfVector() == 2);
}

void FilterByMeasurementAndQuantity_ValidInputWithMeasurement_FiltersListOfEvidence()
{
	Repository repository{};
	StandardUserDatabase userDatabase{};
	Service service{ repository, userDatabase };
	service.addEvidence("100", "12X13X14", 0.1, 13, "DSC455.png");
	service.addEvidence("200", "10X14X30", 0.21, 13, "DSC311.png");
	assert(service.filterByMeasurementAndQuantity("12X13X14", 13).getSizeOfVector() == 1);
}



void testsForDynamicVector()
{
	GetSizeOfVector_ValidInput_ReturnsSize();
	GetElementFromIndex_ValidInput_ReturnsElement();
}

void testsForRepository()
{
	AddEvidenceToRepository_ValidInput_EvidenceAdded();
	AddEvidenceToRepository_DuplicateID_ReturnsError();
	DeleteEvidenceFromRepository_ValidInput_EvidenceDeleted();
	DeleteEvidenceFromRepository_NonExistentEvidence_ReturnsError();
	UpdateEvidenceInRepository_ValidInput_EvidenceUpdated();
	UpdateEvidenceInRepository_NonExistentEvidence_ReturnsError();
	FindEvidenceIndexByID_ValidInput_ReturnsIndex();
	FindEvidenceIndexByID_NonExistentID_ReturnsError();
}

void testsForService()
{
	AddEvidence_ValidInput_EvidenceAdded();
	AddEvidence_DuplicateID_ReturnsError();
	DeleteEvidence_ValidInput_EvidenceDeleted();
	DeleteEvidence_NonExistentEvidence_ReturnsError();
	UpdateEvidence_ValidInput_EvidenceUpdated();
	UpdateEvidence_NonExistentEvidence_ReturnsError();
	GetAccessMode_ValidInput_ReturnsAccessMode();
	SetAccessMode_ValidInput_ModifiesAccesMode();
	GetNextEvidence_ValidInput_ReturnsNextEvidece();
	GetNextEvidence_EmptyRepository_ThrowsException();
	SaveEvidenceToUserDatabase_ValidInput_AddsEvidenceToUserDatabase();
	SaveEvidenceToUserDatabase_InvalidID_ReturnsError();
	FilterByMeasurementAndQuantity_ValidInputNoMeasurement_FiltersListOfEvidence();
	FilterByMeasurementAndQuantity_ValidInputWithMeasurement_FiltersListOfEvidence();
}

void runAllTests()
{
	testsForDynamicVector();
	testsForRepository();
	testsForService();
}

