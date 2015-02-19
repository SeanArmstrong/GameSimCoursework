#pragma once
#include "Matrix4.h"
#include "Mesh.h"
#include "Shader.h"


class RenderObject	{
public:
	RenderObject(void);
	RenderObject(Mesh*m, Shader*s, GLuint t = 0);
	~RenderObject(void);

	void Intialize(Mesh* m, Shader* s, GLuint t = 0);

	Mesh*	GetMesh()	const			{return mesh;}
	void	SetMesh(Mesh*m)				{mesh = m;}

	Shader* GetShader()		const		{return shader; }
	void	SetShader(Shader*s)			{shader = s;}

	GLuint	GetTexture()		const	{ return texture; }
	void	SetTexture(GLuint tex)		{ texture = tex; }

	GLuint	GetSmileyTexture()		const	{ 
		return smileyTex;
	}
	void	SetSmileyTexture(GLuint tex)		{ smileyTex = tex; }

	GLuint	GetStaticTexture()		const	{ return staticTex; }
	void	SetStaticTexture(GLuint tex)		{ staticTex = tex; }

	GLuint	GetBrickTexture()		const	{ return brickTex; }
	void	SetBrickTexture(GLuint tex)		{ brickTex = tex; }

	void	SetModelMatrix(Matrix4 mat) {modelMatrix = mat;}
	Matrix4 GetModelMatrix()	const	{return modelMatrix;}

	virtual void Update(float msec);

	virtual void Draw() const;

	//virtual void Update(float msec);

	void	AddChild(RenderObject &child) {
		children.push_back(&child);
		child.parent = this;
	}

	Matrix4 GetWorldTransform() const {
		return worldTransform;
	}

	const vector<RenderObject*>& GetChildren() const  {
		return children;
	}

protected:
	Mesh*	mesh;
	Shader*	shader;

	GLuint texture;
	GLuint smileyTex;
	GLuint staticTex;
	GLuint brickTex;

	Matrix4 modelMatrix;
	Matrix4 worldTransform;

	RenderObject*			parent;
	vector<RenderObject*>	children;
};

