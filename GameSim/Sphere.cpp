#include "Sphere.h"
#include <cmath>


Sphere::Sphere(){
	Sphere(Vector3(0, 0, 0), 1.0f, 1.0f, Vector3(0, 0, 0));
}

Sphere::Sphere(const Vector3& pos, const float& radius, float mass, Vector3 force){
	this->position = pos;
	this->previousPosition = pos;
	this->mass = mass;
	this->acceleration = force / mass;
	this->radius = radius;
	

	Mesh* m = Mesh::LoadMeshObj("assets/models/sphere.obj");
	Shader* s = new Shader("assets/shaders/basicvert.glsl", "assets/shaders/textureFrag.glsl");
	ro = new RenderObject(m, s);
}

Sphere::~Sphere(){
	delete ro;
}

bool Sphere::isColliding(const Sphere& s) const {
	float radius = this->radius + s.radius;
	float distance = position.distanceBetweenTwoPointsSquared(s.position);
	return distance < (radius*radius);
}

bool Sphere::isColliding(const Plane& p) const {
	return p.isColliding(*this);
}

void Sphere::resolveCollisions(Sphere& s){
	// Get Data
	float distance = sqrt(position.distanceBetweenTwoPointsSquared(s.position));
	float penetrationDistance = this->radius + s.radius - distance;
	
	Vector3 normal = this->getPosition() - s.getPosition();
	normal.Normalise();

	Vector3 point = this->getPosition() - normal*(s.getRadius() - penetrationDistance*0.5f);	// Resolve Collision

}
