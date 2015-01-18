#include "LS_Screen.h"
#include <iostream>

CLS_Screen::CLS_Screen(void)
{
	//Becose White text on a blck screen is too comman
	console.setColour(console.LIGHT_BLUE,console.GRAY);
	//Clear the screnn to make the changes visible
	console.clear();

}


CLS_Screen::~CLS_Screen(void)
{
	//Nothing to do here
}

void CLS_Screen::output(std::string text)
{
	std::cout << text;
}

void CLS_Screen::outputNL(std::string  text)
{
	std::cout << text << std::endl;
}

void CLS_Screen::outputPos(int x, int y, std::string  text)
{
	console.gotoXY(x,y);
	std::cout << text;
}


CLS_ConsoleInterface* CLS_Screen::getConsole()
{
	return &this->console;
}
