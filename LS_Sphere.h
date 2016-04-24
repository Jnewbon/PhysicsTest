#pragma once
#include "LS_Shapes.h"
class CLS_Sphere :
	public CLS_Shapes
{
public:
	CLS_Sphere();
	~CLS_Sphere();

#ifdef GLUseShader
	void draw(GLuint shaderProgram);
#else
	void draw();
#endif

};

