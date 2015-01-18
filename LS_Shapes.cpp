#include "LS_Shapes.h"
#include "LS_VAO_Setup.h"

int CLS_Shapes::nextID = 0;

CLS_Shapes::CLS_Shapes(void)
{
	//This will give the shape a unique ID
	shapeID = nextID;
	nextID++;

}

CLS_Shapes::~CLS_Shapes(void)
{

}

CLS_VectorPoint<float> CLS_Shapes::getLocation()
{
	return this->location;
}

CLS_VectorPoint<float> CLS_Shapes::getSpeed()
{
	return this->speed;
}

float CLS_Shapes::getMass()
{
	return this->mass;
}

bool CLS_Shapes::isImmovable()
{
	return this->immovable;
}

Type CLS_Shapes::getType()
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

CLS_VectorPoint<float> CLS_Shapes::getCollisionBox()
{
	return this->CollisionBoxSize;
}

void CLS_Shapes::setLocation(CLS_VectorPoint<float> newLoc)
{
	this->location = newLoc;
}

void CLS_Shapes::setSpeed(CLS_VectorPoint<float> newSpeed)
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

void CLS_Shapes::setColour(int r, int g, int b)
{
	
}

void CLS_Shapes::draw()
{
	glPushMatrix();
	glTranslatef(this->location.getX(), this->location.getY(), 1.0f);
	glPushMatrix();
	glScalef(this->scale,this->scale,1.0);
	

	glBindVertexArray(this->modelVAO);
	
	glDrawElements(GL_TRIANGLE_FAN, this->shapeType, GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
	glPopMatrix();
	glPopMatrix();

}

void CLS_Shapes::setScale(float value)
{
	this->scale = value;
}

void CLS_Shapes::setBounceFactor(float value)
{
	this->bouncyFactor = value;
}

void CLS_Shapes::setCollisionBox(CLS_VectorPoint<float> value)
{
	this->CollisionBoxSize = value;
}