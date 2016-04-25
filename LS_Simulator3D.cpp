#include "LS_Simulator3D.h"
#include "LS_Sphere.h"
#include "LS_Physics.h"

#include <stdio.h>

bool					CLS_Simulator3D::fullscreen = false;
glm::vec2				CLS_Simulator3D::screenLocation[WINDOW_COUNT];
glm::vec2				CLS_Simulator3D::screenSize[WINDOW_COUNT];
glm::vec2				CLS_Simulator3D::mouseLocation = glm::vec2(0,0);
bool					CLS_Simulator3D::mouseButton[MOUSE_BUTTONS];
glm::vec3				CLS_Simulator3D::cameraLocation = glm::vec3(0, 0, 0);
glm::vec2				CLS_Simulator3D::cameraRotation = glm::vec2(0, 0);
GLuint					CLS_Simulator3D::window[WINDOW_COUNT];
long long				CLS_Simulator3D::lastFrameTime = 0;
const glm::vec2			CLS_Simulator3D::worldSize = glm::vec2(10, 10);
glm::vec2				CLS_Simulator3D::screenAspectRatio = glm::vec2(1,1);
std::vector<CLS_Shapes*>	CLS_Simulator3D::objects;
#ifdef _DEBUG
std::list<long long>	CLS_Simulator3D::frameRenderTime;
long					CLS_Simulator3D::averageRenderTime = 0;
#endif


CLS_Simulator3D::CLS_Simulator3D()
{	
}

//TODO CLS_Simulator3D::~CLS_Simulator3D
CLS_Simulator3D::~CLS_Simulator3D()
{
}

void CLS_Simulator3D::init(int argc, char ** argv)
{
	glutInit(&argc, argv);

	//Initilise the primary window
	initGlut();
	
#ifdef _DEBUG
	//Initilise the debug window
	debug_window_init();
#endif

	//Initilized glew and output if successful
	GLenum err = glewInit();

	printf("GLEW Setup... ");
	if (err == GLEW_OK)
	{
		printf("OK");
	}
	else
	{
		printf("FAILED");
	}
	int glMajor, glMinor = 0;

	glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
	glGetIntegerv(GL_MINOR_VERSION, &glMinor);

	printf("\nOpenGL Version: %i.%i", glMajor, glMinor);
	(true);
	//TODO Change to glm::vec2
	CLS_Physics::setScreenSize(CLS_VectorPoint<float>(worldSize.x, worldSize.y));
	CLS_Physics::CCDStaus(false, 5);

}

//MINOR CLS_Simulator3D::mainloop
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
		while (CLS_Simulator3D::getTimeStamp() - lastFrameTime < 16)
		{ }
		CLS_Physics::applyPhysics(CLS_Simulator3D::getTimeStamp() - lastFrameTime, &objects);

		lastFrameTime = CLS_Simulator3D::getTimeStamp();
		
	}
}

void CLS_Simulator3D::setScreenSizeLoc(GLuint screenID, int top, int left, int width, int height, bool full_screen)
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

	screenLocation[screenID].x = left;
	screenLocation[screenID].y = top;

}

void CLS_Simulator3D::initGlut()
{

	glutInitContextVersion(4, 5);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(CLS_Simulator3D::screenSize[WINDOW_PRIMARY].x, CLS_Simulator3D::screenSize[WINDOW_PRIMARY].y);
	glutInitWindowPosition(screenLocation[WINDOW_PRIMARY].x, screenLocation[WINDOW_PRIMARY].y);
	window[WINDOW_PRIMARY] = glutCreateWindow("PhysicsTest");
	glClearColor(1, 1, 1, 1);

	//as the display function is a static this call is made very easy.
	glutDisplayFunc(CLS_Simulator3D::display);
	glutKeyboardFunc(CLS_Simulator3D::event_keyboard);
	glutSpecialFunc(CLS_Simulator3D::event_keyboardSpecialKeys);
	glutPassiveMotionFunc(CLS_Simulator3D::event_MouseMovment);
	glutMotionFunc(CLS_Simulator3D::event_MouseMovment);
	glutMouseFunc(CLS_Simulator3D::event_mouseButtons);
	glutReshapeFunc(CLS_Simulator3D::event_screenResize);

}

//TODO CLS_Simulator3D::event_keyboard
void CLS_Simulator3D::event_keyboard(unsigned char, int, int)
{
}

//TODO CLS_Simulator3D::event_keyboardSpecialKeys
void CLS_Simulator3D::event_keyboardSpecialKeys(int, int, int)
{
}

void CLS_Simulator3D::event_MouseMovment(int x, int y)
{
	if (mouseButton[GLUT_RIGHT_BUTTON])
	{
		if (cameraRotation.y >= -90 && cameraRotation.y <= 90)
			cameraRotation.y += mouseLocation.y - y;
		else if (cameraRotation.y < -90)
			cameraRotation.y = -90;
		else 
			cameraRotation.y = 90;

		cameraRotation.x += mouseLocation.x - x;
		if (cameraRotation.x > 360)
			cameraRotation.x -= 360;
		else if (cameraRotation.x < 0)
			cameraRotation.x += 360;
		/*if (cameraRotation.y > 360)
			cameraRotation.y -= 360;
		else if (cameraRotation.y < 0)
			cameraRotation.y += 360;*/

	}
	//set the mouse location
	mouseLocation.x = x;
	mouseLocation.y = y;
}


void CLS_Simulator3D::event_mouseButtons(int button, int state, int x, int y)
{
	if (button < MOUSE_BUTTONS)
	{
		mouseButton[button] = state == 1 ? false : true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		CLS_Sphere *newObject = new CLS_Sphere();
		//Set the objects attributes
		newObject->setLocation(glm::vec3(
											(worldSize.x * (x / screenSize[WINDOW_PRIMARY].x)) - (worldSize.x /2),
											-((worldSize.y * (y / screenSize[WINDOW_PRIMARY].y)) - (worldSize.y /2))
											, 0.0f));
		newObject->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
		newObject->setMass(7.0f);
		newObject->setColour(glm::vec4(float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, 1.0f));
		newObject->setBounceFactor(0.8f);
		newObject->setScale(1.0f);
		printf("\nObject Created at: { %.3f, %.3f, %.3f }", newObject->getLocation().x, newObject->getLocation().y, newObject->getLocation().z);
		objects.push_back(newObject);
	}


}

void CLS_Simulator3D::event_screenResize(int width, int height)
{
	screenAspectRatio.y = float(height) / float(width);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(	-(worldSize.x / 2) * screenAspectRatio.y,
				 (worldSize.x / 2) * screenAspectRatio.y,
				-(worldSize.y / 2) * screenAspectRatio.x,
				 (worldSize.y / 2) * screenAspectRatio.x,
				-400, 400);

	printf("\nScreen Resized to { %i, %i } new Aspect Ratio { %.3f, %.3f }", width, height, screenAspectRatio.x, screenAspectRatio.y);

	
	//glutPostRedisplay();
}

//TODO CLS_Simulator3D::display
void CLS_Simulator3D::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glRotatef(cameraRotation.x, 0.0f, 0.5f, 0.0f);
	glRotatef(cameraRotation.y, -0.5f, 0.0f, 0.0f);

	//glColor3f(0.0f,0.0f,0.0f);

	//glutSolidSphere(1.0f, 20, 20);

	

	for (std::vector<CLS_Shapes*>::iterator i = objects.begin(); i != objects.end(); i++)
	{
#ifdef GLUseShader
		(*i)->draw(shaderProgram);
#else
		(*i)->draw();
#endif 
	}

	glPopMatrix();
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

void CLS_Simulator3D::debug_window_init()
{
	
	glutInitContextVersion(4, 5);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(screenSize[WINDOW_DEBUG].x, screenSize[WINDOW_DEBUG].y);
	glutInitWindowPosition(screenLocation[WINDOW_DEBUG].x, screenLocation[WINDOW_DEBUG].y);
	window[WINDOW_DEBUG] = glutCreateWindow("Debug infomation");

	glClearColor(1, 1, 1, 1);

	//as the display function is a static this call is made very easy.
	glutDisplayFunc(CLS_Simulator3D::debug_window_display);

}

void CLS_Simulator3D::debug_window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int row = 1;
	screenPrint(row++, 1, "Mouse location: {%3.0f,%3.0f}", mouseLocation.x, mouseLocation.y);
	screenPrint(row++, 1, "Camera location: {%3.0f,%3.0f,%3.0f} Rotation: {%3.0f,%3.0f}", cameraLocation.x, cameraLocation.y, cameraLocation.z, cameraRotation.x,cameraRotation.y);
	screenPrint(row++, 1, "Mouse buttons pressed: %s%s%s", mouseButton[0] ? "Left " : "", mouseButton[1] ? "Middle  " : "", mouseButton[2] ? "Right " : "");
	screenPrint(row++, 1, "SPF: %4llu mS (%4llu mS average over the last %i frames)", frameRenderTime.back(), (long long)(averageRenderTime / (int)NUMBER_OF_TIMEPOINTS), (int)NUMBER_OF_TIMEPOINTS);
	screenPrint(row++, 1, "FPS: %4llu (%4llu Average)", 1000 / frameRenderTime.back(), 1000 / ((long long)(averageRenderTime / (int)NUMBER_OF_TIMEPOINTS)));
	screenPrint(row++, 1, "Number of Objects: %i Number of Collisions %llu", objects.size(), CLS_Physics::collisionCounter);
	for (int i = 0; i < objects.size(); i++)
	{
		screenPrint(row++, 1, "Object %i Speed: {%3.3f,%3.3f}",i, objects[i]->getSpeed().x, objects[i]->getSpeed().y);
	}

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
