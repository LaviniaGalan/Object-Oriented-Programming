#include "UI.h"
#include "Test.h"
#include <crtdbg.h>
int main()
{

	{
		//runAllTests();
		Repository repository{};
		StandardUserDatabase standardUserDatabase{};
		Service service{ repository, standardUserDatabase };
		UserInterface ui{ service };
		ui.runProgram();

	}

	_CrtDumpMemoryLeaks();
	return 0;
}