#pragma once 
#include "Domain.h"
#define CAPACITY 10 

//typedef SheriffWorkersProfile* TypeElement;

typedef struct {
	TypeElement* arrayOfElements;
	int lengthOfContainer;
	int capacityOfContainer;
} Container;

Container* createDynamicContainer(int capacityOfContainer);
/*
	Description: Creates a dynamic array which has the capacity given as parameter.
	Output:
		> returns the dynamic container if it was created successfully;
		> returns NULL otherwise;
*/

void destroyContainer(Container* containerToBeDestroyed);
/*
	Description: Destroys the container.
*/

void destroyAuxiliaryContainer(Container* auxiliaryContainer);
/*
	Description: Destroy the auxiliary containers that I used (for example, the container with the profiles having a certain
psychological profile).

*/

int resizeContainer(Container* container);
/*
	Description: Resizes the container given as parameter.
	Output:
		> returns -1 if the container could not be resized;
		> returns 0 otherwise.
*/

void addElement(Container* container, TypeElement elementToBeAdded);
/*
	Description: Adds the element given as parameter to the container.
*/

void deleteElementFromContainer(Container* container, int indexToBeRemoved);
/*
	Description: Deletes from the container the element on the position "indexToBeRemoved".
*/

void updateElementFromGivenIndex(Container* container, int index, TypeElement newElement);
/*
	Description: Updates in the container the element on the position "index", assigning to it newElement.
*/

int getLengthOfContainer(Container* container);
/*
	Description: Gets the lenght of the container given as parameter.
	Output:
		> Returns the lenght of the container.
*/

TypeElement* getElementFromGivenIndex(Container* container, int index);
/*
	Description: Get the element which is on the index given as parameter in the container.
	Output:
		> returns the element from that index if the index is valid;
		> returns NULL if the index was invalid.
*/

void increaseLengthOfContainer(Container* container);
/*
	Description: Increases the lenght of the container given as parameter with 1.
*/

void setElementFromGivenIndex(Container* container, int index, TypeElement setValue);
/*
	Description: Set the value of the element from the index to a new value, given by setValue.
*/