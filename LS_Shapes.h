#pragma once

#include "LS_VectorPoint.h"

#include "GL\glew\glew.h" 
#include "GL\glut.h"
#include "GL\freeglut.h"

enum Type {CIRCLE = 36};
class CLS_Shapes
{
public:

	

	CLS_Shapes(void);
	~CLS_Shapes(void);

	//this will be the counter for the shapes ID's
	static int nextID;

	//Getters
	CLS_VectorPoint<float> getLocation();
	CLS_VectorPoint<float> getSpeed();
	float getMass();
	bool isImmovable();
	Type getType();
	GLuint getModelVAO();
	float getScale();
	CLS_VectorPoint<float> getCollisionBox();
	float getBounceFactor();

	//Setters
	virtual void setLocation(CLS_VectorPoint<float>);
	virtual void setSpeed(CLS_VectorPoint<float>);
	virtual void setMass(float);
	virtual void setModelVAO(GLuint);
	virtual void setType(Type);
	virtual void setColour(int, int, int);
	virtual void setScale(float);
	virtual void setCollisionBox(CLS_VectorPoint<float>);
	virtual void setBounceFactor(float);
	
	virtual void draw();

private:

	//The Unique id of the shape
	int shapeID;

	//The type of shape
	Type shapeType;

	//Virtual Array Object for the Shape
	GLuint modelVAO;

	//Virtual Buffer Objects of the shape
	GLuint colorUBO;
	
	//The locartion of the object in space
	CLS_VectorPoint<float> location;

	//the Speed of the object in space
	CLS_VectorPoint<float> speed;



	//####Object Propities####

	//This is for scaling the object size, and calculating the collision box
	float scale;

	//Mass of the object
	float mass;

	//If the object is immovable
	bool immovable;

	//if the object can collide True if no collision
	bool noClip;

	//A box for quick colision dection using manhattan distance
	CLS_VectorPoint<float> CollisionBoxSize;		//this is for the size of the collison box

	//This is the speed lost when bouncing on the floor 0.1 = a 10% loss is speed
	float bouncyFactor;
	
	
};

