
#include "LS_Simulator.h"
#include "LS_Circle.h"
#include "LS_VectorPoint.h"
#include "LS_Physics.h"

#include <time.h>
#include <sstream>

using namespace std;

const int SCREEN_X = 800;
const int SCREEN_Y = 800;

CLS_Screen CLS_Simulator::screen;
std::vector<CLS_Shapes*> CLS_Simulator::objects;
long long CLS_Simulator::lastTimePoint = 0;
bool CLS_Simulator::quit = false;
std::vector<float> CLS_Simulator::timePoints;

CLS_Simulator::~CLS_Simulator(void)
{
	for(vector<CLS_Shapes*>::iterator i = objects.begin(); i != objects.end(); i++)
	{

		delete (*i);

	}
}

void CLS_Simulator::simulationInit(int argc, char **argv) {

	glutInit(&argc,argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(SCREEN_X,SCREEN_Y);
	glutInitWindowPosition(800,0);
	glutCreateWindow("This be the freeking window yo!");
	
	//as the display function is a static this call is made very easy.
	glutDisplayFunc(CLS_Simulator::display);
	glutKeyboardFunc(CLS_Simulator::keyHandler);
	glutSpecialFunc(CLS_Simulator::specialKeyHandler);
	glutPassiveMotionFunc(CLS_Simulator::activeMouseHandler);
	glutMotionFunc(CLS_Simulator::activeMouseHandler);


	//Initilized glew and output if successful
	GLenum err = glewInit();
	screen.output("GLEW Setup..");
	if (err == GLEW_OK)
	{	screen.outputNL("SUCCEEDED");	}
	else
	{	screen.outputNL("FAILED");	}
	
	glClearColor(0.5,0.5,0.5,1.0);
	glOrtho(-(SCREEN_X/2),(SCREEN_X/2),-(SCREEN_Y/2),(SCREEN_Y/2),-1.0,1.0);

	//glutFullScreenToggle();

	CLS_Physics::setScreenSize(CLS_VectorPoint<float>(SCREEN_X,SCREEN_Y));

	screen.outputNL("SPF:");
	screen.outputNL("FPS:");
	screen.outputNL("Collision Counter:");
	screen.outputNL("Number of Objects:");


	//Initilize the Circle Template
	CLS_Circle::initCirc();

	// #### Test object

	CLS_Circle* newObject;
	//newObject = new CLS_Circle();
	////Set the objects attributes
	//newObject->setLocation(CLS_VectorPoint<float>(-300.0f,0.0f));
	//newObject->setSpeed(CLS_VectorPoint<float>(-2,0));
	//newObject->setMass(100.0f);
	//newObject->setColour(255,0,0);
	//newObject->setBounceFactor(-0.001f);


	////Push the object into the vector
	//objects.push_back(newObject);

	for (int i = 0; i < 15; i++)
	{
		newObject = new CLS_Circle();
		//Set the objects attributes
		newObject->setLocation(CLS_VectorPoint<float>(-300.0f + i*40.0f,-300.0f + i*40.0f));
		newObject->setSpeed(CLS_VectorPoint<float>(-2,0));
		newObject->setMass(10.0f);
		newObject->setColour(255,255,255);
		newObject->setBounceFactor(-0.001f);


		//Push the object into the vector
		objects.push_back(newObject);
	}
	//bool vSync = wglSwapIntervalEXT(1);
	quit = false;
}

void CLS_Simulator::mainLoop() {


	lastTimePoint = CLS_Simulator::elapsedTime();

	
	while(!quit)
	{
		glutMainLoopEvent();

		glutPostRedisplay();

		timePoints.push_back(float(CLS_Simulator::elapsedTime() - lastTimePoint));

		if (timePoints.size() > 10)
		{

			long long tempTimePoint = 0;

			for(int i = 0; i < timePoints.size(); i++)
			{
				tempTimePoint += timePoints[i];
			}

			ostringstream stream;
			stream << (CLS_Simulator::elapsedTime() - lastTimePoint)/1000.0f;
			//stream << (float(tempTimePoint)/float(timePoints.size()))/1000.0f;

			screen.outputPos(6,1, "             ");
			screen.outputPos(6,1, stream.str());
			
			stream.str("");
			
			stream << 1000.0f/(CLS_Simulator::elapsedTime() - lastTimePoint);
			
			//stream << 1000.0f / ((float(tempTimePoint)/float(timePoints.size()))/1000.0f);

			screen.outputPos(6,2, "             ");
			screen.outputPos(6,2, stream.str());
			
			stream.str("");
			
			stream << CLS_Physics::collisionCounter;

			screen.outputPos(19,3, "             ");
			screen.outputPos(19,3, stream.str());

			stream.str("");
			
			stream << objects.size();

			screen.outputPos(19,4, "             ");
			screen.outputPos(19,4, stream.str());

			timePoints.clear();

		}
		
		for(vector<CLS_Shapes*>::iterator i = objects.begin(); i != objects.end(); i++)
		{

			CLS_Physics::applyGravity(CLS_Simulator::elapsedTime() - lastTimePoint,(*i));
			CLS_Physics::applyObjectMovment(CLS_Simulator::elapsedTime() - lastTimePoint,(*i));
		}

		CLS_Physics::applyPhysics(CLS_Simulator::elapsedTime() - lastTimePoint, &objects);

		lastTimePoint = CLS_Simulator::elapsedTime();

	}

}

void CLS_Simulator::display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for(vector<CLS_Shapes*>::iterator i = objects.begin(); i != objects.end(); i++)
	{
		CLS_Shapes* temp = (*i);

		temp->draw();
		//(*i)->draw();

	}
	glutSwapBuffers();
}

void CLS_Simulator::keyHandler(unsigned char key, int x, int y)
{
	if (key = 'q')
		quit = true;
}

void CLS_Simulator::specialKeyHandler(int key , int x, int y)
{

}

void CLS_Simulator::activeMouseHandler(int x, int y)
{

}

long long CLS_Simulator::elapsedTime() {
	static LARGE_INTEGER s_frequency;
    static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    if (s_use_qpc) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    } else {
        return GetTickCount();
    }
}
