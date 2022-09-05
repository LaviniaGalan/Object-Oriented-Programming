#pragma once

#include "Domain.h"
#include "DynamicContainer.h"
#include <stdlib.h>


typedef struct {
	Container* profilesData;
} Repository;

Repository* createRepository();
/*
	Creates a repository.
	Output:
		> returns NULL if there was no space allocated for the repository;
		> returns the repository otherwise.
*/
void destroyRepository(Repository* repository);
/*
	Deallocates the memory which was allocated for the repository given as parameter.
*/

int repoHasGivenProfile(Repository* repository, TypeElement* profileToBeSearched);
/*
	Description: Checks if a repository contains a given profile.
	Output:
		> returns 1 if the repository contains the profile;
		> returns 0 otherwise.
*/

int addProfileToRepository(Repository* repository, TypeElement profileToBeAdded);
/*
	Description: Adds a profile to a repository.
	Output:
		> returns -1 if the repository already contains the profile;
		> returns 0 if the profile was added successfully.
*/

int deleteProfileFromRepository(Repository* repository, int profileIdNumber);
/*
	Description: Removes a profile from a repository.
	Output:
		> returns -1 if the profile can not be removed (repository does not contain the profile);
		> returns 0 if the profile was removed successfully.
*/

int updateProfileInRepository(Repository* repository, TypeElement newProfile);
/*
	Description: Updates a profile from the repository, by assigning to it a new value.
	Output: 
		> returns -1 if the profile can not be updated (repository does not contain a profile with the same profile Id Number 
as the new Profile)
		> return 0 if the profile was removed successfully.
*/

int findProfileIndexByIdNumber(Repository* repository, int profileIdNumber);
/*
	Description: Finds the position of the profile in repository's container by its Id Number.
	Output:
		> returns the index of the profile in the container of the repository (if it is there);
		> returns -1 if there is no profile with that IdNumber in the container.
*/

Container* getAllProfilesFromRepository(Repository* repository);
/*
	Description: Gets the dynamic container with the profiles from repository.
	Output:
		> returns the container of profiles.
*/

Container* getAllMatchingPsychologicalProfilesFromRepository(Repository* repository, char psychologicalProfile[]);
/*
	Description: Finds all the profiles from the repository which have the same psychological profile as the one that is given.
	Output:
		> a container with the profiles matching the description.
*/

Container* getAllMatchingProfilesMaximumYearsOfServiceFromRepository(Repository* repository, int maximumYearsOfService);
/*
	Description: Finds all the profiles from the repository for which the number of years of recorded service is at most the
one that's given.
	Output:
		> a container with the profiles which match the description.
*/

SheriffWorkersProfile* getProfileByIdNumber(Repository* repository, int profileIdNumber);
/*
	Description: Finds the profile which has the given profile Id number.
	Output:
		> returns the profile with the given Id number.
*/