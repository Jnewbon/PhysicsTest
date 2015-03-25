#version 330

//input Vertex Packet
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 textureCoord;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

//output vertex Packet
out packet {

	vec4 color;
	vec2 textureCoord;
	
} outputVertex;

void main(void) {
	
	//outputVertex.color = color;
	//outputVertex.textureCoord = textureCoord;
	
	gl_Position = viewMatrix * modelMatrix * position;
	
}