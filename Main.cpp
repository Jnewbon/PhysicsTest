


#include "options.h"
#include "LS_Simulator.h"

using namespace std;

void main(int argc, char **argv)
{

#ifdef _DEBUG
	//Used to check for Memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	CLS_Simulator::simulationInit(argc,argv);

	CLS_Simulator::mainLoop();
	system("PAUSE");
}

