#include "LS_Physics.h"
#include "glm\glm.hpp"
#include "glm\gtx\scalar_multiplication.hpp"
#include "glm\gtx\vector_angle.hpp"

#include <iostream>

#include <vector>

long long CLS_Physics::collisionCounter = 0;

CLS_VectorPoint<float> CLS_Physics::viewSize = CLS_VectorPoint<float>(0,0);

//For the moment the resistance of air and ground can be done by simple math higher the number the more resistance the object encounters when moving
float CLS_Physics::RESISTANCE_AIR = 0.0f;
float CLS_Physics::RESISTANCE_GROUND = 0.0;

float CLS_Physics::ACCELARATION = -120.81f;
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

	Rather then checking if there is overlap.
	We will check if there is no overlap. 
	as most object wont be colliding as soon as a condition thatv makes it immposible 
	to collide is found the fuction will return false
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
	
	//Seperate the diffrent object out
	//
	//#### Circle to Circle ####
	//
	if (obj1->getType() == CLS_Shapes::CIRCLE && obj2->getType() == CLS_Shapes::CIRCLE)
		return CLS_Physics::collision_Manhattan_Dist((CLS_Circle*)obj1, (CLS_Circle*)obj2);

	//
	//#### Circle to Line ####
	//
	else if (
		(obj1->getType() == CLS_Shapes::LINE && obj2->getType() == CLS_Shapes::CIRCLE) ||
		(obj1->getType() == CLS_Shapes::CIRCLE && obj2->getType() == CLS_Shapes::LINE))
	{
		if (obj1->getType() == CLS_Shapes::LINE)
			return CLS_Physics::collision_Manhattan_Dist((CLS_Circle*)obj2, (CLS_Line*)obj1);
		else
			return CLS_Physics::collision_Manhattan_Dist((CLS_Circle*)obj1, (CLS_Line*)obj2);
	}

	return false;

}

bool CLS_Physics::collision_Manhattan_Dist(CLS_Circle* obj1, CLS_Circle* obj2)
{
	if ((obj1->getLocation().x - obj1->getScale()) >
		(obj2->getLocation().x + obj2->getScale()))
		//Cond1 = true No overlap
		return false;

	if ((obj1->getLocation().x + obj1->getScale()) <
		(obj2->getLocation().x - obj2->getScale()))
		//Cond2 = true No overlap
		return false;

	if ((obj1->getLocation().y - obj1->getScale()) >
		(obj2->getLocation().y + obj2->getScale()))
		//Cond3 = true No overlap
		return false;

	if ((obj1->getLocation().y + obj1->getScale()) <
		(obj2->getLocation().y - obj2->getScale()))
		//Cond4 = true No overlap
		return false;

	//If none of the conditions are true then the object is colliding

	return true;
}

bool CLS_Physics::collision_Manhattan_Dist(CLS_Circle* circ, CLS_Line* line)
{

	//Source: http://paulbourke.net/geometry/pointlineplane/

	glm::vec3 lineStart = line->getLocation() + line->getPointOne();
	glm::vec3 lineEnd = line->getLocation() + line->getPointTwo();

	glm::vec3 toCircle = lineStart - circ->getLocation();
	glm::vec3 lineDirection = lineEnd - lineStart;


	glm::vec3 P1 = lineStart;
	glm::vec3 P2 = lineEnd;
	glm::vec3 P3 = circ->getLocation();


	float u = ((P3.x - P1.x)*(P2.x - P1.x) + (P3.y - P1.y)*(P2.y - P1.y)) / (glm::length(P2 - P1) * glm::length(P2 - P1));
	//std::cout << "\n" << u;
	if (u <= 0.0f)
		//The center of the circle is closest to the Start of the line
		return CLS_Physics::math_Euclidian_Dist(P1, P3) < circ->getScale();

	else if (u >= 1.0f)
		//The center of the circle is closer to the End of the line
		return CLS_Physics::math_Euclidian_Dist(P2, P3) < circ->getScale();

	else
	{
		glm::vec3 P4(P1.x + (u*(P2.x - P1.x)), P1.y + (u*(P2.y - P1.y)),0.0f);
		return CLS_Physics::math_Euclidian_Dist(P4, P3) < circ->getScale();
	}



	//float PlatformLength = glm::length(lineDirection);
	//float radius = circ->getScale();




	//if (projected <= 0)
	//{

	//	// The blob is nearest to the start point
	//	if (glm::length(toCircle) < radius)
	//	{
	//		return true;
	//	}
	//	else if (projected >= PlatformLength * PlatformLength)
	//	{
	//		// The blob is nearest to the end point
	//		toCircle = circ->getLocation() - lineEnd;
	//		if (glm::length(toCircle) < radius)
	//		{
	//			return true;
	//		}
	//	}
	//	else
	//	{
	//		// the blob is nearest to the middle.
	//		float distanceToPlatform = glm::length(toCircle) - projected / PlatformLength;
	//		if (distanceToPlatform < radius)
	//		{
	//			return true;
	//		}
	//	}
	//}

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
	//Make sure there are objects to apply physics to
	if (objects == nullptr)
		return;


	//Start looping through the objects
	for (std::vector<CLS_Shapes*>::iterator i = objects->begin(); i != objects->end(); i++)
	{
		//Start the next loop to the priviouse one plus 1, This will make sure no two onjects and screwtinized more then once
		for(std::vector<CLS_Shapes*>::iterator j = i+1; j != objects->end(); j++)
		{
			//Continuous Collision Detection is enabled
			if (CLS_Physics::PHYSICS_CCD)
			{
				//go the the CCD collision loop
				CLS_Physics::CCD_ColliosnLoop(elapsedTime, (*i), (*j));
			}
			else
			{
				//Check for approx collision/Fast collision algorithm
				if (CLS_Physics::collision_Manhattan_Dist((*i), (*j)))
				{

					//As circle to line colliosn only has the advaced detection algortim currently only one test needs to be done
					//So apply the momentum to the objects
					if (((*i)->getType() == CLS_Shapes::LINE && (*j)->getType() == CLS_Shapes::CIRCLE) ||
						((*i)->getType() == CLS_Shapes::CIRCLE && (*j)->getType() == CLS_Shapes::LINE))
					{

						CLS_Physics::math_Apply_Collision_Momentum((*i), (*j));
					}
					//Circle to circle has two algoritms, a basic and advanced, apply the advanced version now
					else if (CLS_Physics::collision_Euclidian_Dist((*i), (*j)))
					{
						CLS_Physics::math_Apply_Collision_Momentum((*i), (*j));

					}
				}
			}
		}
	}

	//Apply the object movment and gravity

	for (std::vector<CLS_Shapes*>::iterator i = objects->begin(); i != objects->end(); i++)
	{
		//if (!CLS_Physics::PHYSICS_CCD)
		CLS_Physics::applyObjectMovment(elapsedTime, (*i));

		//Apply gravity anyway as thats not applied to everything during the CDD
		CLS_Physics::applyGravity(elapsedTime, (*i));
	}

}

void CLS_Physics::applyGravity(long long elapsedTime, CLS_Shapes* object)
{	
	//if the object is immovable skip this object movemnt
	if (!object->isMovable())
		return;

	glm::vec3 temp = object->getSpeed();

	temp.y = (temp.y + ((ACCELARATION/1000.0f) * elapsedTime));

	object->setSpeed(temp);

}
	
void CLS_Physics::applyObjectMovment(long long elapsedTime,CLS_Shapes* object)
{
	//if the object is immovable skip this object movemnt
	if (!object->isMovable())
		return;

	float resistancefactorX, resistancefactorY;

	//Set the resistances for the ground and air in an x/y plane, (ground resistance currney only works for object on a constant y plane/flat line)
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
	
	//Move the object
	object->setLocation(object->getLocation() + ((object->getSpeed() / 1000.0f) * float(elapsedTime)));

	//Time to make sure the object is within the boundrys of the screen
	glm::vec3 temp1, temp2, temp3;
	temp1 = object->getCollisionBox();
	temp2 = object->getLocation();
	temp3 = object->getSpeed();	



	//Make sure the object is above the bottom of the screen
	if (temp2.y < -(CLS_Physics::viewSize.getY()/2) + (temp1.y/2) && temp3.y <= 0.0f)
	{
		//if not snap to the bottom of the screen and reverse the y speed

		if (temp3.y > -0.1f)
			temp3.y = 0.0f;

		temp3.y = -((temp3.y * object->getBounceFactor()));
		temp2.y = (temp2.y + -(temp2.y - (-(CLS_Physics::viewSize.getY()/2) + (temp1.y/2))));

		if ((-((temp3.x / object->getScale())*(180.0 / MATH_PI) / 1000.0f) * float(elapsedTime)) < -1.0f)
			temp3.y = temp3.y;

		object->setRotationalVelocity((-((temp3.x/object->getScale())*(180.0/MATH_PI) / 1000.0f) * float(elapsedTime)));

		//CLS_Physics::collisionCounter++;
	}
	//Make sure the object is below of the screen
	else if (temp2.y > (CLS_Physics::viewSize.getY()/2) - (temp1.y/2))
	{
		//if not snap to the top of the screen and reverse the y speed
		temp3.y = -((temp3.y * object->getBounceFactor()));
		temp2.y = (temp2.y - (temp2.y - ((CLS_Physics::viewSize.getY()/2) - (temp1.y/2))));

		//CLS_Physics::collisionCounter++;
	}
	//Make sure the object is to the right of the left of the screen
	if (temp2.x < -(CLS_Physics::viewSize.getX()/2) + (temp1.x/2))
	{

		//if not snap to the left  of the screen and reverse the x speed
		temp3.x = -((temp3.x * object->getBounceFactor()) );
		temp2.x = (temp2.x + ( (((CLS_Physics::viewSize.getX()/2)*-1) + (temp1.x/2)) - temp2.x ));
		//CLS_Physics::collisionCounter++;
	}
	//Make sure the object is to the left of the right of the screen
	else if(temp2.x > (CLS_Physics::viewSize.getX()/2) - (temp1.x/2))
	{
		//if not snap to the right  of the screen and reverse the x speed
		
		temp3.x = -((temp3.x * object->getBounceFactor()));
		temp2.x = (temp2.x - (temp2.x - ((CLS_Physics::viewSize.getX()/2) - (temp1.x/2))));

		//CLS_Physics::collisionCounter++;
	}
	

	//factor in the Resistances calculated eariler and apply the new location and speed to the objects
	temp3.x = (temp3.x * resistancefactorX);
	temp3.y = (temp3.y * resistancefactorY);
	object->setLocation(temp2);
	object->setSpeed(temp3);

	//Also rotate the object using the roational velocity
	object->setRotaion(object->getRotation() + ((object->getRotationalVelociy()/1000) * float(elapsedTime)));
}
//TODO CCD Colliosn currently broken
void CLS_Physics::CCD_ColliosnLoop(long long elapsedTime, CLS_Shapes *obj1, CLS_Shapes *obj2)
{
	//As the detection is done in steps save the original speed of both objects

	

	//And set the speed of the objects to the step amount, The current speed divided by the number of steps to be done
	obj1->setSpeed((obj1->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));
	obj2->setSpeed((obj2->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));

	//Loop for the number of steps to be done
	for (unsigned int i = 0; i < CLS_Physics::PHYSICS_CCD_ITOR; i++)
	{
		//Check the manhattan distance first
		if (CLS_Physics::collision_Manhattan_Dist(obj1, obj2) && !(obj1->getType() == CLS_Shapes::LINE && obj2->getType() == CLS_Shapes::LINE))
		{

			
			//If we are checking a Circle and Line then theres no need to go further then that
			if ((obj1->getType() == CLS_Shapes::LINE && obj2->getType() == CLS_Shapes::CIRCLE) ||
				(obj1->getType() == CLS_Shapes::CIRCLE && obj2->getType() == CLS_Shapes::LINE))
			{
				//Reset the speed back th there original for the calculations to be accurate
				obj1->setSpeed((obj1->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
				obj2->setSpeed((obj2->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
				CLS_Physics::math_Apply_Collision_Momentum(obj1, obj2);
				//If the object has cillided then it wont collide with this object again, Probably
				obj1->setSpeed((obj1->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));
				obj2->setSpeed((obj2->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));
				//Add whats left of the movment to the 
				//Best way to add the remaining step of the movment is to times the elapse time by 
				//the remaining step and apply it to the object via the establised function
				CLS_Physics::applyObjectMovment(elapsedTime * (CLS_Physics::PHYSICS_CCD_ITOR - i), obj1);
				CLS_Physics::applyObjectMovment(elapsedTime * (CLS_Physics::PHYSICS_CCD_ITOR - i), obj2);
				//exit the for loop

				obj1->setIscolliding(true);
				obj2->setIscolliding(true);
			}


			//Then the euclidian
			else if (CLS_Physics::collision_Euclidian_Dist(obj1, obj2))
			{
				//Reset the speed back th there original for the calculations to be accurate
				obj1->setSpeed((obj1->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
				obj2->setSpeed((obj2->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
				CLS_Physics::math_Apply_Collision_Momentum(obj1, obj2);
				//If the object has cillided then it wont collide with this object again, Probably
				obj1->setSpeed((obj1->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));
				obj2->setSpeed((obj2->getSpeed() / float(CLS_Physics::PHYSICS_CCD_ITOR)));
				//Add whats left of the movment to the 
				//Best way to add the remaining step of the movment is to times the elapse time by 
				//the remaining step and apply it to the object via the establised function
				CLS_Physics::applyObjectMovment(elapsedTime * (CLS_Physics::PHYSICS_CCD_ITOR - i), obj1);
				CLS_Physics::applyObjectMovment(elapsedTime * (CLS_Physics::PHYSICS_CCD_ITOR - i), obj2);
				//exit the for loop

				obj1->setIscolliding(true);
				obj2->setIscolliding(true);

				break;
			}
		}

		//Apply the objects movment for the next step
		CLS_Physics::applyObjectMovment(elapsedTime, obj1);
		CLS_Physics::applyObjectMovment(elapsedTime, obj2);

	}

	//Reset the speed back th there original
	obj1->setSpeed((obj1->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
	obj2->setSpeed((obj2->getSpeed() * float(CLS_Physics::PHYSICS_CCD_ITOR)));
}

void CLS_Physics::math_Apply_Collision_Momentum(CLS_Shapes* obj1, CLS_Shapes* obj2)
{

	//Seperate the diffrent object collisions out
	//
	//#### Circle to Circle ####
	//
	if (obj1->getType() == CLS_Shapes::CIRCLE && obj2->getType() == CLS_Shapes::CIRCLE)
		CLS_Physics::math_Apply_Collision_Momentum((CLS_Circle*)obj1, (CLS_Circle*)obj2);

	//
	//#### Circle to Line ####
	//
	else if (
		(obj1->getType() == CLS_Shapes::LINE && obj2->getType() == CLS_Shapes::CIRCLE) ||
		(obj1->getType() == CLS_Shapes::CIRCLE && obj2->getType() == CLS_Shapes::LINE))
	{
		if (obj1->getType() == CLS_Shapes::LINE)
			CLS_Physics::math_Apply_Collision_Momentum((CLS_Circle*)obj2, (CLS_Line*)obj1);
		else
			CLS_Physics::math_Apply_Collision_Momentum((CLS_Circle*)obj1, (CLS_Line*)obj2);
	}





}

void CLS_Physics::math_Apply_Collision_Momentum(CLS_Circle* obj1, CLS_Circle* obj2)
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
	float unX = nvX / sqrt(pow(nvX, 2) + pow(nvY, 2));
	float unY = nvY / sqrt(pow(nvX, 2) + pow(nvY, 2));

	//Get the Unit Tangent
	float utX = -unY;
	float utY = unX;

	//Work out the scalers
	float v1un = (o1XS * unX) + (o1YS * unY);
	float v1ut = (o1XS * utX) + (o1YS * utY);
	float v2un = (o2XS * unX) + (o2YS * unY);
	float v2ut = (o2XS * utX) + (o2YS * utY);

	//Work out Directionlees speed
	float v1fv = ((v1un * (o1M - o2M)) + (2 * o2M * v2un)) / (o1M + o2M);
	float v2fv = ((v2un * (o2M - o1M)) + (2 * o1M * v1un)) / (o1M + o2M);

	//work out Change in x/ Change in Y
	glm::vec3 fv1;
	fv1.x = ((v1fv * unX) + (v1ut * utX));
	fv1.y = ((v1fv * unY) + (v1ut * utY));

	glm::vec3 fv2;
	fv2.x = ((v2fv * unX) + (v2ut * utX));
	fv2.y = ((v2fv * unY) + (v2ut * utY));

	//Finally set the new vectoer of both objects
	if (obj1->isMovable())
		obj1->setSpeed(fv1 * obj1->getBounceFactor());
	if (obj2->isMovable())
		obj2->setSpeed(fv2 * obj2->getBounceFactor());
	CLS_Physics::collisionCounter++;


	//This will snapp the circle to a point where they are exactally colliding preventing any of the balls merging into each other
	if (math_Euclidian_Dist(obj1->getLocation(), obj2->getLocation()) < obj1->getScale() + obj2->getScale())
	{

		obj1->setLocation(obj1->getLocation() - (((obj2->getLocation() - obj1->getLocation()) / (obj1->getScale() + obj2->getScale()))));
		obj2->setLocation(obj2->getLocation() - (((obj1->getLocation() - obj2->getLocation()) / (obj1->getScale() + obj2->getScale()))));
	}

}

void CLS_Physics::math_Apply_Collision_Momentum(CLS_Circle* circ, CLS_Line* line)
{
	glm::vec3 lineStart = line->getLocation() + line->getPointOne();
	glm::vec3 lineEnd = line->getLocation() + line->getPointTwo();

	glm::vec3 toCircle = lineStart - circ->getLocation();
	glm::vec3 lineDirection = lineEnd - lineStart;


	glm::vec3 P1 = lineStart;
	glm::vec3 P2 = lineEnd;
	glm::vec3 P3 = circ->getLocation();


	//This calculates at a 0-1 basis where the center of the ball is along the line tangant. 
	//for example 0.5 means the the center of the circle is at a tangent to the middle of the line.
	//Values of less the 0.0 and above 1.0 meant the center of the circle is not within the boundries of the line and collision should be tested bases on the distance from either
	//the start of the line or the end of the line base on if the value is above 1 or below 0.
	float u = ((P3.x - P1.x)*(P2.x - P1.x) + (P3.y - P1.y)*(P2.y - P1.y)) / (glm::length(P2 - P1) * glm::length(P2 - P1));
	
	
	CLS_Circle colisionPoint;
	colisionPoint.setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
	colisionPoint.setMovableStatus(false);
	colisionPoint.setMass(200.0f);
	colisionPoint.setScale(0.0f);

	if (u <= 0.0f)
	{	//The center of the circle is closest to the Start of the line
		//Use the circular collison for the ends of the lines
		colisionPoint.setLocation(lineStart);
	}

	else if (u >= 1.0f)
	{	//The center of the circle is closer to the End of the line
		//Use the circular collison for the ends of the lines
		colisionPoint.setLocation(lineEnd);
	}

	else
	{

		//This get the coordinates on the line that the circle had collidied with (contact point)
		glm::vec3 P4(P1.x + (u*(P2.x - P1.x)), P1.y + (u*(P2.y - P1.y)), 0.0f);
		
		//This snapes the ball to the exact point the ball would have contacted the line eliminating all penetration
		circ->setLocation(P4 - ((P4 - P3) / glm::length(P4 - P3)) * circ->getScale());

		
		//in real physics, the rotaion of the object 'should' affect the resultant resolution angle. but ill just let that slide for now. 
		//Game physics is all about the apprent view of being realistic, and this is realistic 'enough'
		float angle = glm::orientedAngle(glm::normalize(lineDirection), glm::normalize(circ->getSpeed()), glm::vec3(0.0f, 1.0f, 0.0f));
		angle -= MATH_PI / 2.0f;

		//Set the rotational speed and velocities
		

		//This should stop a ball infinatly bouncing when the ball almost coemes to rest
		glm::vec3 newSpeed = glm::reflect(circ->getSpeed(), glm::normalize(P4 - P3)) * circ->getBounceFactor();

		if (glm::length(newSpeed) < 2.0)
		{
			newSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
			angle = 0.0f;
		}

		circ->setRotationalVelocity((angle) / circ->getScale());
		circ->setSpeed(newSpeed);

		return;
	}

	//if the circle has cllided with the ends of the line then apply circle on circle collision  using the object created
	CLS_Physics::math_Apply_Collision_Momentum(&colisionPoint, circ);


	//using the point of contact and the balls location move the ball out to the exact size of the ball raidius
	//This should prevent multiple colisions
	circ->setLocation(colisionPoint.getLocation() - ((colisionPoint.getLocation() - P3) / glm::length(colisionPoint.getLocation() - P3)) * circ->getScale());

}

float CLS_Physics::math_Euclidian_Dist(glm::vec3 p1, glm::vec3 p2)
{
	return glm::length(p1-p2);
}

