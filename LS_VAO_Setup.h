#pragma once

#include "options.h"
#include "GL\glew\glew.h"
#include "GL\glut.h"
#include "GL\freeglut.h"

class CLS_VAO_Setup
{
public:

	//Template the Static function so that the size of the array is parsed as well
	//other wise the array pointer decay to a basic pointer losing the size infomation
	//Damn I sound smart there :P
	template <unsigned S,unsigned T,unsigned U,unsigned V>
	//Static function as it does not need to be instaniated
	static GLuint setupVAO(GLfloat (&posVBA)[S], GLuint (&colVBA) [T], GLfloat (&texVBA) [U], GLuint (&verInd) [V])
	{

		GLuint objectVBA, objectPosVBO, objectColourVBO, objectTextureVBO, objectIndicesVBO;

		glGenVertexArrays(1, &objectVBA);
		glBindVertexArray(objectVBA);

		// copy vertex position data to VBO
		glGenBuffers(1, &objectPosVBO);
		glBindBuffer(GL_ARRAY_BUFFER, objectPosVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(posVBA), posVBA, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);

		// copy star vertex colour data to VBO
		glGenBuffers(1, &objectColourVBO);
		glBindBuffer(GL_ARRAY_BUFFER, objectColourVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colVBA), colVBA, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_INT, GL_TRUE, 0, (const GLvoid*)0);

		// copy star vertex texture data to VBO
		glGenBuffers(1, &objectTextureVBO);
		glBindBuffer(GL_ARRAY_BUFFER, objectTextureVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texVBA), texVBA, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	
		// enable position, colour and texture coordinate buffer inputs
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// setup star vertex index array
		glGenBuffers(1, &objectIndicesVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectIndicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verInd), verInd, GL_STATIC_DRAW);

		glBindVertexArray(0);

		return objectVBA;

	}

};
