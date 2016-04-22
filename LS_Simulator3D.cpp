#include "LS_Simulator3D.h"


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
}

//MAJOR CLS_Simulator3D::mainloop
void CLS_Simulator3D::mainloop()
{
}

void CLS_Simulator3D::setScreenSize(int width, int height, bool fullscreen)
{
	//Make sure the size of the screen is a valid size
	if (width > 480 &&
		height > 640)
	{
		this->fullscreen = fullscreen;
		this->screenSize.x = width;
		this->screenSize.y = height;
	}
	else
		throw "Screen size too small";
}

//MAJOR CLS_Simulator3D::initGlut
void CLS_Simulator3D::initGlut(int argc, char ** argv)
{
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
void CLS_Simulator3D::event_MouseMovment(int, int)
{
}

//TODO CLS_Simulator3D::event_mouseButtons
void CLS_Simulator3D::event_mouseButtons(int, int, int, int)
{
}

#ifdef DEBUG
//TODO CLS_Simulator3D::debug_window
void CLS_Simulator3D::debug_window()
{
}
#endif
