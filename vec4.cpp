#include "vec4.h"

vec4::vec4()
{
	this->pos[0] = 0.0f;
	this->pos[1] = 0.0f;
	this->pos[2] = 0.0f;
	this->pos[3] = 0.0f;
}

vec4::vec4(float x, float y, float z, float a)
{
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = z;
	this->pos[3] = a;
}