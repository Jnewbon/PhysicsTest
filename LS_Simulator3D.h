#pragma once
#include "glm/glm.hpp"
#include "GL\glew\glew.h"
#include "GL\glut.h"
#include "GL\freeglut.h"
#include <vector>
#include <list>
#include "LS_Shapes.h"

#define MOUSE_BUTTONS		3		//The number of buttons the mouse has



enum glut_windows{
	WINDOW_PRIMARY,
#ifdef _DEBUG
	WINDOW_DEBUG,
#endif
	WINDOW_COUNT
};

#ifdef _DEBUG
	#define NUMBER_OF_TIMEPOINTS	10	//this is the number of timepoint the function will keep when debugging
#endif


class CLS_Simulator3D
{
public:
	CLS_Simulator3D();
	~CLS_Simulator3D();

	//Initilisation for the simulator
	static void			init(int argc, char **argv);

	/* This will be the Simulations main loop; Return from this means end of program */
	static void			mainloop();

	static void			setScreenSizeLoc(GLuint screenID,int top, int left, int width, int height, bool full_screen = false);

private:

	/* ####################### */
	/* #Private Enumerations## */
	/* ####################### */
	enum cameraMatracies {
			CAM_PERSPECTIVE,
			NUM_OF_CAMERA_MATX
		};

	/* ####################### */
	/* ## Private Variables ## */
	/* ####################### */

	static bool			fullscreen;										//True id the view is to be fullscreen (Will only work on the forst windows created)
	static glm::vec2	screenLocation[WINDOW_COUNT];					//Sets the location of the viewports
	static glm::vec2	screenSize[WINDOW_COUNT];						//Sets the size of the viewports
	static glm::vec2	mouseLocation;									//The mouse location on the window;
	static bool			mouseButton[MOUSE_BUTTONS];						//Will contain the state of all the mouse buttons
	static glm::vec3	cameraLocation;									//will contain the location of the camera
	static glm::vec2	cameraRotation;									//will contain the current updown and side to side rotation of the camera

#ifdef GLUseShader
	static glm::mat4	camera[NUM_OF_CAMERA_MATX];						//This will contain the matricies that the camera needs to function normally
#endif

	static GLuint		window[WINDOW_COUNT];							//The identifers for the display windows

	static long long	lastFrameTime;									//this will contain the time th last frame was rendered

	const static glm::vec2 worldSize;									//will contain the world size
	static glm::vec2	screenAspectRatio;								//will contain the world size


	static std::vector<CLS_Shapes*> objects;

	/* ####################### */
	/* ## Private Functions ## */
	/* ####################### */

	// Glut Functions
	static void			initGlut();										//Initilises the Glut window for diplay use

	/* Event functions that happen inside the glut window 
	   These need to be static functions so they can be 
	   parsed into the glut as function pointers */
	static void			event_keyboard(unsigned char, int, int);		// Handels all the normal keys on the keyboard
	static void			event_keyboardSpecialKeys(int, int, int);		// Handels the Special keys on the keyboard eg Ctrl, Alt
	static void			event_MouseMovment(int, int);					// Handels the movment of the mouse in the window
	static void			event_mouseButtons(int, int, int, int);			// Handels the mouse buttons that are pressed
	static void			event_screenResize(int, int);					// Handles the resizing of the viewport

	static void			display();										// The display function
	static void			screenPrint(int, int, const char *, ...);		// Will print HUD text to the screen

	static long long	getTimeStamp();									//will return the timepoint the the function is called
#ifdef _DEBUG

	static std::list<long long> frameRenderTime;						//Will contain a stack of time that it took to render the last {NUMBER_OF_TIMEPOINTS} frames
	static long			averageRenderTime;								//will contain the total time it took to render the last {NUMBER_OF_TIMEPOINTS} frames

	static void			debug_window_init();							//Will create a second glut windows for debugging perposes
	static void			debug_window_display();							//The display for the debug window
	static void			addTimePoint(long long);
#endif



};

