#pragma once
#include "glm/glm.hpp"
class CLS_Simulator3D
{
public:
	CLS_Simulator3D();
	~CLS_Simulator3D();

	//Initilisation for the simulator
	void init(int argc, char **argv);

	/* This will be the Simulations main loop; Return from this means end of program */
	void mainloop();

	void setScreenSize(int width, int height, bool fullscreen);

private:

	/* ####################### */
	/* ## Private Variables ## */
	/* ####################### */

	bool			fullscreen;		//True id the view is to be fullscreen
	glm::vec2		screenSize;		//Sets the size of the viewport

	/* ####################### */
	/* ## Private Functions ## */
	/* ####################### */

	// Glut Functions
	static void			initGlut(int argc, char **argv);	//Initilises the Glut window for diplay use

	/* Event functions that happen inside the glut window 
	   These need to be static functions so they can be 
	   parsed into the glut as function pointers */
	static void			event_keyboard(unsigned char, int, int);		// Handels all the normal keys on the keyboard
	static void			event_keyboardSpecialKeys(int, int, int);		// Handel the Special keys on the keyboard eg Ctrl, Alt
	static void			event_MouseMovment(int, int);					// Handels the movment of the mouse in the window
	static void			event_mouseButtons(int, int, int, int);			// Handel the mouse buttons that are pressed

#ifdef DEBUG
	//TODO Add the rest of the debug window
	static void			debug_window();									//Will create a second glut windows for debugging perposes
#endif



};

