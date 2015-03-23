#include "CLS_Line.h"

#include "glm\gtc\matrix_transform.hpp"

CLS_Line::CLS_Line()
{
	this->setType(LINE);

}


CLS_Line::~CLS_Line()
{
}

void CLS_Line::draw(GLuint shaderProgram)
{
	GLuint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");

	GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");

	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), glm::vec3(this->getLocation().x, this->getLocation().y, 0.0f));
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(this->getScale(), this->getScale(), this->getScale()));

	glm::mat4 medelMat = transMat * scaleMat;

	glm::vec4 color;
	if (this->getIsColliding())
	{
		color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
		color = this->getColor();

	glUniform4fv(colorLoc, 1, (GLfloat*)&color);
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &medelMat[0][0]);

	glBegin(GL_LINES);
	glColor3f(0, 1, 1);
	glVertex2f(this->point1.x, this->point1.y);
	glVertex2f(this->point2.x, this->point2.y);
	glEnd();


	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glUniform4fv(colorLoc, 1, (GLfloat*)&color);

	

}



void CLS_Line::setPointOne(double p1, double p2, double p3)
{
	this->point1 = glm::vec3(p1, p2, p3);

}
void CLS_Line::setPointTwo(double p1, double p2, double p3)
{

	this->point2 = glm::vec3(p1, p2, p3);

}


glm::vec3 CLS_Line::getPointOne()
{
	return this->point1;
}
glm::vec3 CLS_Line::getPointTwo()
{
	return this->point2;
}