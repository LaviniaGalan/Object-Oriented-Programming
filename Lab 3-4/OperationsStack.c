#include "OperationsStack.h"

OperationOnProfiles* createOperation(SheriffWorkersProfile* profile, char* operationType)
{
	OperationOnProfiles* operation = (OperationOnProfiles*)malloc(sizeof(OperationOnProfiles));
	if (operation == NULL)
		return NULL;
	operation->profile = makeCopyOfProfile(profile);

	if (operationType != NULL)
	{
		operation->operationType = (char*)malloc(sizeof(char) * (strlen(operationType) + 1));
		strcpy(operation->operationType, operationType);
		operation->operationType[strlen(operation->operationType)] = 0;
	}
	else
		operation->operationType = NULL;
	return operation;
}

void destroyOperation(OperationOnProfiles* operationToBeDestroyed)
{
	if (operationToBeDestroyed == NULL)
		return;

	destroySheriffWorkersProfile(operationToBeDestroyed->profile);
	free(operationToBeDestroyed->operationType);
	free(operationToBeDestroyed);
}

OperationOnProfiles* copyOperation(OperationOnProfiles* operationToBeCopied)
{
	if (operationToBeCopied == NULL)
		return NULL;
	OperationOnProfiles* copyOfOperation = createOperation(operationToBeCopied->profile, getOperationType(operationToBeCopied));
	return copyOfOperation;
}

char* getOperationType(OperationOnProfiles* operation)
{
	if (operation == NULL)
		return NULL;
	return operation->operationType;
}

SheriffWorkersProfile* getOperationProfile(OperationOnProfiles* operation)
{
	if (operation == NULL)
		return NULL;
	return operation->profile;
}



OperationsStack* createOperationsStack()
{
	OperationsStack* operationsStack = (OperationsStack*)malloc(sizeof(OperationsStack));
	if (operationsStack == NULL)
		return NULL;
	operationsStack->lenghtOfStack = 0;
	return operationsStack;
}

void destroyOperationsStack(OperationsStack* operationsStack)
{
	if (operationsStack == NULL)
		return;
	for (int index = 0; index < operationsStack->lenghtOfStack; index++)
		destroyOperation(operationsStack->operations[index]);
	free(operationsStack);
}

void pushOperationOnStack(OperationsStack* operationsStack, OperationOnProfiles* operation)
{
	if (operationsStack == NULL || operation == NULL)
		return;
	if (stackIsFull(operationsStack))
		return;
	operationsStack->operations[operationsStack->lenghtOfStack++] = copyOperation(operation);
}

OperationOnProfiles* popOperationFromStack(OperationsStack* operationsStack)
{
	if (operationsStack == NULL || stackIsEmpty(operationsStack))
		return NULL;

	operationsStack->lenghtOfStack = operationsStack->lenghtOfStack - 1;
	return operationsStack->operations[operationsStack->lenghtOfStack];
}

int stackIsEmpty(OperationsStack* operationsStack)
{
	if (operationsStack->lenghtOfStack == 0)
		return 1;
	return 0;
}

int stackIsFull(OperationsStack* operationsStack)
{
	if (operationsStack->lenghtOfStack == 100)
		return 1;
	return 0;
}
