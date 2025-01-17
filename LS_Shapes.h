#pragma once
#include "options.h"
#include "LS_VectorPoint.h"


#include "GL\glew\glew.h" 
#include "GL\glut.h"
#include "GL\freeglut.h"
#include "glm\glm.hpp"


class CLS_Shapes
{
public:

enum Type { CIRCLE = 36,
			LINE = 2};
	

	CLS_Shapes(void);
	~CLS_Shapes(void);

	//this will be the counter for the shapes ID's
	static int nextID;

	//Getters
	glm::vec3 getLocation();
	glm::vec3 getSpeed();
	float getMass();
	bool isMovable();
	Type getType();
	GLuint getModelVAO();
	float getScale();
	glm::vec3 getCollisionBox();
	float getBounceFactor();
	glm::vec4 getColor();
	bool getIsColliding();
	float getRotationalVelociy();
	float getRotation();


	//Setters
	virtual void setLocation(const glm::vec3);
	virtual void setSpeed(const glm::vec3);
	virtual void setMass(float);
	virtual void setModelVAO(GLuint);
	virtual void setType(Type);
	virtual void setColour(const glm::vec4);
	virtual void setScale(float);
	virtual void setCollisionBox(const glm::vec3);
	virtual void setBounceFactor(float);
	virtual void setMovableStatus(bool);
	virtual void setIscolliding(bool);
	virtual void setRotationalVelocity(float);
	virtual void setRotaion(float);
	


	virtual void drawCenterCross();
	
#ifdef GLUseShader
	virtual void draw(GLuint);
#else
	virtual void draw();
#endif // GLUseShader


private:

	//The Unique id of the shape
	int shapeID;

	//The type of shape
	Type shapeType;

	//Virtual Array Object for the Shape
	GLuint modelVAO;

	//Virtual Buffer Objects of the shape
	GLuint colorUBO;

	//Virtual Buffer Objects of the shape
	GLuint texture;
	
	//The locartion of the object in space
	glm::vec3 location;

	//the Speed of the object in space
	glm::vec3 speed;
	float rotationVelocity;
	float currentRotation;

	bool isColliding;
	int showCollisionColour;
	//####Object Propities####

	//This is for scaling the object size, and calculating the collision box
	float scale;

	//Mass of the object
	float mass;

	//If the object is movable (Motion /collision applied)
	bool movable;

	//if the object can collide True if no collision
	bool noClip;

	//A box for quick colision dection using manhattan distance
	glm::vec3 CollisionBoxSize;		//this is for the size of the collison box

	//This is the speed lost when bouncing on the floor 0.1 = a 10% loss in speed
	float bouncyFactor;

	//the color of the object
	glm::vec4 color;
	
	
};

