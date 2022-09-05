#include <string.h>
#include "Domain.h"
#include <stdlib.h>

SheriffWorkersProfile* createProfile(int profileIdNumber, char* placeOfBirth, char* psychologicalProfile, int yearsOfRecordedService)
{
	SheriffWorkersProfile* workerProfile = (SheriffWorkersProfile*)malloc(sizeof(SheriffWorkersProfile));
	if (workerProfile == NULL)
		return NULL;
	workerProfile->profileIdNumber = profileIdNumber;
	workerProfile->placeOfBirth = (char*)malloc(sizeof(char) * (strlen(placeOfBirth) + 1));
	if (workerProfile->placeOfBirth != NULL)
		strcpy(workerProfile->placeOfBirth, placeOfBirth);
	workerProfile->psychologicalProfile = (char*)malloc(sizeof(char) * (strlen(psychologicalProfile) + 1));
	if (workerProfile->psychologicalProfile != NULL)
		strcpy(workerProfile->psychologicalProfile, psychologicalProfile);
	workerProfile->yearsOfRecordedService = yearsOfRecordedService;

	return workerProfile;
}

void destroySheriffWorkersProfile(SheriffWorkersProfile* profileToBeDestroyed)
{
	free(profileToBeDestroyed->placeOfBirth);
	free(profileToBeDestroyed->psychologicalProfile);

	free(profileToBeDestroyed);
}

SheriffWorkersProfile* makeCopyOfProfile(SheriffWorkersProfile* profileToBeCopied)
{
	if (profileToBeCopied == NULL)
		return NULL;

	SheriffWorkersProfile* copyOfProfile = createProfile(getProfileIdNumber(profileToBeCopied), getPlaceOfBirth(profileToBeCopied), getPsychologicalProfile(profileToBeCopied), getYearsOfRecordedService(profileToBeCopied));
	return copyOfProfile;
}

int getProfileIdNumber(SheriffWorkersProfile* profile)
{
	if (profile == NULL)
		return NULL;
	return profile->profileIdNumber;
}

char* getPlaceOfBirth(SheriffWorkersProfile* profile)
{
	if (profile == NULL)
		return NULL;
	return profile->placeOfBirth;
}

char* getPsychologicalProfile(SheriffWorkersProfile* profile)
{
	if (profile == NULL)
		return NULL;
	return profile->psychologicalProfile;
}

int getYearsOfRecordedService(SheriffWorkersProfile* profile)
{
	if (profile == NULL)
		return NULL;
	return profile->yearsOfRecordedService;
}

