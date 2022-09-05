#include "DynamicContainer.h"
#include <stdlib.h>


Container* createDynamicContainer(int capacityOfContainer)
{
	Container* dynamicContainer = (Container*)malloc(sizeof(Container));

	if (dynamicContainer == NULL)
		return NULL;

	dynamicContainer->capacityOfContainer = capacityOfContainer;
	dynamicContainer->lengthOfContainer = 0;

	dynamicContainer->arrayOfElements = (TypeElement*)malloc(capacityOfContainer * sizeof(TypeElement));
	if (dynamicContainer->arrayOfElements  == NULL)
		return NULL;

	return dynamicContainer;
}

void destroyContainer(Container* containerToBeDestroyed)
{
	if (containerToBeDestroyed == NULL)
		return NULL;

	for (int index = 0; index < containerToBeDestroyed->lengthOfContainer; index++)
		destroySheriffWorkersProfile(containerToBeDestroyed->arrayOfElements[index]);

	free(containerToBeDestroyed->arrayOfElements);
	containerToBeDestroyed->arrayOfElements = NULL;

	free(containerToBeDestroyed);
}

void destroyAuxiliaryContainer(Container* auxiliaryContainer)
{
	if (auxiliaryContainer == NULL)
		return;
	free(auxiliaryContainer->arrayOfElements);
	auxiliaryContainer->arrayOfElements = NULL;

	free(auxiliaryContainer);

}

int resizeContainer(Container* container)
{
	if (container == NULL)
		return -1;

	container->capacityOfContainer = container->capacityOfContainer * 2;
	TypeElement* auxiliaryArrayOfElements = (TypeElement*)malloc(container->capacityOfContainer * sizeof(TypeElement));
	if (auxiliaryArrayOfElements == NULL)
		return -1;
	for (int index = 0; index < container->lengthOfContainer; index++)
		auxiliaryArrayOfElements[index] = container->arrayOfElements[index];
	free(container->arrayOfElements);
	container->arrayOfElements = auxiliaryArrayOfElements;

	return 0;
}

void addElement(Container* container, TypeElement elementToBeAdded)
{
	if (container == NULL)
		return;
	if (container->arrayOfElements == NULL)
		return;

	// resize the array, if necessary
	if (container->lengthOfContainer == container->capacityOfContainer)
		resizeContainer(container);
	container->arrayOfElements[container->lengthOfContainer++] = elementToBeAdded;
}

void deleteElementFromContainer(Container* container, int indexToBeRemoved)
{
	if (container == NULL)
		return;
	if (indexToBeRemoved == container->lengthOfContainer - 1)
	{
		destroySheriffWorkersProfile(container->arrayOfElements[indexToBeRemoved]);
		container->lengthOfContainer = container->lengthOfContainer - 1;
		return;
	}

	//if (container->lengthOfContainer > 1)
	destroySheriffWorkersProfile(container->arrayOfElements[indexToBeRemoved]);
	
	for (int index = indexToBeRemoved; index < container->lengthOfContainer - 1; index++)
	{
		container->arrayOfElements[index] = makeCopyOfProfile(container->arrayOfElements[index + 1]);
	}
	destroySheriffWorkersProfile(container->arrayOfElements[container->lengthOfContainer - 1]);
	
	container->lengthOfContainer = container->lengthOfContainer - 1;
	
}

void updateElementFromGivenIndex(Container* container, int index, TypeElement newElement)
{
	container->arrayOfElements[index] = newElement;
}

int getLengthOfContainer(Container* container)
{
	return container->lengthOfContainer;
}

TypeElement* getElementFromGivenIndex(Container* container, int index)
{
	if (index >= container->lengthOfContainer || index < 0)
		return NULL;
	return container->arrayOfElements[index];
}

void increaseLengthOfContainer(Container* container)
{
	container->lengthOfContainer++;
}

void setElementFromGivenIndex(Container* container, int index, TypeElement setValue)
{
	container->arrayOfElements[index] = setValue;
}
