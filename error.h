#pragma once
#include <string>
#include <iostream>
enum error_type{
	ERROR_WARNING,
	ERROR_CITICAL
};
enum ERRORCODE {
	INVALID_TYPE
};



void catch_Error(error_type type, ERRORCODE error)
{

	std::string errorlist[] = {
						"The type given was invalid.",				// INVALID_TYPE
	};

	switch (error)
	{
	case INVALID_TYPE:
		catch_Error(type, errorlist[error]);
		break;
	default:
		break;
	}

}
void catch_Error(error_type type, std::string error)
{
	switch (type)
	{
	case ERROR_WARNING:
		std::cout << "WARNING: " << error << std::endl;
		break;
	case ERROR_CITICAL:
		std::cout << "CRITICAL: " << error << std::endl;
		break;
	default:
		break;
	}
}