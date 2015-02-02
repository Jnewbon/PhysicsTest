#include "matrix4.h"

matrix4::matrix4()
{
	for (int i = 0; i < 16; i++)
		matrix[i] = 0.0f;
}

matrix4::matrix4(
	float m1 = 1.0f, float m2 = 0.0f, float m3 = 0.0f, float m4 = 0.0f,
	float m5 = 0.0f, float m6 = 1.0f, float m7 = 0.0f, float m8 = 0.0f,
	float m9 = 0.0f, float m10 = 0.0f, float m11 = 1.0f, float m12 = 0.0f,
	float m13 = 0.0f, float m14 = 0.0f, float m15 = 0.0f, float m16 = 1.0f)
{
	matrix[0] = m1;
	matrix[1] = m2;
	matrix[2] = m3;
	matrix[3] = m4;
	matrix[4] = m5;
	matrix[5] = m6;
	matrix[6] = m7;
	matrix[7] = m8;
	matrix[8] = m9;
	matrix[9] = m10;
	matrix[10] = m11;
	matrix[11] = m12;
	matrix[12] = m13;
	matrix[13] = m14;
	matrix[14] = m15;
	matrix[15] = m16;
}

matrix4 matrix4::operator* (const matrix4& m1)
{

	float mat[16];
	//matrix[0] = (matrix1[0] * matrix2[0]) + (matrix1[1] * matrix2[4]) + (matrix1[2] * matrix2[8]) + (matrix1[3] * matrix2[12]);
	//matrix[1] = (matrix1[0] * matrix2[1]) + (matrix1[1] * matrix2[5]) + (matrix1[2] * matrix2[9]) + (matrix1[3] * matrix2[13]);

	for (int a = 0; a < 16; a++)
	{
		int mat1row = (a - (a % 4)) / 4;
		int mat2col = a % 4;

		float num = 0.0f;

		for (int b = 0; b < 4; b++)
		{
			num += this->matrix[((mat1row * 4) + b)] * m1.matrix[((b * 4) + mat2col)];
		}
		mat[a] = num;
	}

	return matrix4(mat[0], mat[1], mat[2], mat[3],
		mat[4], mat[5], mat[6], mat[7], 
		mat[8], mat[9], mat[10], mat[11], 
		mat[12], mat[13], mat[14], mat[15]);

}

matrix4 matrix4::ScaleMatrix(float x)
{
	return ScaleMatrix(x, 1.0f, 1.0f);
}

matrix4 matrix4::ScaleMatrix(float x, float y)
{
	return ScaleMatrix(x, y, 1.0f);
}

matrix4 matrix4::ScaleMatrix(float x, float y , float z)
{
	return matrix4(	x, 0.0f, 0.0f, 0.0f,
					0.0f, y, 0.0f, 0.0f,
					0.0f, 0.0f, z, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);

}

matrix4 matrix4::TranslationMatrix(float x, float y)
{
	return TranslationMatrix(x, y, 0.0f);
}

matrix4 matrix4::TranslationMatrix(float x, float y, float z)
{
	return matrix4(	1.0f, 0.0f, 0.0f, x,
					0.0f, 1.0f, 0.0f, y,
					0.0f, 0.0f, 1.0f, z,
					0.0f, 0.0f, 0.0f, 1.0f);
}


std::ostream& operator<<(std::ostream& os, const matrix4& dt)
{
	os << "M=:\t {\t";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			os << dt.matrix[(i*4) + j] << ",\t";

		}
		if (i == 3)
			os << "}" << std::endl;
		else
			os << std::endl << "\t\t";

	}
	return os;
}
//matrix4 matrix4::RotationMatrix(float x, float y)
//{
//	return RotationMatrix(x, y, 0.0f);
//}
//
//matrix4 matrix4::RotationMatrix(float x, float y, float z)
//{
//
//}
