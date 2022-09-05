#pragma once

typedef struct
{
	int profileIdNumber;
	char* placeOfBirth;
	char* psychologicalProfile;
	int yearsOfRecordedService;
} SheriffWorkersProfile;

typedef SheriffWorkersProfile* TypeElement;

SheriffWorkersProfile* createProfile(int profileIdNumber, char* placeOfBirth, char* psychologicalProfile, int yearsOfRecordedService);
/*
	Description: Creates a profile which has the characteristics given as parameters.
	Output: > the created profile.
*/
void destroySheriffWorkersProfile(SheriffWorkersProfile* profileToBeDestroyed);
/*
	Description: Destroys the profile given as parameter (deallocates memory which was allocated for that profile).
*/
int getProfileIdNumber(SheriffWorkersProfile* profile);
/*
	Description: A getter for the Id number of the profile given as parameter.
	Output: > returns the Id number of the profile.
*/
char* getPlaceOfBirth(SheriffWorkersProfile* profile);
/*
	Description: A getter for the place of birth corresponding to the profile given as parameter.
	Output: > returns the place of birth of the profile.
*/
char* getPsychologicalProfile(SheriffWorkersProfile* profile);
/*
	Description: A getter for the psychological profile of the profile given as parameter.
	Output: > returns the psychological profile of the profile.
*/
int getYearsOfRecordedService(SheriffWorkersProfile* profile);
/*
	Description: A getter for the number of years of recorded service for the profile given as parameter.
	Output: > returns the profile's number of years of recorded service.
*/

SheriffWorkersProfile* makeCopyOfProfile(SheriffWorkersProfile* profileToBeCopied);
/*
	Description: Creates a copy of the profile given as parameter.
	Output: > returns the copy of the profile.
*/