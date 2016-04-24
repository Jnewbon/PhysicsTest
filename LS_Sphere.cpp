#include "LS_Sphere.h"



CLS_Sphere::CLS_Sphere()
{
}


CLS_Sphere::~CLS_Sphere()
{
}

#ifdef GLUseShader
void CLS_Sphere::draw(GLuint shaderProgram)
{

	GLuint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");

	GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");

	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), glm::vec3(this->getLocation().x, this->getLocation().y, 0.0f));
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(this->getScale(), this->getScale(), this->getScale()));
	glm::mat4 rotatMat = glm::rotate(glm::mat4(1.0f), this->currentRotation, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 medelMat = transMat * scaleMat * rotatMat;
	glm::vec4 color;

#ifdef SHOW_COLLISION_HIGHLIGHT
	if (this->getIsColliding())
	{
		color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		color = this->getColor();
	}
#else 
	color = this->getColor();
#endif

	glUniform4fv(colorLoc, 1, (GLfloat*)&color);
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &medelMat[0][0]);

	glBindVertexArray(this->modelVAO);

	glDrawElements(GL_TRIANGLE_FAN, this->shapeType, GL_UNSIGNED_INT, (GLvoid*)0);

	glBindVertexArray(0);

	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glUniform4fv(colorLoc, 1, (GLfloat*)&color);
	this->drawCenterCross();
}
#else
void CLS_Sphere::draw()
{

	glPushMatrix();
	glTranslatef(getLocation().x, getLocation().y, getLocation().z);
	glPushMatrix();
	glScalef(getScale(), getScale(), getScale());

	glColor3f(getColor().x, getColor().y, getColor().z);
	glutSolidSphere(1.0f, 20, 20);

	glPopMatrix();
	glPopMatrix();

}
#endif