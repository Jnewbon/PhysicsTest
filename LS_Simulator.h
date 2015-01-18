#if !defined(_CLS_SIMULATOR_H)
#define _CLS_SIMULATOR_H

#include <vector>


#include "GL\glew\glew.h"
#include "GL\glut.h"
#include "GL\freeglut.h"
#include "GL\glew\wglew.h"

#include "LS_Shapes.h"
#include "LS_Screen.h"

class CLS_Simulator {
public:

	static void simulationInit(int argc, char **argv);
	static void mainLoop();

private:

	~CLS_Simulator(void);
	static CLS_Screen screen;
	static std::vector<CLS_Shapes*> objects;
	static long long lastTimePoint;
	static std::vector<float> timePoints;

	static void display();

	static bool quit;

	static void keyHandler(unsigned char, int, int);
	static void specialKeyHandler(int, int, int);
	static void activeMouseHandler(int, int);

	static long long elapsedTime();
};


#endif  //_CLS_SIMULATOR_H
