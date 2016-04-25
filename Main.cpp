


#include "options.h"
#include "LS_Simulator.h"
#include "LS_Simulator3D.h"

using namespace std;

void main(int argc, char **argv)
{

#ifdef _DEBUG
	//Used to check for Memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
	//Hide the console
	FreeConsole();
#endif
	CLS_Simulator3D::setScreenSizeLoc(WINDOW_PRIMARY, 0, 0, 800, 800);
#ifdef _DEBUG
	CLS_Simulator3D::setScreenSizeLoc(WINDOW_DEBUG, 831, 0, 500, 200);
#endif

	//CLS_Simulator::simulationInit(argc,argv);

	//CLS_Simulator::mainLoop();

	CLS_Simulator3D::init(argc, argv);

	CLS_Simulator3D::mainloop();

	system("PAUSE");
}

