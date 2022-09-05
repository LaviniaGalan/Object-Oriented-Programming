#include "Repository.h"

Repository* createRepository() {

	Repository* repository;
	repository = (Repository*)malloc(sizeof(Repository));
	if (repository == NULL)
		return NULL;
	repository->profilesData = createDynamicContainer(CAPACITY);
	return repository;
}

void destroyRepository(Repository* repository)
{
	if (repository == NULL)
		return NULL;
	
	destroyContainer(repository->profilesData);
	free(repository);
}

int repoHasGivenProfile(Repository* repository, TypeElement* profileToBeSearched)
{
	for (int index = 0; index < getLengthOfContainer(repository->profilesData); index++)
	{
		if (getProfileIdNumber(getElementFromGivenIndex(repository->profilesData, index)) == getProfileIdNumber(profileToBeSearched))
		{
			return 1;
		}
	}
	return 0;

}

int addProfileToRepository(Repository* repository, TypeElement profileToBeAdded)
{
	if (repository == NULL || profileToBeAdded == NULL)
		return -1;

	if (repoHasGivenProfile(repository, profileToBeAdded) == 1)
	{
		destroySheriffWorkersProfile(profileToBeAdded);
		return -1;
	}
	addElement(repository->profilesData, profileToBeAdded);
	return 0;
}

int findProfileIndexByIdNumber(Repository* repository, int profileIdNumber)
{
	for (int index = 0; index < getLengthOfContainer(repository->profilesData); index++)
	{
		if (getProfileIdNumber(getElementFromGivenIndex(repository->profilesData, index)) == profileIdNumber)
		{
			return index;
		}
	}

	return -1;
}

SheriffWorkersProfile* getProfileByIdNumber(Repository* repository, int profileIdNumber)
{
	for (int index = 0; index < getLengthOfContainer(repository->profilesData); index++)
	{
		if (getProfileIdNumber(getElementFromGivenIndex(repository->profilesData, index)) == profileIdNumber)
		{
			return getElementFromGivenIndex(repository->profilesData, index);
		}
	}

	return NULL;
}

int deleteProfileFromRepository(Repository* repository, int profileIdNumber)
{
	int indexToBeRemoved;
	indexToBeRemoved = findProfileIndexByIdNumber(repository, profileIdNumber);
	if (indexToBeRemoved == -1)
	{
		return -1;
	}
	deleteElementFromContainer(repository->profilesData, indexToBeRemoved);
	
	return 0;
}

int updateProfileInRepository(Repository* repository, TypeElement newProfile)
{
	int indexToBeUpdated = findProfileIndexByIdNumber(repository, getProfileIdNumber(newProfile));
	if (indexToBeUpdated == -1) {
		destroySheriffWorkersProfile(newProfile);
		return -1;
	}
	updateElementFromGivenIndex(repository->profilesData, indexToBeUpdated, newProfile);
	return 0;
}

Container* getAllProfilesFromRepository(Repository* repository)
{
	return repository->profilesData;
}

Container* getAllMatchingPsychologicalProfilesFromRepository(Repository* repository, char psychologicalProfile[])
{
	Container* allMatchingPsychologicalProfilesRepository = createDynamicContainer(10);

	for (int index = 0; index < repository->profilesData->lengthOfContainer; index++)
	{
		if (strcmp(getPsychologicalProfile(getElementFromGivenIndex(repository->profilesData, index)), psychologicalProfile) == 0)
		{
			setElementFromGivenIndex(allMatchingPsychologicalProfilesRepository, getLengthOfContainer(allMatchingPsychologicalProfilesRepository), getElementFromGivenIndex(repository->profilesData, index));
			increaseLengthOfContainer(allMatchingPsychologicalProfilesRepository);
		}
	}

	return allMatchingPsychologicalProfilesRepository;
}

Container* getAllMatchingProfilesMaximumYearsOfServiceFromRepository(Repository* repository, int maximumYearsOfService)
{
	Container* allMatchingProfilesMaximumYearsOfService = createDynamicContainer(10);

	for (int index = 0; index < repository->profilesData->lengthOfContainer; index++)
	{
		if (getYearsOfRecordedService(getElementFromGivenIndex(repository->profilesData, index)) < maximumYearsOfService)
		{
			setElementFromGivenIndex(allMatchingProfilesMaximumYearsOfService, getLengthOfContainer(allMatchingProfilesMaximumYearsOfService), getElementFromGivenIndex(repository->profilesData, index));
			increaseLengthOfContainer(allMatchingProfilesMaximumYearsOfService);
		}
	}

	return allMatchingProfilesMaximumYearsOfService;

}