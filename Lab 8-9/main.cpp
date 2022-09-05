#include "UI.h"
#include "Test.h"
#include <iostream>
#include <crtdbg.h>

int main()
{
	{
	Repository* repo = nullptr;

	StandardUserDatabase* sudb = nullptr;
	Service service{ repo, sudb };
	UserInterface ui{ service };
	ui.runProgram();
}
	_CrtDumpMemoryLeaks();
}
