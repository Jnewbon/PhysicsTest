#version 330

uniform vec4 objColour;

// input packet
in packet {

	vec4 colour;
	vec2 textureCoord;

} inputFragment;


// output packet
layout (location = 0) out vec4 fragmentColour;


void main(void) {

	fragmentColour = vec4(1.0f,1.0f,0.0f,1.0f);//inputFragment.colour;
}