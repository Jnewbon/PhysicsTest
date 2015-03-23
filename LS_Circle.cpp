#include "LS_Circle.h"
#include <cmath>
#include "LS_VAO_Setup.h"

const double PI = 3.14152695;

GLuint CLS_Circle::circleTemplateVAO = 0;

void CLS_Circle::initCirc()
{

	//Create the Points for the vetexes around the entire circle and store them in an array
	GLfloat circleTemplateVBO[(36*2)];
 
	for (int i=0; i<(36*2); i+=2) {

		circleTemplateVBO[i] = float(cos(float(i*10*float(PI/180))));
		circleTemplateVBO[i+1] = float(sin(float(i*10*float(PI/180))));

	}

	//For the Default colours
	GLuint ColourTemplateVBO[36*3]; //Declare the temp array for the Circle

	for (int i=0; i<(36*3); i+=3) {

		ColourTemplateVBO[i] = 20;
		ColourTemplateVBO[i+1] = 20;
		ColourTemplateVBO[i+2] = 20;
	}

	//Point order of all the vertexes

	GLuint PointOrder[36];

	for (int i=0; i<(36); i+=1) {

		PointOrder[i] = i;
	}


	//Using the Templated Class for creating a VAO create the VAO
	

	GLfloat textureTemplateVBO[(36*2)];
 
	for (int i=0; i<(36*2); i+=2) {

		textureTemplateVBO[i] = circleTemplateVBO[i];
		textureTemplateVBO[i+1] = circleTemplateVBO[i+1];

	}

	circleTemplateVAO = CLS_VAO_Setup::setupVAO(circleTemplateVBO,
												ColourTemplateVBO,
												textureTemplateVBO,
												PointOrder);


}

CLS_Circle::CLS_Circle(void)
{

	this->setType(CIRCLE);
	this->setModelVAO(this->circleTemplateVAO);
	this->setScale(20.0f);

	this->setBounceFactor(0.1);
}

void CLS_Circle::setScale(float newScale)
{
	CLS_Shapes::setScale(newScale);
	//Width of the circle is -1.0f to 1.0f which is 2.0f. Wdht and height is the same
	this->setCollisionBox(glm::vec3(2.0f * this->getScale(), 2.0f * this->getScale(), 2.0f * this->getScale()));
}

CLS_Circle::~CLS_Circle(void)
{

}

/*
void CLS_Circle::draw()
{
	glBindVertexArray(this->getModelVAO());
	
	glDrawElements(GL_TRIANGLE_FAN, this->getType(), GL_UNSIGNED_INT, (GLvoid*)0);

	glBindVertexArray(0);
}*/

//void CLS_Circle::setColour(int r, int g, int b)
//{
//		//Create the Points for the vetexes around the entire circle and store them in an array
//	GLfloat circleTemplateVBO[(36*2)];
// 
//	for (int i=0; i<(36*2); i+=2) {
//
//		circleTemplateVBO[i] = float(cos(float(i*10*float(PI/180))));
//		circleTemplateVBO[i+1] = float(sin(float(i*10*float(PI/180))));
//
//	}
//
//	//For the Default colours
//	GLuint ColourTemplateVBO[36*3]; //Declare the temp array for the Circle
//
//	for (int i=0; i<(36*3); i+=3) {
//
//		ColourTemplateVBO[i] = r;
//		ColourTemplateVBO[i+1] = g;
//		ColourTemplateVBO[i+2] = b;
//	}
//
//	//Point order of all the vertexes
//
//	GLuint PointOrder[36];
//
//	for (int i=0; i<(36); i+=1) {
//
//		PointOrder[i] = i;
//	}
//
//
//	//Using the Templated Class for creating a VAO create the VAO
//	
//
//	GLfloat textureTemplateVBO[(36*2)];
// 
//	for (int i=0; i<(36*2); i+=2) {
//
//		textureTemplateVBO[i] = circleTemplateVBO[i];
//		textureTemplateVBO[i+1] = circleTemplateVBO[i+1];
//
//	}
//
//	this->setModelVAO(CLS_VAO_Setup::setupVAO(circleTemplateVBO,
//												ColourTemplateVBO,
//												textureTemplateVBO,
//												PointOrder));
//
//}