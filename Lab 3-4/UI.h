#pragma once
#include "Service.h"

typedef struct {
	Service* service;
} UserInterface;

UserInterface* createUserInterface(Service* service);

void destroyUserInterface(UserInterface* userInterface);

void addProfileUI(UserInterface* userInterface, char argumentsOfCommand[]);

void deleteProfileUI(UserInterface* userInterface, char argumentsOfCommand[]);

void updateProfileUI(UserInterface* userInterface, char argumentsOfCommand[]);

void listAllProfilesUI(UserInterface* userInterface);

void listPsychologicalProfilesUI(UserInterface* userInterface, char argumentsOfCommand[]);

void listMaximumYearsOfServiceSortedUI(UserInterface* userInterface, char argumentsOfCommand[]);

void startProgram(UserInterface* userInterface);

void undoUI(UserInterface* userInterface);

void redoUI(UserInterface* userInterface);