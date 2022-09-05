#include "UI.h"
#include <string.h>
#include <stdio.h>

UserInterface* createUserInterface(Service* service)
{
	UserInterface* userInterface;
	userInterface = (UserInterface*)malloc(sizeof(UserInterface));
	if (userInterface == NULL)
		return NULL;
	userInterface->service = service;
	return userInterface;
}

void destroyUserInterface(UserInterface* userInterface)
{
	destroyService(userInterface->service);
	free(userInterface);
}

void addProfileUI(UserInterface* userInterface, char argumentsOfCommand[])
{
	int inputProfileIdNumber, inputYearsOfRecordedService;
	char inputPlaceOfBirth[20], inputPsychologicalProfile[20];
	char* argumentOfAdding;
	argumentOfAdding = strtok(argumentsOfCommand, ",");
	inputProfileIdNumber = atoi(argumentOfAdding);
	argumentOfAdding = strtok(NULL, ", ");
	strcpy(inputPlaceOfBirth, argumentOfAdding);
	argumentOfAdding = strtok(NULL, ", ");
	strcpy(inputPsychologicalProfile, argumentOfAdding);
	argumentOfAdding = strtok(NULL, ", ");
	inputYearsOfRecordedService = atoi(argumentOfAdding);

	int resultOfAddingUI = addProfileService(userInterface->service, inputProfileIdNumber, inputPlaceOfBirth, inputPsychologicalProfile, inputYearsOfRecordedService);
	if (resultOfAddingUI == -1) printf("No! \n");
}

void deleteProfileUI(UserInterface* userInterface, char argumentsOfCommand[])
{
	int inputProfileIdNumber;
	inputProfileIdNumber = atoi(argumentsOfCommand);
	int resultOfDeletingUI = deleteProfileService(userInterface->service, inputProfileIdNumber);
	if (resultOfDeletingUI == -1) printf("No! \n");
}


void listAllProfilesUI(UserInterface* userInterface)
{
	Container* listOfAllProfiles;
	listOfAllProfiles = getAllProfilesService(userInterface->service);
	SheriffWorkersProfile* profileFromList;
	for (int index = 0; index < getLengthOfContainer(listOfAllProfiles); index++)
	{
		profileFromList = getElementFromGivenIndex(listOfAllProfiles, index);
		printf("%d %s %s %d", getProfileIdNumber(profileFromList), getPlaceOfBirth(profileFromList), getPsychologicalProfile(profileFromList), getYearsOfRecordedService(profileFromList));
		printf("\n");
	}
	
}

void listPsychologicalProfilesUI(UserInterface* userInterface, char argumentsOfCommand[])
{
	Container* allMatchingPsychologicalProfiles;
	char psychologicalProfile[20];
	char* argument = strtok(argumentsOfCommand, " ");
	strcpy(psychologicalProfile, argument);
	allMatchingPsychologicalProfiles = getAllMatchingPsychologicalProfilesService(userInterface->service, psychologicalProfile);
	SheriffWorkersProfile* profileFromList;
	for (int index = 0; index < getLengthOfContainer(allMatchingPsychologicalProfiles); index++)
	{
		profileFromList = getElementFromGivenIndex(allMatchingPsychologicalProfiles, index);
		printf("%d %s %s %d", getProfileIdNumber(profileFromList), getPlaceOfBirth(profileFromList), getPsychologicalProfile(profileFromList), getYearsOfRecordedService(profileFromList));
		printf("\n");
	}
	destroyAuxiliaryContainer(allMatchingPsychologicalProfiles);
}


void listMaximumYearsOfServiceSortedUI(UserInterface* userInterface, char argumentsOfCommand[])
{
	Container* allMatchingProfiles;
	int maximumYearsOfService;
	char* argument = strtok(argumentsOfCommand, " ");
	maximumYearsOfService = atoi(argument);
	allMatchingProfiles = getAllMatchingProfilesMaximumYearsOfServiceSorted(userInterface->service, maximumYearsOfService);
	SheriffWorkersProfile* profileFromList;
	for (int index = 0; index < getLengthOfContainer(allMatchingProfiles); index++)
	{
		profileFromList = getElementFromGivenIndex(allMatchingProfiles, index);
		printf("%d %s %s %d", getProfileIdNumber(profileFromList), getPlaceOfBirth(profileFromList), getPsychologicalProfile(profileFromList), getYearsOfRecordedService(profileFromList));
		printf("\n");
	}
	destroyAuxiliaryContainer(allMatchingProfiles);
}


void updateProfileUI(UserInterface* userInterface, char argumentsOfCommand[])
{
	int inputProfileIdNumber, inputNewYearsOfRecordedService;
	char inputNewPlaceOfBirth[20], inputNewPsychologicalProfile[20];

	char* argumentOfUpdating;
	argumentOfUpdating = strtok(argumentsOfCommand, ", ");
	inputProfileIdNumber = atoi(argumentOfUpdating);
	argumentOfUpdating = strtok(NULL, ", ");
	strcpy(inputNewPlaceOfBirth, argumentOfUpdating);
	argumentOfUpdating = strtok(NULL, ", ");
	strcpy(inputNewPsychologicalProfile, argumentOfUpdating);
	argumentOfUpdating = strtok(NULL, ", ");
	inputNewYearsOfRecordedService = atoi(argumentOfUpdating);

	int resultOfUpdating = updateProfileService(userInterface->service, inputProfileIdNumber, inputNewPlaceOfBirth, inputNewPsychologicalProfile, inputNewYearsOfRecordedService);
	if (resultOfUpdating == -1) printf("No! \n");
}

void undoUI(UserInterface* userInterface)
{
	int resultOfUndo = undoService(userInterface->service);
	if (resultOfUndo == 0)
		printf("No more undos!\n");
}

void redoUI(UserInterface* userInterface)
{
	int resultOfRedo = redoService(userInterface->service);
	if (resultOfRedo == 0)
		printf("No more redos!\n");
}

void startProgram(UserInterface* userInterface)
{

	int firstPositionOfArguments = 0;
	char inputCommand[70], argumentsOfCommand[60], * firstWordOfCommand;
	while (1) {
		gets(inputCommand);
		inputCommand[strlen(inputCommand)] = 0;
		if (strcmp(inputCommand, "exit") == 0) break;
		else if (strcmp(inputCommand, "list") == 0) listAllProfilesUI(userInterface);
		else if (strcmp(inputCommand, "undo") == 0) undoUI(userInterface);
		else if (strcmp(inputCommand, "redo") == 0) redoUI(userInterface);
		else
		{
			firstPositionOfArguments = 0;
			while (inputCommand[firstPositionOfArguments] != ' ')
				firstPositionOfArguments++;
			strcpy(argumentsOfCommand, inputCommand + firstPositionOfArguments);
			firstWordOfCommand = strtok(inputCommand, " ");
			if (strcmp(firstWordOfCommand, "add") == 0) addProfileUI(userInterface, argumentsOfCommand);
			else if (strcmp(firstWordOfCommand, "delete") == 0) deleteProfileUI(userInterface, argumentsOfCommand);
			else if (strcmp(firstWordOfCommand, "update") == 0) updateProfileUI(userInterface, argumentsOfCommand);
			else if (strcmp(firstWordOfCommand, "list") == 0)
			{
				int argumentIsANumberOfYears = 1;
				for (int index = 0; index < strlen(argumentsOfCommand); index++)
					if (!(argumentsOfCommand[index] == ' ' || (argumentsOfCommand[index] >= '0' && argumentsOfCommand[index] <= '9')))
					{
						argumentIsANumberOfYears = 0;
						break;
					}
				if (argumentIsANumberOfYears == 0)
					listPsychologicalProfilesUI(userInterface, argumentsOfCommand);
				else
					listMaximumYearsOfServiceSortedUI(userInterface, argumentsOfCommand);

			}

		}

	}
}