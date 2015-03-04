#include "Sphere.h"
#include <cmath>


Sphere::Sphere(){
	Sphere(Vector3(0, 0, 0), 1.0f, 1.0f, Vector3(0, 0, 0));
}

Sphere::Sphere(const Vector3& pos, const float& radius, float mass, Vector3 force){
	this->position = pos;
	this->previousPosition = pos;
	this->mass = mass;
	this->oneovermass = 1 / mass; // store inverse mass for computation
	this->acceleration = force / mass;
	this->radius = radius;
	this->elasticity = 1.0f; // no loss in energy by default
	this->dragFactor = 1.0f; // no drag
	this->atRest = false;
	this->gravity = Vector3(0, 0, 0); // off by default
	

	Mesh* m = Mesh::LoadMeshObj("assets/models/sphere.obj");
	Shader* s = new Shader("assets/shaders/basicvert.glsl", "assets/shaders/textureFrag.glsl");
	ro = new RenderObject(m, s);
}

Sphere::~Sphere(){
	delete ro;
}



/* Updating */

/* Update position of sphere using verlet integration */
void Sphere::update(const float& msec){
	if (!atRest){
		Vector3 temp = position;
		position += ((position - previousPosition) + ((acceleration + gravity) * msec * msec)) * dragFactor;
		previousPosition = temp;
		checkRestState(msec);
	}
}

/* 
* If the sphere has moved under given amount in the last 10 frames
* consider it to be at rest until a external force is applied
*/
void Sphere::checkRestState(const float& msec){
	//if (getVelocity(msec).SquaredLength() < 0.00001f && acceleration.SquaredLength() == 0.0f){
	//	atRest = true;
	//}
	if ((position - previousPosition).SquaredLength() < 0.000001f){
		framesAtRest++;
		if (framesAtRest == 10){
			setRestState(true);
		}
	}
	else{
		framesAtRest = 0;
	}
}
/* END Updating */




/* Drawing */
void Sphere::draw(SFMLRenderer& renderer, const float& msec) const {
	ro->SetModelMatrix(Matrix4::Translation(position) * Matrix4::Scale(Vector3(radius, radius, radius)));
	ro->Update(msec);
	renderer.Render(*ro);
}
/* END Drawing */



/* Setters */
// f=ma gives a = f/m
void Sphere::applyNewForce(Vector3& force){
	acceleration = force / mass;
}

/* Applied gravity which is not affected by mass unlike
* acceleration
*/
void Sphere::applyGravity(bool status){
	gravity = status ? Vector3(0, -9.81f, 0) : Vector3(0, 0, 0);
}

/* move the sphere by a given amount */
void Sphere::moveBy(const Vector3& d){
	position = position + d;
	previousPosition = previousPosition + d;
}
/* set the rest state of the sphere */
void Sphere::setRestState(bool state){
	atRest = state;
}

/* Set the drag factor to given float */
void Sphere::setDragFactor(const float& drag){
	dragFactor = drag;
}
/* END Setters */




/* Collisions */
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
	setRestState(false);
}
/* END Collisions */