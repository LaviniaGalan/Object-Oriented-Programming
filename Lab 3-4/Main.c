#include "UI.h"
#include "Test.h"
#include <stdio.h>
#include <string.h>
#include <crtdbg.h>

int main()
{
	
	//runAllTests();

	Repository* repository = createRepository();
	OperationsStack* stackForUndoOperation = createOperationsStack();
	OperationsStack* stackForRedoOperation = createOperationsStack();
	Service* service = createService(repository, stackForUndoOperation, stackForRedoOperation);
	UserInterface* userInterface = createUserInterface(service);

	startProgram(userInterface);

	destroyUserInterface(userInterface);
	
	_CrtDumpMemoryLeaks();
	
	return 0;
}