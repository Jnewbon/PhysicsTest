#version 330



uniform mat4 T; // model-view-projection matrix


// input vertex packet
layout (location = 0) in vec2 position;
layout (location = 1) in vec4 defaultColour;
//layout (location = 2) in vec2 textureCoord;



// output vertex packet
out packet {

	vec4 colour;
	//vec2 textureCoord;

} outputVertex;



void main(void) {

	outputVertex.colour = defaultColour;
	//outputVertex.textureCoord = textureCoord;

	gl_Position = T * vec4(position, 0.0, 1.0); // MUST set gl_Position
}

