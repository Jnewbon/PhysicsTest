#include "LS_Physics.h"

#include <vector>

long long CLS_Physics::collisionCounter = 0;

CLS_VectorPoint<float> CLS_Physics::viewSize = CLS_VectorPoint<float>(0,0);

//For the moment the resistance of air and ground can be done by simple math higher the number the more resistance the object encounters when moving
float CLS_Physics::RESISTANCE_AIR = 0.0f;
float CLS_Physics::RESISTANCE_GROUND = 0.0f;

float CLS_Physics::ACCELARATION = -9.81f;
float CLS_Physics::MATH_PI = 3.14159265f;
bool CLS_Physics::destroyOffScreen = true; //This will destory offscreen objects.
bool CLS_Physics::PHYSICS_CCD = false; //If The CCD system is active or not
unsigned int CLS_Physics::PHYSICS_CCD_ITOR = 10; //The number of steps the objects will do for the collision detection

void CLS_Physics::setScreenSize(CLS_VectorPoint<float> value )
{
	CLS_Physics::viewSize = value;
}

void CLS_Physics::CCDStaus(bool CCD, unsigned int CCDloop)
{
	CLS_Physics::PHYSICS_CCD = CCD;
	CLS_Physics::PHYSICS_CCD_ITOR = CCDloop;
}

bool CLS_Physics::collision_Manhattan_Dist(CLS_Shapes* obj1, CLS_Shapes* obj2)
{
	/* 
	This is the Fast collision detection for quickly dectecting if there is a possibility of collision between two objects
	How this works is by doing simple box collision, this is fast and easy, and allows for the majority of the comparasons to be ruled out 
	with simple calculations without having to start the more complex stuff
	This is done by drawing a box round the object and testing with box collision.
	Once this function determins that there is a collision a more complex calculation 
	can take place to more accuratly determine if the two object have collided

	/*
	/*Rather then checking if there is overlap.
	//We will check if there is no overlap. 
	//as most object wont be colliding as soon as a condition thatv makes it immposible 
	//to collide is found the fuction will return false
	useing 4 conditions
	Cond1.  If A's left edge is to the right of the B's right edge,
           -  then A is Totally to right Of B
	Cond2.  If A's right edge is to the left of the B's left edge,
           -  then A is Totally to left Of B
	Cond3.  If A's top edge is below B's bottom  edge,
           -  then A is Totally below B
	Cond4.  If A's bottom edge is above B's top edge,
           -  then A is Totally above B

		   If any of these conitions is true then the two objects are not colliding
		   else they are
*/
	
	if ((obj1->getLocation().x - obj1->getCollisionBox().x/2) > 
		(obj2->getLocation().x + obj2->getCollisionBox().x/2))
		//Cond1 = true No overlap
		return false;
	
	if ((obj1->getLocation().x + obj1->getCollisionBox().x/2) < 
		(obj2->getLocation().x - obj2->getCollisionBox().x/2))
		//Cond2 = true No overlap
		return false;
	
	if ((obj1->getLocation().y - obj1->getCollisionBox().y/2) > 
		(obj2->getLocation().y + obj2->getCollisionBox().y)/2)
		//Cond3 = true No overlap
		return false;
	
	if ((obj1->getLocation().y + obj1->getCollisionBox().y/2) < 
		(obj2->getLocation().y - obj2->getCollisionBox().y/2))
		//Cond4 = true No overlap
		return false;

	//If none of the conditions are true then the object is colliding

	return true;

}

bool CLS_Physics::collision_Euclidian_Dist(CLS_Shapes* obj1, CLS_Shapes* obj2)
{
	float x = (obj1->getLocation().x + obj1->getSpeed().x) - (obj2->getLocation().x + obj2->getSpeed().x);
	float y = (obj1->getLocation().y + obj1->getSpeed().y) - (obj2->getLocation().y + obj2->getSpeed().y);
	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;


	if ( (x * x) + (y * y) <= (obj1->getCollisionBox().x) * (obj2->getCollisionBox().x))
		return true;
	else 
		return false;
}

bool CLS_Physics::collision_will_collide(CLS_Shapes* obj1, CLS_Shapes* obj2)
{
	////this will be a test to make sure the object are moving towards each other and not away.
	////this wil prevent multiple collision events occuring should an object move inside of the other

	//float	a , b, c, d, x, y, det, lambda, mu;
	//glm::vec4	pP11, pP12, pP21, pP22;

	//pP11 = obj1->getLocation();
	//pP12 = obj1->getLocation() + (obj1->getSpeed() * 100.0f);
	//pP21 = obj2->getLocation();
	//pP22 = obj2->getLocation() + (obj2->getSpeed() * 100.0f);
	//	
	//// We must see if there exist lambda and mu such that:
	//// lambda[P11, P12] = mu[P21, P22]  with  0 < lambda, mu < 1.
	//// This give us two equations with two unknowns.
	//// We set up a few parameters
	//a = pP12.getX() - pP11.getX();
	//b = pP22.getX() - pP21.getX();
	//c = pP12.getY() - pP11.getY();
	//d = pP22.getY() - pP21.getY();
	//det = a * d - b * c; // determinant of equation matrix 

	//// det == 0 means that the edges are parallel.
	//// We assume that they must not intersect in this case,
	//// since 'overlapping' edges are dealt with beforehand
	//if (abs(det) < 0.00000001F)
	//	return FALSE;

	//// If you do the maths, you discover that if lambda and mu exist, then
	//// lambda = (dx - by) / det  and  mu = (cx - ay) / det
	//// where  x = x21 - x11  and  y = y21 - y11
	//x = pP21.getX() - pP11.getX();
	//y = pP21.getY() - pP11.getY();
	//lambda = (d * x - b * y) / det;
	//if (lambda < 0 || lambda > 1)
	//	return FALSE;
	//mu = (c * x - a * y) / det;
	//if (mu < 0 || mu > 1)
	//	return FALSE;

	return TRUE;
}

	
//Main Physics Entry point
void CLS_Physics::applyPhysics(long long elapsedTime, std::vector<CLS_Shapes*> *objects)
{

	if (objects == nullptr)
		return;

	for (std::vector<CLS_Shapes*>::iterator i = objects->begin(); i != objects->end(); i++)
	{
		for(std::vector<CLS_Shapes*>::iterator j = i+1; j != objects->end(); j++)
		{
			if (CLS_Physics::PHYSICS_CCD)
			{
				CLS_Physics::CCD_ColliosnLoop((*i), (*j));
			}
			else
			{
				//Check for approx collision/Fast collision algorithm
				if (CLS_Physics::collision_Manhattan_Dist((*i), (*j)))
				{
					if (CLS_Physics::collision_Euclidian_Dist((*i), (*j)))
					{
						CLS_Physics::math_Apply_Collision_Momentum((*i), (*j));

					}
				}
			}
		}
	}
}

void CLS_Physics::applyGravity(long long elapsedTime, CLS_Shapes* object)
{
	glm::vec3 temp = object->getSpeed();

	temp.y = (temp.y + ((ACCELARATION/1000.0f) * elapsedTime));

	object->setSpeed(temp);

}
	
void CLS_Physics::applyObjectMovment(long long elapsedTime,CLS_Shapes* object)
{

	float resistancefactorX, resistancefactorY;


	if (object->getSpeed().x <= 0.01f && object->getSpeed().x >= -0.01f)
	{
		resistancefactorX = 1.0f - (CLS_Physics::RESISTANCE_GROUND / 1000.0f);
		resistancefactorY = 1.0f - (CLS_Physics::RESISTANCE_AIR / 1000.0f); 
	}
	else
	{
		resistancefactorX = 1.0f - (CLS_Physics::RESISTANCE_AIR / 1000.0f);
		resistancefactorY = 1.0f - (CLS_Physics::RESISTANCE_AIR / 1000.0f);
	}	
	
	object->setLocation(object->getLocation() + object->getSpeed());

	glm::vec3 temp1, temp2, temp3;
	temp1 = object->getCollisionBox();
	temp2 = object->getLocation();
	temp3 = object->getSpeed();	




	if (temp2.y < -(CLS_Physics::viewSize.getY()/2) + (temp1.y/2) && temp3.y < 0.0f)
	{
		temp3.y = ((temp3.y * (1.0f - object->getBounceFactor()))* -1);
		temp2.y = (temp2.y + -(temp2.y - (-(CLS_Physics::viewSize.getY()/2) + (temp1.y/2))));

		//CLS_Physics::collisionCounter++;
	}
	else if (temp2.y > (CLS_Physics::viewSize.getY()/2) - (temp1.y/2))
	{
		temp3.y = ((temp3.y * (1.0f - object->getBounceFactor())) * -1);
		temp2.y = (temp2.y - (temp2.y - ((CLS_Physics::viewSize.getY()/2) - (temp1.y/2))));

		//CLS_Physics::collisionCounter++;
	}
	if (temp2.x < -(CLS_Physics::viewSize.getX()/2) + (temp1.x/2))
	{
			
		temp3.x = ((temp3.x * (1.0f - object->getBounceFactor()))* -1 );
		temp2.x = (temp2.x + ( (((CLS_Physics::viewSize.getX()/2)*-1) + (temp1.x/2)) - temp2.x ));
		//CLS_Physics::collisionCounter++;
	}
	else if(temp2.x > (CLS_Physics::viewSize.getX()/2) - (temp1.x/2))
	{
		
		temp3.x = ((temp3.x * (1.0f - object->getBounceFactor())) * -1);
		temp2.x = (temp2.x - (temp2.x - ((CLS_Physics::viewSize.getX()/2) - (temp1.x/2))));

		//CLS_Physics::collisionCounter++;
	}
	
	temp3.x = (temp3.x * resistancefactorX);
	temp3.y = (temp3.y * resistancefactorY);
	object->setLocation(temp2);
	object->setSpeed(temp3);
}

void CLS_Physics::CCD_ColliosnLoop(CLS_Shapes *obj1, CLS_Shapes *obj2)
{
	//As the detection is done in steps save the original speed of both objects


	//And set the speed of the objects to the step amount, The current speed divided by the number of steps to be done
	obj1->setSpeed((obj1->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));
	obj2->setSpeed((obj2->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));

	//Loop for the number of steps to be done
	for (unsigned int i = 0; i < CLS_Physics::PHYSICS_CCD_ITOR; i++)
	{
		//Check the manhattan distance first
		if (CLS_Physics::collision_Manhattan_Dist(obj1, obj2))
		{
			//Then the euclidian
			if (CLS_Physics::collision_Euclidian_Dist(obj1, obj2))
			{
				//Rest the speed back th there original for the calculations to be accurate
				obj1->setSpeed((obj1->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
				obj2->setSpeed((obj2->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
				CLS_Physics::math_Apply_Collision_Momentum(obj1, obj2);
				//If the object has cillided then it wont collide with this object again, Probably
				obj1->setSpeed((obj1->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));
				obj2->setSpeed((obj2->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));
				//Add whats left of the movment to the 
				for (i; i < CLS_Physics::PHYSICS_CCD_ITOR; i++)
				{
					CLS_Physics::applyObjectMovment(0, obj1);
					CLS_Physics::applyObjectMovment(0, obj2);
				}
				//exit the for loop
				break;
			}
		}

		//Apply the objects movment for the next step
		CLS_Physics::applyObjectMovment(0, obj1);
		CLS_Physics::applyObjectMovment(0, obj2);

	}

	//Rest the speed back th there original
	obj1->setSpeed((obj1->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
	obj2->setSpeed((obj2->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
}

void CLS_Physics::math_Apply_Collision_Momentum(CLS_Shapes* obj1, CLS_Shapes* obj2)
{
	float o1X = obj1->getLocation().x;
	float o1Y = obj1->getLocation().y;
	float o1XS = obj1->getSpeed().x;
	float o1YS = obj1->getSpeed().y;
	float o1M = obj1->getMass();

	float o2X = obj2->getLocation().x;
	float o2Y = obj2->getLocation().y;
	float o2XS = obj2->getSpeed().x;
	float o2YS = obj2->getSpeed().y;
	float o2M = obj2->getMass();

	//Get the normal Vector
	float nvX = (o1X - o2X);
	float nvY = (o1Y - o2Y);

	//Get the Unit Normal
	float unX = nvX / sqrt( pow( nvX , 2) + pow( nvY , 2));
	float unY = nvY / sqrt( pow( nvX , 2) + pow( nvY , 2));

	//Get the Unit Tangent
	float utX = -unY;
	float utY = unX;

	//Work out the scalers
	float v1un = ( o1XS * unX ) + ( o1YS * unY );
	float v1ut = ( o1XS * utX ) + ( o1YS * utY );
	float v2un = ( o2XS * unX ) + ( o2YS * unY );
	float v2ut = ( o2XS * utX ) + ( o2YS * utY );

	//Work out Directionlees speed
	float v1fv = ((v1un * (o1M - o2M)) + ( 2 * o2M * v2un)) / (o1M + o2M);
	float v2fv = ((v2un * (o2M - o1M)) + ( 2 * o1M * v1un)) / (o1M + o2M);

	//work out Change in x/ Change in Y
	glm::vec3 fv1;
	fv1.x = ((v1fv * unX) + ( v1ut * utX ));
	fv1.y = ((v1fv * unY) + ( v1ut * utY ));

	glm::vec3 fv2;
	fv2.x = ((v2fv * unX) + ( v2ut * utX ));
	fv2.y = ((v2fv * unY) + ( v2ut * utY ));

	//Finally set the new vectoer of both objects
	obj1->setSpeed(fv1);
	obj2->setSpeed(fv2);
	CLS_Physics::collisionCounter++;


}

template <typename T>
float CLS_Physics::math_Euclidian_Dist(CLS_VectorPoint<T>, CLS_VectorPoint<T>)
{
	return 0.0f;
}

template <typename T>
float CLS_Physics::math_Manhattan_Dist(CLS_VectorPoint<T>, CLS_VectorPoint<T>)
{
	return 0.0f;
}