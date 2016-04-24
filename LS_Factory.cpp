#include "LS_Factory.h"
#include "LS_Circle.h"
#include "CLS_Line.h"

std::list<CLS_Shapes*> CLS_Factory::allObjMV;

CLS_Factory::CLS_Factory()
{
}

void CLS_Factory::registerObj(CLS_Shapes* newObj)
{
	//Add the new object to the tracked list
	CLS_Factory::allObjMV.push_back(newObj);
}

CLS_Shapes* CLS_Factory::createObj(CLS_Shapes::Type objType)
{
	CLS_Shapes* obj = NULL;
	switch (objType)
	{
	case CLS_Shapes::CIRCLE:
		obj = new CLS_Circle();
		CLS_Factory::registerObj(obj);
		return obj;
		break;

	case CLS_Shapes::LINE:
		obj = new CLS_Line();
		CLS_Factory::registerObj(obj);
		return obj;
		break;

	default:
		throw 1;
	}

}
