#pragma once
#include "Repository.h"
#include "OperationsStack.h"

typedef struct
{
	Repository* repository;
	OperationsStack* stackForUndoOperation;
	OperationsStack* stackForRedoOperation;
} Service;

typedef int (*Comparator)(SheriffWorkersProfile*, SheriffWorkersProfile*);

Service* createService(Repository* repository, OperationsStack* stackForUndoOperation, OperationsStack* stackForRedoOperation);
/*
	Creates a service.
	Parameters: > repository = the services's repository;
				> stackForUndoOperation = a stack which stores all undo-able operations which were done until a certain point;
				> stackForRedoOperation = a stack with all redo-able operations;
	Output:
		> returns NULL if there was no space allocated for the service;
		> returns the service otherwise.
*/
void destroyService(Service* service);
/*
	Destroys the service.
*/

int addProfileService(Service* service, int profileIdNumber, char placeOfBirth[], char pshycologicalProfile[], int yearsOfRecordedService);
/*
	Creates a profile with the given characteristics and adds it to the list of profiles.
	Parameters: > service = the service
				> profileIdNumber = the input profile Id number
				> placeOfBirth = the input place of birth
				> psychologicalProfile = the input psychological profile
				> yearsOfRecordedService = the input years of recorded service
	Output:
		> returns -1 if the profile could not be added to the list of profiles;
		> returns 0 if the profile was added successfully to the list.
*/
int updateProfileService(Service* service, int profileIdNumber, char newPlaceOfBirth[], char newPshycologicalProfile[], int newYearsOfRecordedService);
/*
	Updates a profile from the list of profiles.
	Parameters: > service = the service
				> profileIdNumber = the id number of the profile to be updated
				> newPlaceOfBirth = the input place of birth (to update with)
				> newPsychologicalProfile = the input psychological profile to update with
				> newYearsOfRecordedService = the input number of years of recorded service
	Output:
		> returns -1 if the profile could not be updated;
		> returns 0 if the profile was updated successfully.
*/
int deleteProfileService(Service* service, int profileIdNumber);
/*
	Deletes from the list of profiles, that profile that has the given profile Id number.
	Parameters: > service = the service
				> profileIdNumber = the input profile Id number for deleting
	Output:
		> returns -1 if the profile could not be deleted from the list of profiles;
		> returns 0 if the profile was removed successfully to the list.
*/

Container* getAllProfilesService(Service* service);
/*
	Description: Gets the dynamic container with the existent profiles.
	Output:
		> returns the container of profiles.
*/

Container* getAllMatchingPsychologicalProfilesService(Service* service, char psychologicalProfile[]);
/*
	Description: Finds all the profiles which have the same psychological profile as the one that is given.
	Output:
		> a container with the profiles matching the description.
*/

Container* getAllMatchingProfilesMaximumYearsOfServiceSorted(Service* service, int maximumYearsOfService);
/*
	Description: Finds all the profiles for which the number of years of recorded service is at most the one that's given.
	Output:
		> a container with the profiles which match the description.
*/

int comparatorForPlaceOfBirth(SheriffWorkersProfile* firstProfileInComparison, SheriffWorkersProfile* secondProfileInComparison);
/*
	Compares two profiles by their place of birth.
	Output:
		> returns 0 if the profiles have the same place of birth;
		> returns 1 if the place of birth of the first profile is before the place of birth of the second profile (alphabetically);
		> returns -1 if the place of birth of the first profile is after the place of birth of the second profile (alphabetically);
*/

Container* sortProfiles(Container* profilesToBeSorted, Comparator comparatorFunction, int orderOfSorting);
/*
	Sorts a container of profiles by the criterias given by comparatorFunction (in this case, the sorting is made by place of
birth), in the order given by orderOfSorting (1 for ascending sorting, -1 for descending sorting).
	Output:
		> returns NULL if the container is NULL;
		> returns the container of sorted profiles otherwise.
*/

int undoService(Service* service);
/*	
	Undoes the last performed operation.
	Output:
		> returns 0 if there were no performed operations that can be undone.
		> returns 1 if the undo was made successfully.
*/

int redoService(Service* service);
/*
	Redoes the last performed operation.
	Output:
		> returns 0 if there were no performed operations that can be redone.
		> returns 1 if the redo was made successfully.
*/