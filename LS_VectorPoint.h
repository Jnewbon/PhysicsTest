#pragma once
template <typename T>
struct spacialPoint
{

	spacialPoint() 
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	spacialPoint(T valueX, T valueY) 
	{
		this->x = valueX;
		this->y = valueY;
		this->z = 0;
	}
	spacialPoint(T valueX, T valueY, T valueZ) 
	{
		this->x = valueX;
		this->y = valueY;
		this->z = valueZ;
	}

	//Do the simple math here, the more complx stuff we will do the the class
	spacialPoint<T> operator+ (const spacialPoint<T>& sp1)
	{
			spacialPoint<T> temp;
			temp.x = this->x + sp1.x;
			temp.y = this->y + sp1.y;
			temp.z = this->z + sp1.z;
			return temp;
	}
	
	spacialPoint<T> operator- (const spacialPoint<T>& sp1)
	{
			spacialPoint<T> temp;
			temp.x = this->x - sp1.x;
			temp.y = this->y - sp1.y;
			temp.z = this->z - sp1.z;
			return temp;
	}

	//Cartesian Coordinates
	T x;
	T y;
	T z;


};



/*
A Vector point that can handle any coordinate system that is 2 or 3 dimentional 
*/
template <class T>
class CLS_VectorPoint
{
public:

	CLS_VectorPoint(void);
	CLS_VectorPoint(T, T);
	CLS_VectorPoint(T, T, T);
	CLS_VectorPoint(spacialPoint<T>);

	~CLS_VectorPoint(void);

	T getX();
	T getY();
	T getZ();
	spacialPoint<T> getAll();

	void setX(T);
	void setY(T);
	void setZ(T);
	void setAll(spacialPoint<T>);

	//The simple math add...
	CLS_VectorPoint<T> operator+ (const CLS_VectorPoint<T>& vec1)
	{
		return this->point + vec1.point;
	}
	// and takeaway 
	CLS_VectorPoint<T> operator- (const CLS_VectorPoint<T>& vec1)
	{
		return this->point - vec1.point;
	}

	//Now the slightly more complex math
	//Multiplication this will be overloaded as there 2 types, multiple by a scalar, and multiply by another vector
	CLS_VectorPoint<T> operator* (const T scalar)
	{
		return spacialPoint<float>(this->getX() * scalar, this->getY() * scalar, this->getZ() * scalar);
	}

	//And of course divide bay a scaler
	CLS_VectorPoint<T> operator/ (const T scalar)
	{
		return spacialPoint<float>(this->getX() / scalar, this->getY() / scalar, this->getZ() / scalar);
	}

	T dotProduct(const CLS_VectorPoint<T> vec1)
	{
		//multiply each axis ot both points then add them all together (A · B = A.x * B.x + A.y * B.y + A.z * B.z)
		return this->getX * vec1.getX + this->getY * vec1.getY() + this->getZ() * vec1.getZ(); 
	}

	CLS_VectorPoint<T> crossProduct(const CLS_VectorPoint<T> vec1)
	{
		// C.x = (A.y * B.z) - (A.z * B.y)
		// C.y = (A.z * B.x) - (A.x * b.z)
		// C.z = (A.x * B.y) - (A.y * B.x)
		// Or C = |a| |b| sin(?) n
		
		return spacialPoint(	(this->getY() * vec1.getZ()) - (this->getZ() * vec1.getY()), 
								(this->getZ() * vec1.getX()) - (this->getX() * vec1.getZ()), 
								(this->getX() * vec1.getY()) - (this->getY() * vec1.getX()) );
	}

	T magnitude()
	{
		return sqrt(this->getX() * this->getX() + this->getY() * this->getY() + this->getZ() * this->getZ());
	} 
	
	T angle()
	{
		return 0;
	}




private:

	spacialPoint<T> point;

};

//apreantly the stupid compliler cant figure out this is the same when it is in a sperate file... retard eh

template<class T>
CLS_VectorPoint<T>::CLS_VectorPoint(void)
{
	//Leave it to the default (will be 0's)
}

template<class T>
CLS_VectorPoint<T>::CLS_VectorPoint(T newX, T newY)
{
	this->point = spacialPoint<T>(newX,newY);
}

template<class T>
CLS_VectorPoint<T>::CLS_VectorPoint(T newX, T newY, T newZ)
{
	this->point = spacialPoint<T>(newX,newY,newZ);
}

template<class T>
CLS_VectorPoint<T>::CLS_VectorPoint(spacialPoint<T> newValue)
{
	this->point = newValue;
}

template<class T>
CLS_VectorPoint<T>::~CLS_VectorPoint(void)
{
	//Dont need to do anything
}

template<class T>
T CLS_VectorPoint<T>::getX(void)
{
	return this->point.x;
}

template<class T>
T CLS_VectorPoint<T>::getY(void)
{
	return this->point.y;
}

template<class T>
T CLS_VectorPoint<T>::getZ(void)
{
	return this->point.z;
}

template<class T>
spacialPoint<T> CLS_VectorPoint<T>::getAll(void)
{
	return this->point;
}

template<class T>
void CLS_VectorPoint<T>::setX(T value)
{
	this->point.x = value;
}

template<class T>
void CLS_VectorPoint<T>::setY(T value)
{
	this->point.y = value;
}

template<class T>
void CLS_VectorPoint<T>::setZ(T value)
{
	this->point.y = value;
}

template<class T>
void CLS_VectorPoint<T>::setAll(spacialPoint<T>)
{
	this->point = value;
}