#include "LS_Simulator3D.h"

#include <stdio.h>

bool					CLS_Simulator3D::fullscreen = false;
glm::vec2				CLS_Simulator3D::screenSize[WINDOW_COUNT];
glm::vec2				CLS_Simulator3D::mouseLocation = glm::vec2(0,0);
bool					CLS_Simulator3D::mouseButton[MOUSE_BUTTONS];
GLuint					CLS_Simulator3D::window[WINDOW_COUNT];
long long				CLS_Simulator3D::lastFrameTime = 0;
#ifdef _DEBUG
std::list<long long>	CLS_Simulator3D::frameRenderTime;
long					CLS_Simulator3D::averageRenderTime = 0;
#endif
//MAJOR Complete the 3D Simulation Class
CLS_Simulator3D::CLS_Simulator3D()
{
}

//TODO CLS_Simulator3D::~CLS_Simulator3D
CLS_Simulator3D::~CLS_Simulator3D()
{
}

//MAJOR CLS_Simulator3D::init
void CLS_Simulator3D::init(int argc, char ** argv)
{
	glutInit(&argc, argv);

	//Initilise the primary window
	initGlut();
	
#ifdef _DEBUG
	//Initilise the debug window
	debug_window_init();
#endif

}

//MAJOR CLS_Simulator3D::mainloop
void CLS_Simulator3D::mainloop()
{
	lastFrameTime = CLS_Simulator3D::getTimeStamp();
	while (true)
	{
		glutMainLoopEvent();
		for (int i = 0; i < WINDOW_COUNT; i++)
		{
			glutSetWindow(window[i]);
			glutPostRedisplay();
		}
		lastFrameTime = CLS_Simulator3D::getTimeStamp();
	}
}

void CLS_Simulator3D::setScreenSize(GLuint screenID, int width, int height, bool full_screen)
{
	//Make sure the size of the screen is a valid size
	if (width > 199 &&
		height > 199)
	{
		if (screenID == WINDOW_PRIMARY)
			fullscreen = full_screen;

		screenSize[screenID].x = width;
		screenSize[screenID].y = height;
	}
	else
		throw "Screen size too small";
}

//MAJOR CLS_Simulator3D::initGlut
void CLS_Simulator3D::initGlut()
{

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(CLS_Simulator3D::screenSize[WINDOW_PRIMARY].x, CLS_Simulator3D::screenSize[WINDOW_PRIMARY].y);
	glutInitWindowPosition(800, 0);
	window[WINDOW_PRIMARY] = glutCreateWindow("PhysicsTest");

	//as the display function is a static this call is made very easy.
	glutDisplayFunc(CLS_Simulator3D::display);
	glutKeyboardFunc(CLS_Simulator3D::event_keyboard);
	glutSpecialFunc(CLS_Simulator3D::event_keyboardSpecialKeys);
	glutPassiveMotionFunc(CLS_Simulator3D::event_MouseMovment);
	glutMotionFunc(CLS_Simulator3D::event_MouseMovment);
	glutMouseFunc(CLS_Simulator3D::event_mouseButtons);

}

//TODO CLS_Simulator3D::event_keyboard
void CLS_Simulator3D::event_keyboard(unsigned char, int, int)
{
}

//TODO CLS_Simulator3D::event_keyboardSpecialKeys
void CLS_Simulator3D::event_keyboardSpecialKeys(int, int, int)
{
}

//TODO CLS_Simulator3D::event_MouseMovment
void CLS_Simulator3D::event_MouseMovment(int x, int y)
{
	//set the mouse location
	mouseLocation.x = x;
	mouseLocation.y = y;
}

//TODO CLS_Simulator3D::event_mouseButtons
void CLS_Simulator3D::event_mouseButtons(int button, int state, int x, int y)
{
	if (button < MOUSE_BUTTONS)
	{
		mouseButton[button] = state == 1 ? false : true;
	}
}

void CLS_Simulator3D::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glutSwapBuffers();
}

/*This will draw to the screen in screen cordinates rather then world cordinates 
  This will be usefull for debugging text*/
void CLS_Simulator3D::screenPrint(int row, int col, const char *fmt, ...)
{
	//Sourced from the freeglut demo
	static char buf[256];
	int viewport[4];
	void *font = GLUT_BITMAP_9_BY_15;
	va_list args;
	glColor3d(0.1, 0.1, 0.4);
	va_start(args, fmt);

	(void)_vsnprintf(buf, sizeof(buf), fmt, args);

	va_end(args);

	glGetIntegerv(GL_VIEWPORT, viewport);

	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, viewport[2], 0, viewport[3], -1, 1);

	glRasterPos2i
	(
		glutBitmapWidth(font, ' ') * col,
		-glutBitmapHeight(font) * row + viewport[3]
	);
	glutBitmapString(font, (unsigned char*)buf);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

long long CLS_Simulator3D::getTimeStamp()
{
	static LARGE_INTEGER s_frequency;
	static long long timepoint;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		timepoint = (1000LL * now.QuadPart) / s_frequency.QuadPart;
	}
	else {
		timepoint = GetTickCount();
	}
#ifdef _DEBUG
	addTimePoint(timepoint - lastFrameTime);
#endif
	return timepoint;
}

#ifdef _DEBUG
//TODO CLS_Simulator3D::debug_window
void CLS_Simulator3D::debug_window_init()
{
	

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(CLS_Simulator3D::screenSize[WINDOW_DEBUG].x, CLS_Simulator3D::screenSize[WINDOW_DEBUG].y);
	glutInitWindowPosition(0, 0);
	window[WINDOW_DEBUG] = glutCreateWindow("Debug infomation");

	glClearColor(1, 1, 1, 1);

	//as the display function is a static this call is made very easy.
	glutDisplayFunc(CLS_Simulator3D::debug_window_display);
	glutIdleFunc(CLS_Simulator3D::debug_window_display);

}

void CLS_Simulator3D::debug_window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int row = 1;
	screenPrint(row++, 1, "Mouse location: { %.0f, %.0f }" , mouseLocation.x, mouseLocation.y);
	screenPrint(row++, 1, "Mouse buttons pressed: %s%s%s", mouseButton[0] ? "Left " : "", mouseButton[1] ? "Middle  " : "", mouseButton[2] ? "Right " : "");
	screenPrint(row++, 1, "SPF: %llu mS (%llu mS average over the last %i frames)", frameRenderTime.back(), (long long)(averageRenderTime / (int)NUMBER_OF_TIMEPOINTS), (int)NUMBER_OF_TIMEPOINTS);
	screenPrint(row++, 1, "FPS: %llu (%llu Average)", 1000 / frameRenderTime.back(), 1000 / ((long long)(averageRenderTime / (int)NUMBER_OF_TIMEPOINTS)));

	glutSwapBuffers();
}

void CLS_Simulator3D::addTimePoint(long long nextTimepoint)
{
	//Pust the time point to the back of the list
	frameRenderTime.push_back(nextTimepoint);

	// By adding this frome to a total time and subacting the time that get poped off we will save a small 
	// amount of processing power as we do not have to add all x number of timepoints every frame.
	averageRenderTime += nextTimepoint;

	//if the list is larger then the max pop the front
	while (frameRenderTime.size() > NUMBER_OF_TIMEPOINTS)
	{
		averageRenderTime -= frameRenderTime.front();
		frameRenderTime.pop_front();
	}
}
#endif
