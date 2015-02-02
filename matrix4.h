#pragma once
#include <iostream>

class matrix4
{

private:
	float matrix[16];
public:

	matrix4();
	matrix4(
		float, float, float, float,
		float, float, float, float,
		float, float, float, float,
		float, float, float, float);

	matrix4 operator* (const matrix4& m1);

	static matrix4 ScaleMatrix(float);
	static matrix4 ScaleMatrix(float, float);
	static matrix4 ScaleMatrix(float, float, float);

	static matrix4 TranslationMatrix(float, float);
	static matrix4 TranslationMatrix(float, float, float);

	//static matrix4 RotationMatrix(float, float);
	//static matrix4 RotationMatrix(float, float, float);

	friend std::ostream& operator<<(std::ostream& os, const matrix4& dt);

};