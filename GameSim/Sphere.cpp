#include "Sphere.h"


Sphere::Sphere(){
	this->position = Vector3(0, 0, 0);
	this->previousPosition = this->position;
	this->mass = 1;
	this->acceleration = Vector3(0, 0, 0);
	this->radius = 1;

	Mesh* m = Mesh::LoadMeshObj("assets/models/sphere.obj");
	Shader* s = new Shader("assets/shaders/basicvert.glsl", "assets/shaders/basicFrag.glsl");
	ro = RenderObject(m, s);
}

Sphere::Sphere(const Vector3& pos, const float& radius, float mass, Vector3 force){
	this->position = pos;
	this->previousPosition = pos;
	this->mass = mass;
	this->acceleration = force / mass;
	this->radius = radius;
	

	Mesh* m = Mesh::LoadMeshObj("assets/models/sphere.obj");
	Shader* s = new Shader("assets/shaders/basicvert.glsl", "assets/shaders/basicFrag.glsl");
	ro = RenderObject(m, s);
}

Sphere::~Sphere(){
}

bool Sphere::isColliding(const Sphere& s) const {
	float radius = this->radius + s.radius;
	float distance = position.distanceBetweenTwoPointsSquared(s.position);
	return distance < (radius*radius);
}
