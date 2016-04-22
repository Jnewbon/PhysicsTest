#pragma once
#include "LS_Shapes.h"
#include <list>

class CLS_Factory
{
private:
	//No point for the facotry to be instaniated so, prevent that from happening
	CLS_Factory(void);
	//As the Factory will not be instantiated there is no need for a destructor

	static std::list<CLS_Shapes*> allObjMV;
	static void registerObj(CLS_Shapes*);

public:

	static void DestoryAllObjects() {};

	static CLS_Shapes* createObj(CLS_Shapes::Type);

};

