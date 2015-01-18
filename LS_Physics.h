#if !defined(_CLS_PHYSICS_H)
#define _CLS_PHYSICS_H

#include "LS_Shapes.h"
#include "LS_VectorPoint.h"
#include <vector>
#include <list>



class CLS_Physics {
private:

	// Continuous Collision Detection
	static const bool PHYSICS_CCD  = true;
	static const unsigned int PHYSICS_CCD_ITOR = 10;

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

	static bool collision_Manhattan_Dist(CLS_Shapes*, CLS_Shapes*);
	static bool collision_Euclidian_Dist(CLS_Shapes*, CLS_Shapes*);
	static bool collision_will_collide(CLS_Shapes*, CLS_Shapes*);

	static void applyPhysics(long long elapsedTime, std::vector<CLS_Shapes*> *objects);
	static void applyGravity(long long elapsedTime, CLS_Shapes* object);
	static void applyObjectMovment(long long elapsedTime,CLS_Shapes* object);

	
	static void math_Apply_Collision_Momentum(CLS_Shapes*, CLS_Shapes*);
	template <typename T>
	static float math_Euclidian_Dist(CLS_VectorPoint<T>, CLS_VectorPoint<T>);
	template <typename T>
	static float math_Manhattan_Dist(CLS_VectorPoint<T>, CLS_VectorPoint<T>);


};

#endif  //_CLS_PHYSICS_H
