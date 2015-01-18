#include "LS_Physics.h"

#include <vector>

long long CLS_Physics::collisionCounter = 0;

CLS_VectorPoint<float> CLS_Physics::viewSize = CLS_VectorPoint<float>(0,0);
float CLS_Physics::RESISTANCE_AIR = 2.5f;
float CLS_Physics::RESISTANCE_GROUND = 5.0f;
float CLS_Physics::ACCELARATION = -9.81f;
float CLS_Physics::MATH_PI = 3.14159265f;
bool CLS_Physics::destroyOffScreen = true; //This will destory offscreen objects.

void CLS_Physics::setScreenSize(CLS_VectorPoint<float> value )
{
	CLS_Physics::viewSize = value;
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
	
	if ((obj1->getLocation().getX() - obj1->getCollisionBox().getX()/2) > 
		(obj2->getLocation().getX() + obj2->getCollisionBox().getX()/2))
		//Cond1 = true No overlap
		return false;
	
	if ((obj1->getLocation().getX() + obj1->getCollisionBox().getX()/2) < 
		(obj2->getLocation().getX() - obj2->getCollisionBox().getX()/2))
		//Cond2 = true No overlap
		return false;
	
	if ((obj1->getLocation().getY() - obj1->getCollisionBox().getY()/2) > 
		(obj2->getLocation().getY() + obj2->getCollisionBox().getY())/2)
		//Cond3 = true No overlap
		return false;
	
	if ((obj1->getLocation().getY() + obj1->getCollisionBox().getY()/2) < 
		(obj2->getLocation().getY() - obj2->getCollisionBox().getY()/2))
		//Cond4 = true No overlap
		return false;

	//If none of the conditions are true then the object is colliding

	return true;

}

bool CLS_Physics::collision_Euclidian_Dist(CLS_Shapes* obj1, CLS_Shapes* obj2)
{
	float x = (obj1->getLocation().getX() + obj1->getSpeed().getX()) - (obj2->getLocation().getX() + obj2->getSpeed().getX());
	float y = (obj1->getLocation().getY() + obj1->getSpeed().getX()) - (obj2->getLocation().getY() + obj2->getSpeed().getX());
	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;


	if ( (x * x) + (y * y) <= (obj1->getCollisionBox().getX()) * (obj2->getCollisionBox().getX()))
		return true;
	else 
		return false;
}

bool CLS_Physics::collision_will_collide(CLS_Shapes* obj1, CLS_Shapes* obj2)
{
	//this will be a test to make sure the object are moving towards each other and not away.
	//this wil prevent multiple collision events occuring should an object move inside of the other

	float	a , b, c, d, x, y, det, lambda, mu;
	CLS_VectorPoint<float>	pP11, pP12, pP21, pP22;

	pP11 = obj1->getLocation();
	pP12 = obj1->getLocation() + (obj1->getSpeed() * 100.0f);
	pP21 = obj2->getLocation();
	pP22 = obj2->getLocation() + (obj2->getSpeed() * 100.0f);
		
	// We must see if there exist lambda and mu such that:
	// lambda[P11, P12] = mu[P21, P22]  with  0 < lambda, mu < 1.
	// This give us two equations with two unknowns.
	// We set up a few parameters
	a = pP12.getX() - pP11.getX();
	b = pP22.getX() - pP21.getX();
	c = pP12.getY() - pP11.getY();
	d = pP22.getY() - pP21.getY();
	det = a * d - b * c; // determinant of equation matrix 

	// det == 0 means that the edges are parallel.
	// We assume that they must not intersect in this case,
	// since 'overlapping' edges are dealt with beforehand
	if (abs(det) < 0.00000001F)
		return FALSE;

	// If you do the maths, you discover that if lambda and mu exist, then
	// lambda = (dx - by) / det  and  mu = (cx - ay) / det
	// where  x = x21 - x11  and  y = y21 - y11
	x = pP21.getX() - pP11.getX();
	y = pP21.getY() - pP11.getY();
	lambda = (d * x - b * y) / det;
	if (lambda < 0 || lambda > 1)
		return FALSE;
	mu = (c * x - a * y) / det;
	if (mu < 0 || mu > 1)
		return FALSE;

	return TRUE;
}

	
void CLS_Physics::applyPhysics(long long elapsedTime, std::vector<CLS_Shapes*> *objects)
{

	if (objects == nullptr)
		return;

	for (std::vector<CLS_Shapes*>::iterator i = objects->begin(); i != objects->end(); i++)
	{
		for(std::vector<CLS_Shapes*>::iterator j = i+1; j != objects->end(); j++)
		{
			//Check for approx collision/Fast collision algorithm
			if (CLS_Physics::collision_Manhattan_Dist((*i),(*j)))
			{
				if (CLS_Physics::collision_Euclidian_Dist((*i),(*j)))
				{
					CLS_Physics::math_Apply_Collision_Momentum((*i),(*j));

				}
			}
		}
	}


}

void CLS_Physics::applyGravity(long long elapsedTime, CLS_Shapes* object)
{
	CLS_VectorPoint<float> temp = object->getSpeed();

	temp.setY(temp.getY() + ((ACCELARATION/1000.0f) * elapsedTime));

	object->setSpeed(temp);

}
	
void CLS_Physics::applyObjectMovment(long long elapsedTime,CLS_Shapes* object)
{
	
	object->setLocation(object->getLocation() + object->getSpeed());

	CLS_VectorPoint<float> temp1,temp2,temp3;
	temp1 = object->getCollisionBox();
	temp2 = object->getLocation();
	temp3 = object->getSpeed();

	if (temp2.getY() < -(CLS_Physics::viewSize.getY()/2) + (temp1.getY()/2) && temp3.getY() < 0.0f)
	{
		temp3.setY((temp3.getY() * (1.0f - object->getBounceFactor()))* -1);
		temp2.setY(temp2.getY() + -(temp2.getY() - (-(CLS_Physics::viewSize.getY()/2) + (temp1.getY()/2))));

		CLS_Physics::collisionCounter++;
	}
	else if (temp2.getY() > (CLS_Physics::viewSize.getY()/2) - (temp1.getY()/2))
	{
		temp3.setY((temp3.getY() * (1.0f - object->getBounceFactor())) * -1);
		temp2.setY(temp2.getY() - (temp2.getY() - ((CLS_Physics::viewSize.getY()/2) - (temp1.getY()/2))));

		CLS_Physics::collisionCounter++;
	}
	if (temp2.getX() < -(CLS_Physics::viewSize.getX()/2) + (temp1.getY()/2))
	{
			
		temp3.setX((temp3.getX() * (1.0f - object->getBounceFactor()))* -1 );
		temp2.setX(temp2.getX() + ( (((CLS_Physics::viewSize.getX()/2)*-1) + (temp1.getX()/2)) - temp2.getX() ));
		CLS_Physics::collisionCounter++;
	}
	else if(temp2.getX() > (CLS_Physics::viewSize.getX()/2) - (temp1.getX()/2))
	{
		
		temp3.setX((temp3.getX() * (1.0f - object->getBounceFactor())) * -1);
		temp2.setX(temp2.getX() - (temp2.getX() - ((CLS_Physics::viewSize.getX()/2) - (temp1.getX()/2))));

		CLS_Physics::collisionCounter++;
	}
	
		object->setLocation(temp2);
		object->setSpeed(temp3);
}

void CLS_Physics::math_Apply_Collision_Momentum(CLS_Shapes* obj1, CLS_Shapes* obj2)
{
	float o1X = obj1->getLocation().getX();
	float o1Y = obj1->getLocation().getY();
	float o1XS = obj1->getSpeed().getX();
	float o1YS = obj1->getSpeed().getY();
	float o1M = obj1->getMass();

	float o2X = obj2->getLocation().getX();
	float o2Y = obj2->getLocation().getY();
	float o2XS = obj2->getSpeed().getX();
	float o2YS = obj2->getSpeed().getY();
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
	CLS_VectorPoint<float> fv1;
	fv1.setX((v1fv * unX) + ( v1ut * utX ));
	fv1.setY((v1fv * unY) + ( v1ut * utY ));

	CLS_VectorPoint<float> fv2;
	fv2.setX((v2fv * unX) + ( v2ut * utX ));
	fv2.setY((v2fv * unY) + ( v2ut * utY ));

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