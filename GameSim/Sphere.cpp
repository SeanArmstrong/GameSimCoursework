#include "Sphere.h"
#include <cmath>


Sphere::Sphere(){
	Sphere(Vector3(0, 0, 0), 1.0f, 1.0f, Vector3(0, 0, 0));
}

Sphere::Sphere(const Vector3& pos, const float& radius, float mass, Vector3 force){
	this->position = pos;
	this->previousPosition = pos;
	this->mass = mass;
	this->oneovermass = 1 / mass;
	this->acceleration = force / mass;
	this->radius = radius;
	this->elasticity = 1;
	this->dragFactor = 1.0f;
	this->atRest = false;
	

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

void Sphere::resolveCollisions(Sphere& s, const float msec){
	// Get Data
	float distance = sqrt(position.distanceBetweenTwoPointsSquared(s.position));
	float penetrationDistance = this->radius + s.radius - distance;
	
	Vector3 normal = this->position - s.position;
	normal.Normalise();

	Vector3 point = this->position - normal*(s.radius - penetrationDistance*0.5f);

	// Resolve Collision

	Vector3 vA = this->getVelocity(msec);
	Vector3 vB = s.getVelocity(msec);

	// Vab = Va - Vb
	// Vn = Vab dot N
	float vN = Vector3::Dot((vA - vB), normal);

	// Elasiticity of collision is average of two colliding spheres
	float E = (this->elasticity + s.elasticity) * 0.5f;

	// Impulse = -(1+E)Vab dot N / N dot (normal(1/ma + 1/mb))
	float impulse = (-(1 + E) * vN) / Vector3::Dot(normal, normal * (this->oneovermass + s.oneovermass));

	// Move the shapes so they are no longer overlapping
	// Need to be moved in the direction of the contact normal
	// by the penetration distance over two so both spheres
	// move equivilent distance from one another
	this->moveBy(normal * penetrationDistance * 0.5f);
	s.moveBy(-(normal * (penetrationDistance * 0.5f)));

	//vAAfter = vABefore + impulse/massA * N
	this->setVelocity(vA + (normal * impulse * this->oneovermass), msec);
	s.setVelocity(vB - (normal * impulse * s.oneovermass), msec);
	atRest = false;
}

void Sphere::setDragFactor(const float& drag){
	dragFactor = drag;
}