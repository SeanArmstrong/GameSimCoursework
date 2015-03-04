/*
* Author: Sean Armstrong
* Adapted from NCLGL Renderer and OGLRenderer to use SFML
*/

#pragma once
#include "RenderObject.h"

class SFMLRenderer
{
public:
	SFMLRenderer();
	~SFMLRenderer(void);

	virtual void RenderScene();


	virtual void Render(const RenderObject &o);

	virtual void UpdateScene(float msec);

	void AddRenderObject(RenderObject& r) {
		renderObjects.push_back(&r);
	}
	
	void UpdateShaderMatrices(GLuint program);

	void			SetProjectionMatrix(Matrix4 m) {
		projMatrix = m;
	}

	void			SetViewMatrix(Matrix4 m) {
		viewMatrix = m;
	}

private:
	vector<RenderObject*> renderObjects;
	Matrix4 projMatrix;
	Matrix4 modelMatrix;
	Matrix4 viewMatrix;
	Matrix4 textureMatrix;

	bool	init;			//Did the renderer initialise properly?

	static int		width;
	static int		height;

};

