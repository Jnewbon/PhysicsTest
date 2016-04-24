#pragma once
#include "glm/glm.hpp"
#include "GL\glew\glew.h"
#include "GL\glut.h"
#include "GL\freeglut.h"
#include <list>

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

	static void			setScreenSize(GLuint screenID, int width, int height, bool full_screen = false);

private:

	/* ####################### */
	/* ## Private Variables ## */
	/* ####################### */

	static bool			fullscreen;										//True id the view is to be fullscreen (Will only work on the forst windows created)
	static glm::vec2	screenSize[WINDOW_COUNT];						//Sets the size of the viewport
	static glm::vec2	mouseLocation;									//The mouse location on the window;
	static bool			mouseButton[MOUSE_BUTTONS];						//Will contain the state of all the mouse buttons

	static GLuint		window[WINDOW_COUNT];							//The identifers for the display windows

	static long long	lastFrameTime;									//this will contain the time th last frame was rendered

	/* ####################### */
	/* ## Private Functions ## */
	/* ####################### */

	// Glut Functions
	static void			initGlut();										//Initilises the Glut window for diplay use

	/* Event functions that happen inside the glut window 
	   These need to be static functions so they can be 
	   parsed into the glut as function pointers */
	static void			event_keyboard(unsigned char, int, int);		// Handels all the normal keys on the keyboard
	static void			event_keyboardSpecialKeys(int, int, int);		// Handel the Special keys on the keyboard eg Ctrl, Alt
	static void			event_MouseMovment(int, int);					// Handels the movment of the mouse in the window
	static void			event_mouseButtons(int, int, int, int);			// Handel the mouse buttons that are pressed

	static void			display();										// The display function
	static void			screenPrint(int, int, const char *, ...);		// Will print HUD text to the screen

	static long long	getTimeStamp();									//will return the timepoint the the function is called
#ifdef _DEBUG

	static std::list<long long> frameRenderTime;						//Will contain a stack of time that it took to render the last {NUMBER_OF_TIMEPOINTS} frames
	static long			averageRenderTime;								//will contain the total time it took to render the last {NUMBER_OF_TIMEPOINTS} frames

	//TODO Add the rest of the debug window
	static void			debug_window_init();							//Will create a second glut windows for debugging perposes
	static void			debug_window_display();							//The display for the debug window
	static void			addTimePoint(long long);
#endif



};

