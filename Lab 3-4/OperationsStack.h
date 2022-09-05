#pragma once
#include "Domain.h"
#include "DynamicContainer.h"
#include <string.h>
#include <stdlib.h>

typedef struct
{
	SheriffWorkersProfile* profile;
	char* operationType;
} OperationOnProfiles;

OperationOnProfiles* createOperation(SheriffWorkersProfile* profile, char* operationType);
/*
	Description: Creates an operation.
	Paramaters: > profile = the profile on which that operation is applied;
				> operationType = the type of operation ("add", "delete", "update").
	Output:
		> returns the operation if it was created successfully;
		> return NULL otherwise.
*/
void destroyOperation(OperationOnProfiles* operationToBeDestroyed);
/*
	Description: Destroys the operation given as parameter.
*/
OperationOnProfiles* copyOperation(OperationOnProfiles* operationToBeCopied);
/*
	Description: Creates a copy of the operation given as parameter.
	Output:
		> returns the copy of the operation if it was created successfully;
		> return NULL otherwise.
*/
char* getOperationType(OperationOnProfiles* operation);
/*
	Description: A getter for the type of the operation given as parameter.
	Output:
		> returns the type of the operation.
*/
SheriffWorkersProfile* getOperationProfile(OperationOnProfiles* operation);
/*
	Description: A getter for the profile of the operation given as parameter.
	Output:
		> returns the profile of the operation.
*/

typedef struct
{
	OperationOnProfiles* operations[100];
	int lenghtOfStack;
} OperationsStack;

OperationsStack* createOperationsStack();
/*
	Description: Creates the operation stack.
	Output:
		> returns the operation stack if it was created successfully;
		> return NULL otherwise.
*/
void destroyOperationsStack(OperationsStack* operationsStack);
/*
	Description: Destroys the operation stack.
*/
void pushOperationOnStack(OperationsStack* operationsStack, OperationOnProfiles* operation);
/*
	Description: Push(adds) an operation given as parameter on the stack.
*/
OperationOnProfiles* popOperationFromStack(OperationsStack* operationsStack);
/*
	Description: Pops the last operation from the stack given as parameter.
	Output:
		> returns NULL if the stack is empty;
		> returns the operation otherwise;
*/
int stackIsEmpty(OperationsStack* operationsStack);
/*
	Description: Checks if the stack given as parameter is empty.
	Output:
		> returns 1 if the stack is empty;
		> returns 0 otherwise;
*/
int stackIsFull(OperationsStack* operationsStack);
/*
	Description: Checks if the stack given as parameter is full.
	Output:
		> returns 1 if the stack is full;
		> returns 0 otherwise;
*/

