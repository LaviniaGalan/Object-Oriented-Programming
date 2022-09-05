#include "EvidenceGUI.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "Test.h"
#include "GUI.h"
#include "EvidenceGUI.h"
#include <memory>
#include <crtdbg.h>

int main(int argc, char* argv[])
{
	{
		QApplication application(argc, argv);
		Repository* repository = nullptr;
		Repository* userDatabase = nullptr;
	
		Service service{ repository, userDatabase };
		EvidenceGUI gui{ service };
		gui.show();

		return application.exec();
	}
	
	_CrtDumpMemoryLeaks;
}
