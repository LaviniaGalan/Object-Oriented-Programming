#include "Test.h"
//#include "Domain.h"
//#include "Repository.h"
#include "UI.h"
#include <assert.h>
#include <string.h>

// Test Domain ----------------------------------------------------------------------------------------------
void CreateProfile_ValidInput_ProfileCreated()
{
	SheriffWorkersProfile* createdProfile = createProfile(1, "New York", "normal pattern", 5);
	assert(getProfileIdNumber(createdProfile) == 1);
	assert(strcmp(getPlaceOfBirth(createdProfile), "New York") == 0);
	assert(strcmp(getPsychologicalProfile(createdProfile), "normal pattern") == 0);
	assert(getYearsOfRecordedService(createdProfile) == 5);

	destroySheriffWorkersProfile(createdProfile);
}

void MakeCopyOfProfile_ValidInput_aCopyIsMade()
{
	SheriffWorkersProfile* createdProfile = createProfile(1, "New York", "normal pattern", 5);
	SheriffWorkersProfile* copiedProfile;
	copiedProfile = makeCopyOfProfile(createdProfile);
	assert(getProfileIdNumber(copiedProfile) == 1);
	assert(strcmp(getPlaceOfBirth(copiedProfile), "New York") == 0);
	assert(strcmp(getPsychologicalProfile(copiedProfile), "normal pattern") == 0);
	assert(getYearsOfRecordedService(copiedProfile) == 5);

	//check if the original profile and the copied one have not the same adress
	assert(copiedProfile != createdProfile);

	destroySheriffWorkersProfile(copiedProfile);
	destroySheriffWorkersProfile(createdProfile);
}

// Test Repository ------------------------------------------------------------------------------------------

void RepoHasGivenProfile_ValidInput_Returns1()
{
	Repository* repository = createRepository();
	SheriffWorkersProfile* profile = createProfile(1, "New York", "normal pattern", 5);
	addProfileToRepository(repository, profile);
	assert(repoHasGivenProfile(repository, profile) == 1);

	destroyRepository(repository);
}

void RepoHasGivenProfile_InvalidInput_Returns0()
{
	Repository* repository = createRepository();
	SheriffWorkersProfile* profile = createProfile(1, "New York", "normal pattern", 5);
	assert(repoHasGivenProfile(repository, profile) == 0);

	destroyRepository(repository);
}

void FindProfileIndexByIdNumber_ValidInput_ReturnsIndex()
{
	Repository* repository = createRepository();
	SheriffWorkersProfile* profile1ToBeAdded = createProfile(1, "New York", "normal pattern", 5);
	SheriffWorkersProfile* profile2ToBeAdded = createProfile(2, "Los Angeles", "psycho pattern", 1);
	addProfileToRepository(repository, profile1ToBeAdded);
	addProfileToRepository(repository, profile2ToBeAdded);

	assert(findProfileIndexByIdNumber(repository, 2) == 1);
	destroyRepository(repository);
}

void FindProfileIndexByIdNumber_InvalidInput_ReturnsError()
{
	Repository* repository = createRepository();
	SheriffWorkersProfile* profileToBeAdded = createProfile(1, "New York", "normal pattern", 5);
	addProfileToRepository(repository, profileToBeAdded);

	assert(findProfileIndexByIdNumber(repository, 3) == -1);
	destroyRepository(repository);
}

void AddProfileToRepository_ValidInput_ProfileAdded()
{
	Repository* repository = createRepository();
	SheriffWorkersProfile* profileToBeAdded = createProfile(1, "New York", "normal pattern", 5);
	assert(addProfileToRepository(repository, profileToBeAdded) == 0);
	assert(getLengthOfContainer(repository->profilesData) == 1);

	
	destroyRepository(repository);
}

void AddProfileToRepository_InvalidInput_ReturnError()
{
	Repository* repository = createRepository();
	SheriffWorkersProfile* profileToBeAdded = createProfile(1, "New York", "normal pattern", 5);
	addProfileToRepository(repository, profileToBeAdded);
	SheriffWorkersProfile* invalidProfile = createProfile(1, "Los Angeles", "psycho pattern", 1);
	assert(addProfileToRepository(repository, invalidProfile) == -1);
	assert(getLengthOfContainer(repository->profilesData) == 1);


	destroyRepository(repository);
	
}

void DeleteProfileFromRepository_ValidInput_ProfileDeleted()
{
	Repository* repository = createRepository();
	SheriffWorkersProfile* profileToBeAddedThenDeleted = createProfile(1, "New York", "normal pattern", 5);
	addProfileToRepository(repository, profileToBeAddedThenDeleted);

	assert(deleteProfileFromRepository(repository, 1) == 0);
	assert(getLengthOfContainer(repository->profilesData) == 0);

	//destroySheriffWorkersProfile(profileToBeAddedThenDeleted);
	destroyRepository(repository);
}

void DeleteProfileFromRepository_InvalidInput_ReturnsError()
{
	Repository* repository = createRepository();

	assert(deleteProfileFromRepository(repository, 1) == -1);
	assert(getLengthOfContainer(repository->profilesData) == 0);

	destroyRepository(repository);
}

void GetAllMatchingPsychologicalProfilesFromRepository_ValidInput_ReturnsContainerOfMatchingProfiles()
{
	Repository* repository = createRepository();
	SheriffWorkersProfile* profile1ToBeAdded = createProfile(1, "New York", "normal pattern", 5);
	SheriffWorkersProfile* profile2ToBeAdded = createProfile(2, "Los Angeles", "psycho pattern", 1);
	addProfileToRepository(repository, profile1ToBeAdded);
	addProfileToRepository(repository, profile2ToBeAdded);

	Container* allMatchingProfiles = getAllMatchingPsychologicalProfilesFromRepository(repository, "normal pattern");
	assert(getLengthOfContainer(allMatchingProfiles) == 1);

	destroyAuxiliaryContainer(allMatchingProfiles);
	destroyRepository(repository);
}

void GetAllMatchingProfilesMaximumYearsOfServiceFromRepository_ValidInput_ReturnsContainerOfMatchingProfiles()
{
	Repository* repository = createRepository();
	SheriffWorkersProfile* profile1ToBeAdded = createProfile(1, "New York", "normal pattern", 5);
	SheriffWorkersProfile* profile2ToBeAdded = createProfile(2, "Los Angeles", "psycho pattern", 1);
	addProfileToRepository(repository, profile1ToBeAdded);
	addProfileToRepository(repository, profile2ToBeAdded);

	Container* allMatchingProfiles = getAllMatchingProfilesMaximumYearsOfServiceFromRepository(repository, 3);
	assert(getLengthOfContainer(allMatchingProfiles) == 1);
	
	destroyAuxiliaryContainer(allMatchingProfiles);
	destroyRepository(repository);
}

// Test Service -------------------------------------------------------------------------------------------------

void AddProfileService_ValidInput_Returns0()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	assert(addProfileService(service, 1, "New York", "normal pattern", 5) == 0);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 1);
	destroyService(service);
}

void AddProfileService_InvalidInput_ReturnsError()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	assert(addProfileService(service, 1, "Los Angeles", "psycho pattern", 1) == -1);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 1);
	destroyService(service);
}

void DeleteProfileService_ValidInput_Returns0()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	assert(deleteProfileService(service, 1) == 0);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 0);
	destroyService(service);
}

void DeleteProfileService_InvalidInput_ReturnsError()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	assert(deleteProfileService(service, 2) == -1);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 1);
	destroyService(service);
}

void UpdateProfileService_ValidInput_Returns0()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	assert(updateProfileService(service, 1, "Old York", "psycho pattern", 2) == 0);
	assert(getProfileIdNumber(getElementFromGivenIndex(getAllProfilesFromRepository(service->repository), 0)) == 1);
	assert(strcmp(getPlaceOfBirth(getElementFromGivenIndex(getAllProfilesFromRepository(service->repository), 0)), "Old York") == 0);

	destroyService(service);
}

void UpdateProfileService_InvalidInput_ReturnsError()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	assert(updateProfileService(service, 2, "Old York", "psycho pattern", 2) == -1);
	assert(strcmp(getPlaceOfBirth(getElementFromGivenIndex(getAllProfilesFromRepository(service->repository), 0)), "New York") == 0);

	destroyService(service);
}

void ComparatorForPlaceOfBirth_ValidInput_ReturnsOrderOfPlacesOfBirth()
{
	SheriffWorkersProfile* firstProfile = createProfile(1, "New York", "normal", 5);
	SheriffWorkersProfile* secondProfile = createProfile(2, "Los Angeles", "normal", 2);
	SheriffWorkersProfile* thirdProfile = createProfile(3, "New York", "psycho", 3);

	assert(comparatorForPlaceOfBirth(firstProfile, secondProfile) == -1);
	assert(comparatorForPlaceOfBirth(firstProfile, thirdProfile) == 0);
	assert(comparatorForPlaceOfBirth(secondProfile, thirdProfile) == 1);
}

void SortProfiles_ValidInput_ReturnsContainerWithSortedProfiles()
{
	SheriffWorkersProfile* firstAddedProfile = createProfile(1, "New York", "normal pattern", 5);
	SheriffWorkersProfile* secondAddedProfile = createProfile(2, "Washington", "idk", 4);
	SheriffWorkersProfile* thirdAddedProfile = createProfile(3, "Las Vegas", "smart pattern", 3);

	Container* profilesToBeSorted = createDynamicContainer(4);
	addElement(profilesToBeSorted, firstAddedProfile);
	addElement(profilesToBeSorted, secondAddedProfile);
	addElement(profilesToBeSorted, thirdAddedProfile);

	Container* sortedProfiles;
	sortedProfiles = sortProfiles(profilesToBeSorted, &comparatorForPlaceOfBirth, 1);

	assert(getProfileIdNumber(getElementFromGivenIndex(sortedProfiles, 0)) == 3);
	assert(getProfileIdNumber(getElementFromGivenIndex(sortedProfiles, 1)) == 1);
	assert(getProfileIdNumber(getElementFromGivenIndex(sortedProfiles, 2)) == 2);

	destroyAuxiliaryContainer(sortedProfiles);
}

void UndoService_ValidInputForAdding_UndoesTheAdding()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	assert(undoService(service) == 1);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 0);

	destroyService(service);
}


void UndoService_ValidInputForUpdating_UndoesTheUpdate()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "Old York", "normal pattern", 5);
	updateProfileService(service, 1, "New York", "updated pattern", 2);
	assert(undoService(service) == 1);
	assert(strcmp(getPlaceOfBirth(getElementFromGivenIndex(getAllProfilesFromRepository(service->repository), 0)), "Old York") == 0);

	destroyService(service);
}

void UndoService_ValidInputForDeleting_UndoesTheDeletion()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	deleteProfileService(service, 1);
	assert(undoService(service) == 1);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 1);

	destroyService(service);
}

void UndoService_InvalidInput_ReturnsError()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	assert(undoService(service) == 0);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 0);

	destroyService(service);
}


void RedoService_ValidInputForAddingAndUndo_RedoesTheAdding()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	undoService(service);
	assert(redoService(service) == 1);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 1);

	destroyService(service);
}


void RedoService_ValidInputForDeletingAndUndo_RedoesTheDeletion()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	deleteProfileService(service, 1);
	undoService(service);
	assert(redoService(service) == 1);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 0);

	destroyService(service);
}

void RedoService_ValidInputForUpdatingAndUndo_RedoesTheUpdate()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "Old York", "normal pattern", 5);
	updateProfileService(service, 1, "New York", "updated pattern", 2);
	undoService(service);
	assert(redoService(service) == 1);
	assert(strcmp(getPlaceOfBirth(getElementFromGivenIndex(getAllProfilesFromRepository(service->repository), 0)), "New York") == 0);

	destroyService(service);
}

void RedoService_InvalidInput_ReturnsError()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	assert(redoService(service) == 0);
	assert(getLengthOfContainer(getAllProfilesFromRepository(service->repository)) == 1);

	destroyService(service);
}

void GetAllMatchingPsychologicalProfilesService_ValidInput_ReturnsContainerOfMatchingProfiles()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	addProfileService(service, 2, "Los Angeles", "psycho pattern", 1);
	addProfileService(service, 3, "Las Vegas", "psycho pattern", 2);

	Container* allMatchingProfiles = getAllMatchingPsychologicalProfilesService(service, "psycho pattern");
	assert(getLengthOfContainer(allMatchingProfiles) == 2);

	destroyAuxiliaryContainer(allMatchingProfiles);
	destroyService(service);
}

void GetAllMatchingProfilesMaximumYearsOfServiceSorted_ValidInput_ReturnsContainerOfMatchingProfiles()
{
	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);

	addProfileService(service, 1, "New York", "normal pattern", 5);
	addProfileService(service, 2, "Los Angeles", "psycho pattern", 1);

	Container* allMatchingProfiles = getAllMatchingProfilesMaximumYearsOfServiceSorted(service, 2);
	assert(getLengthOfContainer(allMatchingProfiles) == 1);

	allMatchingProfiles = getAllMatchingProfilesMaximumYearsOfServiceSorted(service, 7);
	assert(getLengthOfContainer(allMatchingProfiles) == 2);

	destroyAuxiliaryContainer(allMatchingProfiles);
	destroyRepository(repository);
}


//Test Operation Stack --------------------------------------------------------------------------------------

void CreateOperation_ValidInput_OperationCreated()
{
	SheriffWorkersProfile* profile = createProfile(1, "New York", "normal", 5);
	OperationOnProfiles* newOperation = createOperation(profile, "add");

	assert(strcmp(getOperationType(newOperation), "add") == 0);
	assert(getOperationProfile(newOperation) != profile);

	destroySheriffWorkersProfile(profile);
	destroyOperation(newOperation);
}

void CopyOperation_ValidInput_CreatesACopyOfTheOperation()
{
	SheriffWorkersProfile* profileOfOperation = createProfile(1, "New York", "normal pattern", 5);
	OperationOnProfiles* operation = createOperation(profileOfOperation, "add");
	OperationOnProfiles* copyOfOperation = copyOperation(operation);

	assert(operation != copyOfOperation);

	assert(strcmp(getOperationType(copyOfOperation), "add") == 0);
	assert(getOperationProfile(operation) != getOperationProfile(copyOfOperation));

	destroySheriffWorkersProfile(profileOfOperation);
	destroyOperation(operation);
	destroyOperation(copyOfOperation);

}

void StackIsEmpty_ValidInput_Returns1()
{
	OperationsStack* operationsStack = createOperationsStack();
	assert(stackIsEmpty(operationsStack) == 1);
	destroyOperationsStack(operationsStack);
}

void StackIsEmpty_InvalidInput_Returns0()
{
	SheriffWorkersProfile* profileOfOperation = createProfile(1, "New York", "normal pattern", 5);
	OperationOnProfiles* operation = createOperation(profileOfOperation, "add");

	OperationsStack* operationsStack = createOperationsStack();
	pushOperationOnStack(operationsStack, operation);
	destroyOperation(operation);

	assert(stackIsEmpty(operationsStack) == 0);
	destroyOperationsStack(operationsStack);
}

void StackIsFull_InvalidInput_Returns0()
{
	SheriffWorkersProfile* profileOfOperation = createProfile(1, "New York", "normal pattern", 5);
	OperationOnProfiles* operation = createOperation(profileOfOperation, "add");

	OperationsStack* operationsStack = createOperationsStack();
	pushOperationOnStack(operationsStack, operation);
	destroyOperation(operation);

	assert(stackIsFull(operationsStack) == 0);
	destroyOperationsStack(operationsStack);
}

void PopOperationFromStack_ValidInput_ReturnsOperation()
{
	SheriffWorkersProfile* profileOfOperation = createProfile(1, "New York", "normal pattern", 5);
	OperationOnProfiles* operation = createOperation(profileOfOperation, "add");

	OperationsStack* operationsStack = createOperationsStack();
	pushOperationOnStack(operationsStack, operation);
	destroyOperation(operation);

	OperationOnProfiles* popedOperation = popOperationFromStack(operationsStack);
	assert(strcmp(getOperationType(popedOperation), "add") == 0);
	assert(getProfileIdNumber(getOperationProfile(popedOperation)) == 1);

	destroyOperation(popedOperation);
	destroyOperationsStack(operationsStack);

}

void PopOperationFromStack_InvalidInput_ReturnsNULL()
{
	OperationsStack* operationsStack = createOperationsStack();

	OperationOnProfiles* popedOperation = popOperationFromStack(operationsStack);
	assert(popedOperation == NULL);

	destroyOperationsStack(operationsStack);
}


// Test DynamicContainer ------------------------------------------------------------------------------------
void CreateDynamicContainer_ValidInput_CreatesContainer()
{
	Container* newContainer = createDynamicContainer(2);

	assert(newContainer->capacityOfContainer == 2);
	assert(newContainer->lengthOfContainer == 0);

	destroyContainer(newContainer);
}

void ResizeContainer_ValidInput_ResizesTheContainer()
{
	Container* newContainer = createDynamicContainer(1);

	SheriffWorkersProfile* profileToBeAdded = createProfile(1, "New York", "normal", 5);
	addElement(newContainer, profileToBeAdded);

	SheriffWorkersProfile* newProfileToBeAdded = createProfile(2, "New York", "normal", 5);
	addElement(newContainer, newProfileToBeAdded);
	assert(newContainer->capacityOfContainer == 2);
	assert(newContainer->lengthOfContainer == 2);

	destroyContainer(newContainer);
}

void GetElementFromGivenIndex_ValidInput_ReturnsTheElement()
{
	Container* newContainer = createDynamicContainer(4);

	SheriffWorkersProfile* profileToBeAdded = createProfile(1, "New York", "normal", 5);
	addElement(newContainer, profileToBeAdded);

	assert(getElementFromGivenIndex(newContainer, 0) == profileToBeAdded);
	destroyContainer(newContainer);
}

void GetElementFromGivenIndex_InvalidInput_ReturnsNULL()
{
	Container* newContainer = createDynamicContainer(4);

	assert(getElementFromGivenIndex(newContainer, -1) == NULL);
	assert(getElementFromGivenIndex(newContainer, 5) == NULL);
	destroyContainer(newContainer);
}


// Run Tests -----------------------------------------------------------------------------------------------

void runTestsForDomain()
{
	CreateProfile_ValidInput_ProfileCreated();
	MakeCopyOfProfile_ValidInput_aCopyIsMade();
}

void runTestsForDynamicContainer()
{
	CreateDynamicContainer_ValidInput_CreatesContainer();
	ResizeContainer_ValidInput_ResizesTheContainer();
	GetElementFromGivenIndex_ValidInput_ReturnsTheElement();
	GetElementFromGivenIndex_InvalidInput_ReturnsNULL();
}

void runTestsForRepository()
{
	AddProfileToRepository_ValidInput_ProfileAdded();
	AddProfileToRepository_InvalidInput_ReturnError();

	DeleteProfileFromRepository_ValidInput_ProfileDeleted();
	DeleteProfileFromRepository_InvalidInput_ReturnsError();

	RepoHasGivenProfile_ValidInput_Returns1();
	RepoHasGivenProfile_InvalidInput_Returns0();

	FindProfileIndexByIdNumber_ValidInput_ReturnsIndex();
	FindProfileIndexByIdNumber_InvalidInput_ReturnsError();

	GetAllMatchingPsychologicalProfilesFromRepository_ValidInput_ReturnsContainerOfMatchingProfiles();
	GetAllMatchingProfilesMaximumYearsOfServiceFromRepository_ValidInput_ReturnsContainerOfMatchingProfiles();
}

void runTestsForOperationStack()
{
	CreateOperation_ValidInput_OperationCreated();
	CopyOperation_ValidInput_CreatesACopyOfTheOperation();
	StackIsEmpty_ValidInput_Returns1();
	StackIsEmpty_InvalidInput_Returns0();
	StackIsFull_InvalidInput_Returns0();
	PopOperationFromStack_ValidInput_ReturnsOperation();
	PopOperationFromStack_InvalidInput_ReturnsNULL();
}

void runTestsForService()
{
	AddProfileService_ValidInput_Returns0();
	AddProfileService_InvalidInput_ReturnsError();

	DeleteProfileService_ValidInput_Returns0();
	DeleteProfileFromRepository_InvalidInput_ReturnsError();

	UpdateProfileService_ValidInput_Returns0();
	UpdateProfileService_InvalidInput_ReturnsError();

	GetAllMatchingProfilesMaximumYearsOfServiceSorted_ValidInput_ReturnsContainerOfMatchingProfiles();
	GetAllMatchingPsychologicalProfilesService_ValidInput_ReturnsContainerOfMatchingProfiles();

	ComparatorForPlaceOfBirth_ValidInput_ReturnsOrderOfPlacesOfBirth();
	SortProfiles_ValidInput_ReturnsContainerWithSortedProfiles();

	UndoService_ValidInputForAdding_UndoesTheAdding();
	UndoService_InvalidInput_ReturnsError();
	UndoService_ValidInputForDeleting_UndoesTheDeletion();
	UndoService_ValidInputForUpdating_UndoesTheUpdate();

	RedoService_ValidInputForAddingAndUndo_RedoesTheAdding();
	RedoService_ValidInputForDeletingAndUndo_RedoesTheDeletion();
	RedoService_ValidInputForUpdatingAndUndo_RedoesTheUpdate();
	RedoService_InvalidInput_ReturnsError();

}
void runAllTests()
{
	runTestsForDomain();
	runTestsForDynamicContainer();
	runTestsForRepository();
	runTestsForOperationStack();
	runTestsForService();
}