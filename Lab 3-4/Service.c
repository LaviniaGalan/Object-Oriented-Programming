#include "Service.h"

Service* createService(Repository* repository, OperationsStack* stackForUndoOperation, OperationsStack* stackForRedoOperation)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
		return NULL;
	service->repository = repository;
	service->stackForUndoOperation = stackForUndoOperation;
	service->stackForRedoOperation = stackForRedoOperation;
	return service;
}

void destroyService(Service* service)
{
	destroyRepository(service->repository);
	destroyOperationsStack(service->stackForUndoOperation);
	destroyOperationsStack(service->stackForRedoOperation);
	free(service);
}

int addProfileService(Service* service, int profileIdNumber, char placeOfBirth[], char pshycologicalProfile[], int yearsOfRecordedService)
{
	SheriffWorkersProfile* profileToBeAdded;
	profileToBeAdded = createProfile(profileIdNumber, placeOfBirth, pshycologicalProfile, yearsOfRecordedService);
	int resultOfAdding = addProfileToRepository(service->repository, profileToBeAdded);
	if (resultOfAdding == 0)
	{
		OperationOnProfiles* addOperation = createOperation(profileToBeAdded, "add");
		pushOperationOnStack(service->stackForUndoOperation, addOperation);
		destroyOperation(addOperation);
	}
	return resultOfAdding;
}

int updateProfileService(Service* service, int profileIdNumber, char newPlaceOfBirth[], char newPshycologicalProfile[], int newYearsOfRecordedService)
{
	SheriffWorkersProfile* profileToUpdateWith;
	profileToUpdateWith = createProfile(profileIdNumber, newPlaceOfBirth, newPshycologicalProfile, newYearsOfRecordedService);
	
	SheriffWorkersProfile* profileWhichWillBeUpdated = getProfileByIdNumber(service->repository, profileIdNumber);
	SheriffWorkersProfile* copyOfUpdatedProfile = NULL;
	if (profileWhichWillBeUpdated != NULL)
		copyOfUpdatedProfile = makeCopyOfProfile(profileWhichWillBeUpdated);
	
	int resultOfUpdating = updateProfileInRepository(service->repository, profileToUpdateWith);
	if (resultOfUpdating == 0)
	{
		OperationOnProfiles* updateOperation = createOperation(copyOfUpdatedProfile, "update");
		pushOperationOnStack(service->stackForUndoOperation, updateOperation);
		destroyOperation(updateOperation);
		destroySheriffWorkersProfile(copyOfUpdatedProfile);
		destroySheriffWorkersProfile(profileWhichWillBeUpdated);
	}
	return resultOfUpdating;
}

int deleteProfileService(Service* service, int profileIdNumber)
{
	SheriffWorkersProfile* deletedProfile = getProfileByIdNumber(service->repository, profileIdNumber);
	SheriffWorkersProfile* copyOfDeletedProfile = NULL;
	if (deletedProfile != NULL)
		copyOfDeletedProfile = makeCopyOfProfile(deletedProfile);
	
	int resultOfDeleting = deleteProfileFromRepository(service->repository, profileIdNumber);
	if (resultOfDeleting == 0)
	{
		OperationOnProfiles* deleteOperation = createOperation(copyOfDeletedProfile, "delete");
		pushOperationOnStack(service->stackForUndoOperation, deleteOperation);
		destroyOperation(deleteOperation);
		destroySheriffWorkersProfile(copyOfDeletedProfile);
	}
	return resultOfDeleting;
}

Container* getAllProfilesService(Service* service)
{
	return getAllProfilesFromRepository(service->repository);
}

Container* getAllMatchingPsychologicalProfilesService(Service* service, char psychologicalProfile[])
{
	return getAllMatchingPsychologicalProfilesFromRepository(service->repository, psychologicalProfile);
}


Container* getAllMatchingProfilesMaximumYearsOfServiceSorted(Service* service, int maximumYearsOfService)
{
	Container* matchingProfilesMaximumYearsOfService = getAllMatchingProfilesMaximumYearsOfServiceFromRepository(service->repository, maximumYearsOfService);
	Container* matchingProfilesMaximumYearsOfServiceSorted;
	matchingProfilesMaximumYearsOfServiceSorted = sortProfiles(matchingProfilesMaximumYearsOfService, &comparatorForPlaceOfBirth, 1);
	return matchingProfilesMaximumYearsOfServiceSorted;
}


int comparatorForPlaceOfBirth(SheriffWorkersProfile* firstProfileInComparison, SheriffWorkersProfile* secondProfileInComparison)
{
	if (strcmp(getPlaceOfBirth(firstProfileInComparison), getPlaceOfBirth(secondProfileInComparison)) == 0)
		return 0;
	if (strcmp(getPlaceOfBirth(firstProfileInComparison), getPlaceOfBirth(secondProfileInComparison)) < 0)
		return 1;
	return -1;
}

Container* sortProfiles(Container* profilesToBeSorted, Comparator comparatorFunction, int orderOfSorting)
{
	Container* sortedProfiles;
	sortedProfiles = profilesToBeSorted;
	int profilesAreSorted = 0, relationAfterComparing, index;
	SheriffWorkersProfile* auxiliaryProfile;
	while (profilesAreSorted == 0)
	{
		profilesAreSorted = 1;
		for (index = 0; index < getLengthOfContainer(sortedProfiles) - 1; index++)
		{
			relationAfterComparing = comparatorFunction(getElementFromGivenIndex(sortedProfiles, index), getElementFromGivenIndex(sortedProfiles, index + 1));
			if (relationAfterComparing != orderOfSorting && relationAfterComparing != 0)
			{
				auxiliaryProfile = getElementFromGivenIndex(sortedProfiles, index);
				setElementFromGivenIndex(sortedProfiles, index, getElementFromGivenIndex(sortedProfiles, index + 1));
				setElementFromGivenIndex(sortedProfiles, index + 1, auxiliaryProfile);
				profilesAreSorted = 0;
			}
		}
	}
	return sortedProfiles;
}


int undoService(Service* service)
{
	if (stackIsEmpty(service->stackForUndoOperation) == 1)
		return 0;
	
	OperationOnProfiles* operation = popOperationFromStack(service->stackForUndoOperation);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		SheriffWorkersProfile* copyOfProfile = makeCopyOfProfile(getOperationProfile(operation));

		OperationOnProfiles* redoOperation = createOperation(copyOfProfile, "add");
		pushOperationOnStack(service->stackForRedoOperation, redoOperation);
		destroyOperation(redoOperation);

		deleteProfileFromRepository(service->repository, getProfileIdNumber(copyOfProfile));

		destroySheriffWorkersProfile(copyOfProfile);
	}
	else if (strcmp(getOperationType(operation), "delete") == 0)
	{
		SheriffWorkersProfile* copyOfProfile = makeCopyOfProfile(getOperationProfile(operation));

		OperationOnProfiles* redoOperation = createOperation(copyOfProfile, "delete");
		pushOperationOnStack(service->stackForRedoOperation, redoOperation);
		destroyOperation(redoOperation);

		addProfileToRepository(service->repository, copyOfProfile);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{

		SheriffWorkersProfile* copyOfProfile = makeCopyOfProfile(getOperationProfile(operation));

		SheriffWorkersProfile* profileBeforeUndo = getProfileByIdNumber(service->repository, getProfileIdNumber(getOperationProfile(operation)));
		SheriffWorkersProfile* copyOfProfileBeforeUndo = makeCopyOfProfile(profileBeforeUndo);
		OperationOnProfiles* redoOperation = createOperation(copyOfProfileBeforeUndo, "update");
		pushOperationOnStack(service->stackForRedoOperation, redoOperation);
		destroyOperation(redoOperation);
		
		updateProfileInRepository(service->repository, copyOfProfile);
		destroySheriffWorkersProfile(copyOfProfileBeforeUndo);
		destroySheriffWorkersProfile(profileBeforeUndo);
		
	}
	
	destroyOperation(operation);

	return 1;
}

int redoService(Service* service)
{
	if (stackIsEmpty(service->stackForRedoOperation) == 1)
		return 0;

	OperationOnProfiles* operation = popOperationFromStack(service->stackForRedoOperation);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		SheriffWorkersProfile* profile = getOperationProfile(operation);
		SheriffWorkersProfile* copyOfProfile = makeCopyOfProfile(profile);

		OperationOnProfiles* undoOperation = createOperation(copyOfProfile, "add");
		pushOperationOnStack(service->stackForUndoOperation, undoOperation);
		destroyOperation(undoOperation);
		
		addProfileToRepository(service->repository, copyOfProfile);
	}
	else if (strcmp(getOperationType(operation), "delete") == 0)
	{
		//SheriffWorkersProfile* profile = getOperationProfile(operation);
		SheriffWorkersProfile* copyOfProfile = makeCopyOfProfile(getOperationProfile(operation));

		OperationOnProfiles* undoOperation = createOperation(copyOfProfile, "delete");
		pushOperationOnStack(service->stackForUndoOperation, undoOperation);
		destroyOperation(undoOperation);

		deleteProfileFromRepository(service->repository, getProfileIdNumber(copyOfProfile));
		destroySheriffWorkersProfile(copyOfProfile);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		//SheriffWorkersProfile* profile = getOperationProfile(operation);
		SheriffWorkersProfile* copyOfProfile = makeCopyOfProfile(getOperationProfile(operation));

		SheriffWorkersProfile* profileBeforeRedo = getProfileByIdNumber(service->repository, getProfileIdNumber(copyOfProfile));
		SheriffWorkersProfile* copyOfProfileBeforeRedo = makeCopyOfProfile(profileBeforeRedo);
		OperationOnProfiles* undoOperation = createOperation(copyOfProfileBeforeRedo, "update");
		pushOperationOnStack(service->stackForUndoOperation, undoOperation);
		destroyOperation(undoOperation);

		updateProfileInRepository(service->repository, copyOfProfile);
		destroySheriffWorkersProfile(copyOfProfileBeforeRedo);
		destroySheriffWorkersProfile(profileBeforeRedo);
	}

	destroyOperation(operation);

	return 1;
}