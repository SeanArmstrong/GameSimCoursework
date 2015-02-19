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
	//theTexture = t;
	parent = NULL;
	string smile = "assets/textures/smiley.png";
	string noise = "assets/textures/noise.png";
	string brick = "assets/textures/brick.jpg";

	glGenTextures(1, &smileyTex);
	glGenTextures(1, &staticTex);
	glGenTextures(1, &brickTex);

	smileyTex = SOIL_load_OGL_texture(smile.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	staticTex = SOIL_load_OGL_texture(noise.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	brickTex = SOIL_load_OGL_texture(brick.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
}




RenderObject::~RenderObject(void)
{
	glDeleteTextures(1, &smileyTex);
	glDeleteTextures(1, &staticTex);
	glDeleteTextures(1, &brickTex);
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
		glBindTexture(GL_TEXTURE_2D, brickTex);
		glUniform1i(glGetUniformLocation(program, "smileyTex"), GL_TEXTURE0);

		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, GetStaticTexture());
		glUniform1i(glGetUniformLocation(program, "staticTex"), GL_TEXTURE1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, GetBrickTexture());
		glUniform1i(glGetUniformLocation(program, "brickTex"), GL_TEXTURE2);*/

		mesh->Draw();
	}
}