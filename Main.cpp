#ifdef _DEBUG 
	#ifndef DGB_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif

#define GLEW_STATIC 1

#include "LS_Simulator.h"

using namespace std;

void main(int argc, char **argv)
{

	//Used to check for Memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	CLS_Simulator::simulationInit(argc,argv);

	CLS_Simulator::mainLoop();

}

