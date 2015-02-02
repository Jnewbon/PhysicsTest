#version 330

uniform vec4 objectColor;

//input vertex Packet
in packet {

	vec4 color;
	vec2 textureCoord;
	
}inputFragment;

//output packet
layout (location = 0) out vec4 fragmentColor;

void main(void) {

	fragmentColor = objectColor;
    
}