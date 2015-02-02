#version 330

//input Vertex Packet
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 textureCoord;

uniform mat4 modelTrans;
uniform mat4 modelScale;
//uniform mat4 modelRota;

//output vertex Packet
out packet {

	vec4 color;
	vec2 textureCoord;
	
} outputVertex;

void main(void) {
	
	//outputVertex.color = color;
	//outputVertex.textureCoord = textureCoord;
	
	gl_Position = modelScale * modelTrans * position;// * position;
	
}