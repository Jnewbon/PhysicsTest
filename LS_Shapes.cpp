
#include "LS_Shapes.h"
#include "LS_VAO_Setup.h"
#include "LS_VectorPoint.h"
#include "matrix4.h"
#include "vec4.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\scalar_multiplication.hpp"

int CLS_Shapes::nextID = 0;

CLS_Shapes::CLS_Shapes(void)
{
	//This will give the shape a unique ID
	shapeID = nextID;
	nextID++;
	this->movable = true;
	this->isColliding = false;
	this->showCollisionColour;
	this->rotationVelocity = 0.0f;
	this->currentRotation = 0.0f;
}

CLS_Shapes::~CLS_Shapes(void)
{

}

glm::vec3 CLS_Shapes::getLocation()
{
	return this->location;
}

glm::vec3 CLS_Shapes::getSpeed()
{
	return this->speed;
}

float CLS_Shapes::getMass()
{
	return this->mass;
}

bool CLS_Shapes::isMovable()
{
	return this->movable;
}

CLS_Shapes::Type CLS_Shapes::getType()
{
	return this->shapeType;
}

GLuint CLS_Shapes::getModelVAO()
{
	return this->modelVAO;
}

float CLS_Shapes::getScale()
{
	return this->scale;
}

float CLS_Shapes::getBounceFactor()
{
	return this->bouncyFactor;
}

glm::vec3 CLS_Shapes::getCollisionBox()
{
	return this->CollisionBoxSize;
}

glm::vec4 CLS_Shapes::getColor()
{
	return this->color;
}
 
void CLS_Shapes::setLocation(const glm::vec3 newLoc)
{
	this->location = newLoc;
}

void CLS_Shapes::setSpeed(const glm::vec3 newSpeed)
{
	this->speed = newSpeed;
}

void CLS_Shapes::setMass(float newMass)
{
	if(newMass < 0)
	{
		this->mass = 10.0f;
	}
	else
	{
		this->mass = newMass;
	}
}

void CLS_Shapes::setModelVAO(GLuint newVAO)
{
	this->modelVAO = newVAO;
}

void CLS_Shapes::setType(Type newType)
{
	this->shapeType = newType;
}

void CLS_Shapes::setColour(const glm::vec4 newcolor)
{
	this->color = newcolor;
}

#ifdef GLUseShader

void CLS_Shapes::draw(GLuint shaderProgram)
{


	GLuint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");

	GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");

	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), glm::vec3(this->getLocation().x, this->getLocation().y, 0.0f));
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(this->getScale(), this->getScale(), this->getScale()));
	glm::mat4 rotatMat = glm::rotate(glm::mat4(1.0f), this->currentRotation, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 medelMat = transMat * scaleMat * rotatMat;
	glm::vec4 color;
	if (this->getIsColliding())
	{
		color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
		color = this->getColor();

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
void CLS_Shapes::draw()
{


	glPushMatrix();
	glTranslatef(this->location.x, this->location.y, 1.0f);
	glPushMatrix();
	glScalef(this->scale, this->scale, 1.0);


	glBindVertexArray(this->modelVAO);

	glDrawElements(GL_TRIANGLE_FAN, this->shapeType, GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
	glPopMatrix();
	glPopMatrix();

}
#endif // GLUseShader


void CLS_Shapes::setScale(float value)
{
	this->scale = value;
}

void CLS_Shapes::setBounceFactor(float value)
{
	this->bouncyFactor = value;
}

void CLS_Shapes::setCollisionBox(const glm::vec3 newcol)
{
	this->CollisionBoxSize = newcol;
}

void CLS_Shapes::setMovableStatus(bool isMovable){

	this->movable = isMovable;
}

void CLS_Shapes::setIscolliding(bool isColliding)
{
	if (isColliding)
		this->showCollisionColour = 4;
}

bool CLS_Shapes::getIsColliding()
{
	if (this->showCollisionColour > 0)
	{
		this->showCollisionColour--;
		return true;
	}
	else
		return false;
}

void CLS_Shapes::drawCenterCross()
{
	glBegin(GL_LINES);
	float crossScale = 0.9f;
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0f, crossScale);
	glVertex2f(0.0f, -crossScale);
	glVertex2f(crossScale, 0.0f);
	glVertex2f(-crossScale, 0.0f);
	glEnd();
}

void CLS_Shapes::setRotationalVelocity(float velo)
{
	this->rotationVelocity = velo;
}

float CLS_Shapes::getRotationalVelociy()
{
	return this->rotationVelocity;
}

void CLS_Shapes::setRotaion(float rota)
{
	this->currentRotation = rota;
}

float CLS_Shapes::getRotation()
{
	return this->currentRotation;
}