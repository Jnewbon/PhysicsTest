#pragma once

#include <string>

#include "LS_ConsoleInterface.h"
class CLS_Screen
{
public:
	CLS_Screen(void);
	~CLS_Screen(void);

	void output(std::string);
	void outputNL(std::string);
	void outputPos(int x, int y, std::string);

	CLS_ConsoleInterface* getConsole();

private:

	CLS_ConsoleInterface console;

};

