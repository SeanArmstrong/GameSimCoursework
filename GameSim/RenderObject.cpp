#include "RenderObject.h"


RenderObject::RenderObject(void)	{
	mesh	= NULL;
	shader	= NULL;
	texture = NULL;
	parent  = NULL;
}

RenderObject::RenderObject(Mesh*m, Shader*s, GLuint t) {
	Intialize(m, s, t);
}

void RenderObject::Intialize(Mesh*m, Shader*s, GLuint t) {
	mesh = m;
	shader = s;
	parent = NULL;

	string brick = "assets/textures/brick.jpg";

	glGenTextures(1, &texture);

	texture = SOIL_load_OGL_texture(brick.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

}


RenderObject::~RenderObject(void)
{
	glDeleteTextures(1, &texture);
	delete shader;
}


void RenderObject::Update(float msec) {
	if(parent) {
		worldTransform = parent->modelMatrix * modelMatrix;
		//worldTransform = modelMatrix * parent->modelMatrix;
	}
	else {
		worldTransform = modelMatrix;
	}

	for(vector<RenderObject*>::const_iterator i = children.begin(); i != children.end(); ++i ) {
		(*i)->Update(msec);
	}
}

void RenderObject::Draw() const {
	if(mesh) {
		/* Textures */
		GLuint program = GetShader()->GetShaderProgram();

		glUseProgram(program);

		glEnable(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(program, "brick"), GL_TEXTURE0);

		mesh->Draw();
	}
}