
//This will determin if the program will use the shaders or not



#include "LS_Simulator.h"
#include "LS_Circle.h"
#include "CLS_Line.h"
#include "LS_VectorPoint.h"
#include "LS_Physics.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#ifdef GLUseShader
	#include "shader_setup.h"
#endif // GLUseShader


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
CLS_Shapes *CLS_Simulator::tempObject = nullptr;

#ifdef GLUseShader
GLuint CLS_Simulator::shaderProgram = 0;

#endif // GLUseShader

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
	glutCreateWindow("PhysicsTest");
	
	//as the display function is a static this call is made very easy.
	glutDisplayFunc(CLS_Simulator::display);
	glutKeyboardFunc(CLS_Simulator::keyHandler);
	glutSpecialFunc(CLS_Simulator::specialKeyHandler);
	glutPassiveMotionFunc(CLS_Simulator::activeMouseHandler);
	glutMotionFunc(CLS_Simulator::activeMouseHandler);
	glutMouseFunc(CLS_Simulator::mouseFunc);


	//Initilized glew and output if successful
	GLenum err = glewInit();
	screen.output("GLEW Setup..");
	if (err == GLEW_OK)
	{	screen.outputNL("SUCCEEDED");	}
	else
	{	screen.outputNL("FAILED");	}
	
	glClearColor(0.5,0.5,0.5,1.0);
	//wglSwapIntervalEXT(50);
#ifndef GLUseShader
	//this is only needed if the shaders are not in use, as the matrices take care of this in the draw function
	glOrtho(-(SCREEN_X / 2), (SCREEN_X / 2), -(SCREEN_Y / 2), (SCREEN_Y / 2), -1.0, 1.0);

#endif // GLUseShader

	//glutFullScreenToggle();

#ifdef GLUseShader
	shaderProgram = setupShaders("Resources//basic_vertex_shader.vert", "Resources//basic_fragment_shader.frag");

#endif // GLUseShader

	CLS_Physics::setScreenSize(CLS_VectorPoint<float>(SCREEN_X,SCREEN_Y));
	//Non CCD is currently broken. (Circ - Circ, Circ - line Works, and the speed of all objects is slowed)
	CLS_Physics::CCDStaus(true, 10);

#ifdef SHOW_DETAILS
	screen.outputNL("SPF:");
	screen.outputNL("FPS:");
	screen.outputNL("Collision Counter:");
	screen.outputNL("Number of Objects:");
#endif
	
	//Initilize the Circle Template
	CLS_Circle::initCirc();

	// #### Test object
	CLS_Circle* newObject;
	srand(0);	
	//newObject = new CLS_Circle();
	////Set the objects attributes
	//newObject->setLocation(CLS_VectorPoint<float>(300.0f,0.0f));
	//newObject->setSpeed(CLS_VectorPoint<float>(-40.0f,0.0f));
	//newObject->setMass(100.0f);
	//newObject->setColour(1.0f,0.0f,0.0f, 1.0f);
	//newObject->setBounceFactor(-0.001f);


	////Push the object into the vector
	//objects.push_back(newObject);	
	//

	//newObject = new CLS_Circle();
	////Set the objects attributes
	//newObject->setLocation(glm::vec3(0.0f, 300.0f, 0.0f));
	//newObject->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
	//newObject->setMass(7.0f);
	//newObject->setColour(glm::vec4(float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, 1.0f));
	//newObject->setBounceFactor(-0.001f);
	//newObject->setScale(20.0f);


	//////Push the object into the vector
	//objects.push_back(newObject);

	//for (int i = 0; i < 10; i++)
	//{
	//	newObject = new CLS_Circle();
	//	//Set the objects attributes
	//	newObject->setLocation(glm::vec3(-300.0f + i*40.0f, 350.0f, 0.0f));
	//	newObject->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
	//	newObject->setMass(7.0f + float(i));
	//	newObject->setColour(glm::vec4(float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, 1.0f));
	//	newObject->setBounceFactor(0.4f);
	//	newObject->setScale(7.0f + float(i));

	//	//Push the object into the vector
	//	objects.push_back(newObject);
	//}
	////bool vSync = wglSwapIntervalEXT(1);

	//CLS_Line *newLine = new CLS_Line();
	////Set the objects attributes
	//newLine->setLocation(glm::vec3(0.0f, 200.0f, 0.0f));
	//newLine->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
	//newLine->setMass(7.0f);
	//newLine->setColour(glm::vec4(float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, 1.0f));
	//newLine->setBounceFactor(-0.001f);
	//newLine->setScale(1.0f);
	//newLine->setPointOne(-400.0, 50.0, 0.0);
	//newLine->setPointTwo(300.0, -50.0, 0.0);
	//newLine->setMovableStatus(false);

	////Push the object into the vector
	//objects.push_back(newLine);

	//newLine = new CLS_Line();
	////Set the objects attributes
	//newLine->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
	//newLine->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
	//newLine->setMass(7.0f);
	//newLine->setColour(glm::vec4(float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, 1.0f));
	//newLine->setBounceFactor(-0.001f);
	//newLine->setScale(1.0f);
	//newLine->setPointOne(-300, -50.0, 0.0);
	//newLine->setPointTwo(400.0, 50.0, 0.0);
	//newLine->setMovableStatus(false);

	////Push the object into the vector
	//objects.push_back(newLine);

	//newLine = new CLS_Line();
	////Set the objects attributes
	//newLine->setLocation(glm::vec3(0.0f, -200.0f, 0.0f));
	//newLine->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
	//newLine->setMass(7.0f);
	//newLine->setColour(glm::vec4(float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, 1.0f));
	//newLine->setBounceFactor(-0.001f);
	//newLine->setScale(1.0f);
	//newLine->setPointOne(-400.0, 50.0, 0.0);
	//newLine->setPointTwo(300.0, -50.0, 0.0);
	//newLine->setMovableStatus(false);

	////Push the object into the vector
	//objects.push_back(newLine);


	quit = false;
}

void CLS_Simulator::mainLoop() {


	lastTimePoint = CLS_Simulator::elapsedTime();

	
	while(!quit)
	{
		glutMainLoopEvent();

		glutPostRedisplay();

		timePoints.push_back(float(CLS_Simulator::elapsedTime() - lastTimePoint));

		if (timePoints.size() > 100)
		{

			long long tempTimePoint = 0;

			for(int i = 0; i < timePoints.size(); i++)
			{
				tempTimePoint += timePoints[i];
			}

#ifdef SHOW_DETAILS
			ostringstream stream;
			stream << (CLS_Simulator::elapsedTime() - lastTimePoint)/1000.0f;
			//stream << (float(tempTimePoint)/float(timePoints.size()))/1000.0f;

			screen.outputPos(6,1, "             ");
			screen.outputPos(6,1, stream.str());
			
			stream.str("");
			
			stream << 1000.0f / (tempTimePoint / float(timePoints.size()));
			
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
#endif
			timePoints.clear();

		}
		
		/*for(vector<CLS_Shapes*>::iterator i = objects.begin(); i != objects.end(); i++)
		{

			CLS_Physics::applyGravity(CLS_Simulator::elapsedTime() - lastTimePoint,(*i));
			CLS_Physics::applyObjectMovment(CLS_Simulator::elapsedTime() - lastTimePoint,(*i));
		}*/

		CLS_Physics::applyPhysics(CLS_Simulator::elapsedTime() - lastTimePoint, &objects);

		lastTimePoint = CLS_Simulator::elapsedTime();

	}

}

void CLS_Simulator::display() {

#ifdef GLUseShader
	glUseProgram(shaderProgram);

	glm::mat4 orthomatrix = glm::ortho(float(-SCREEN_X/2), float(SCREEN_X/2), float(-SCREEN_Y/2), float(SCREEN_Y/2),-1.0f,1.0f);

	GLuint matrixTransLoc = glGetUniformLocation(shaderProgram, "viewMatrix");

	glUniformMatrix4fv(matrixTransLoc, 1, GL_FALSE, &orthomatrix[0][0]);

#endif // GLUseShader


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for(vector<CLS_Shapes*>::iterator i = objects.begin(); i != objects.end(); i++)
	{
#ifdef GLUseShader
		(*i)->draw(shaderProgram);
#else
		(*i)->draw();
#endif // GLUseShader


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

void CLS_Simulator::mouseFunc(int button, int state, int x, int y)
{
	if (button == 0 && state == 1)
	{

		CLS_Circle *newObject = new CLS_Circle();
		//Set the objects attributes
		newObject->setLocation(glm::vec3(x - 400, 400 - y, 0.0f));
		newObject->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
		newObject->setMass(7.0f);
		newObject->setColour(glm::vec4(float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, 1.0f));
		newObject->setBounceFactor(0.75f);
		newObject->setScale(15.0f);

		//Push the object into the vector
		objects.push_back(newObject);
	}
	if (button == 1 && state == 1)
	{

		CLS_Circle *newObject = new CLS_Circle();
		//Set the objects attributes
		newObject->setLocation(glm::vec3(x - 400, 400 - y, 0.0f));
		newObject->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
		newObject->setMass(50.0f);
		newObject->setColour(glm::vec4(float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, 1.0f));
		newObject->setBounceFactor(0.75f);
		newObject->setScale(25.0f);

		//Push the object into the vector
		objects.push_back(newObject);
	}
	if (button == 2 && state == 0)
	{
		CLS_Line *newLine = new CLS_Line();

		newLine->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
		newLine->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
		newLine->setMass(7.0f);
		newLine->setColour(glm::vec4(float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, float(rand() % 255) / 255.0f, 1.0f));
		newLine->setBounceFactor(0.75f);
		newLine->setScale(1.0f);
		newLine->setPointOne(x - 400, 400 - y, 0.0);
		newLine->setMovableStatus(false);

		tempObject = newLine;


	}
	if (button == 2 && state == 1)
	{
		((CLS_Line*)tempObject)->setPointTwo(x - 400, 400 - y, 0.0);

		objects.push_back(tempObject);

		tempObject = nullptr;
	}
}