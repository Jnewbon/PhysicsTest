#ifndef _OPTIONS_H
#define _OPTIONS_H
//This file shall contain the #define for the entire program

//if defined the program will use shaders and glm::matrices instead of pushing to the glStack
//#define GLUseShader

//This needs to be used otherwise glm::vec's cannot be parsed into methods
#define GLM_FORCE_PURE

//And this is for Release building
#define GLEW_STATIC 1

//This will tell the program to output detals of the FPS and Objects to the screen
#define SHOW_DETAILS

//This will tell the program to highlight objects that are colliding
//#define SHOW_COLLISION_HIGHLIGHT

//This is for memory leak detection
#ifdef _DEBUG 
	#ifndef DGB_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif
#endif