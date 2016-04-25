#pragma once
#include "LS_Shapes.h"
class CLS_Sphere :
	public CLS_Shapes
{
public:
	CLS_Sphere();
	~CLS_Sphere();

	void setScale(float);

#ifdef GLUseShader
	void draw(GLuint shaderProgram);
#else
	void draw();
#endif

};

