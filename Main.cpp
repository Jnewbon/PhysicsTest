


#include "options.h"
#include "LS_Simulator.h"
#include "LS_Simulator3D.h"

using namespace std;

void main(int argc, char **argv)
{

#ifdef _DEBUG
	//Used to check for Memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	CLS_Simulator3D::setScreenSize(WINDOW_PRIMARY, 800, 800);
#ifdef _DEBUG
	CLS_Simulator3D::setScreenSize(WINDOW_DEBUG, 500, 200);
#endif


	CLS_Simulator3D::init(argc,argv);




	CLS_Simulator3D::mainloop();
	system("PAUSE");
}

