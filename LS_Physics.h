#if !defined(_CLS_PHYSICS_H)
#define _CLS_PHYSICS_H


#include "options.h"
#include "LS_Shapes.h"
#include "LS_Circle.h"
#include "CLS_Line.h"
#include "LS_VectorPoint.h"
#include <vector>
#include <list>



class CLS_Physics {
private:

	// Continuous Collision Detection
	static bool PHYSICS_CCD;
	static unsigned int PHYSICS_CCD_ITOR;

	//Private contructor will prevent instantces being made.
	CLS_Physics();

	static float RESISTANCE_AIR;
	static float RESISTANCE_GROUND;
	static float ACCELARATION;
	static float MATH_PI;

	static CLS_VectorPoint<float> viewSize;
	static std::list<CLS_Shapes*> contactList;
	static bool destroyOffScreen; //This will destory offscreen objects.

public:

	static long long collisionCounter;

	static void setScreenSize(CLS_VectorPoint<float>);
	static void CCDStaus(bool, unsigned int);

	static bool collision_Manhattan_Dist(CLS_Shapes*, CLS_Shapes*);

	static bool collision_Manhattan_Dist(CLS_Circle*, CLS_Circle*);
	static bool collision_Manhattan_Dist(CLS_Circle*, CLS_Line*);

	static bool collision_Euclidian_Dist(CLS_Shapes*, CLS_Shapes*);
	static bool collision_will_collide(CLS_Shapes*, CLS_Shapes*);

	//Main Pyysics entry point
	static void applyPhysics(long long elapsedTime, std::vector<CLS_Shapes*> *objects);
	static void applyGravity(long long elapsedTime, CLS_Shapes* object);
	static void applyObjectMovment(long long elapsedTime,CLS_Shapes* object);

	static void CCD_ColliosnLoop(long long elapsedTime, CLS_Shapes*, CLS_Shapes*);
	
	static void math_Apply_Collision_Momentum(CLS_Shapes*, CLS_Shapes*);

	static void math_Apply_Collision_Momentum(CLS_Circle*, CLS_Circle*);
	static void math_Apply_Collision_Momentum(CLS_Circle*, CLS_Line*);


	static float math_Euclidian_Dist(glm::vec3, glm::vec3);
	static float math_Manhattan_Dist(glm::vec3, glm::vec3);


};

#endif  //_CLS_PHYSICS_H

