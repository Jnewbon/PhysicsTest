#pragma once

#include "options.h"
#include "LS_Shapes.h"

#include "GL\glew\glew.h"
#include "GL\glut.h"
#include "GL\freeglut.h"

class CLS_Circle:public CLS_Shapes
{
private:


public:
	CLS_Circle(void);
	~CLS_Circle(void);

	static GLuint circleTemplateVAO;

	static void initCirc();

	void setScale(float);

	//void draw();
	
};

