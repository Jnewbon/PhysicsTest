#include "LS_Factory.h"
#include "LS_Circle.h"
#include "CLS_Line.h"
#include "error.h"


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
	switch (objType)
	{
	case CLS_Shapes::CIRCLE:
		CLS_Shapes* obj = new CLS_Circle();
		CLS_Factory::registerObj(obj);
		return obj;
		break;

	case CLS_Shapes::LINE:
		CLS_Shapes* obj = new CLS_Line();
		CLS_Factory::registerObj(obj);
		return obj;
		break;

	default:
		throw ERROR_WARNING, ERRORCODE::INVALID_TYPE;
	}

}
