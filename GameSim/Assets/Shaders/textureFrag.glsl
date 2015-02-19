#version 150 core
//Perform a non-trivial blend between two textures

uniform sampler2D smileyTex;

uniform float scaleFactor;

in Vertex {
	smooth vec4 colour;
	smooth vec2 texCoord;
} IN;

out vec4 gl_FragColor;

void main(void){
	gl_FragColor = texture(smileyTex, IN.texCoord);
}