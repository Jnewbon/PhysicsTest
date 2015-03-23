#pragma once
#include "LS_Shapes.h"
class CLS_Line :
	public CLS_Shapes
{

private:

	glm::vec3 point1;
	glm::vec3 point2;

public:
	CLS_Line();
	~CLS_Line();


	void draw(GLuint);

	void setPointOne(double, double, double);
	void setPointTwo(double, double, double);
	glm::vec3 getPointOne();
	glm::vec3 getPointTwo();


};

