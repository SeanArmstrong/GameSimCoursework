#include "Plane.h"

Plane::Plane(const Vector3& plane, const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d, const float& distance){
	/*
	Plane Ax + By + Cz + D = 0
	(A, B, C) is Normal and D is distance

	*/
	Mesh* m = Mesh::GenerateQuad(a,b,c,d);
	Shader* s = new Shader("assets/shaders/basicvert.glsl", "assets/shaders/basicFrag.glsl");
	ro = new RenderObject(m, s);

	normal = plane;
	this->distance = distance;
	this->elasticity = 0.5f;
	this->rotatingAxis = Vector3(0, 0, 0);
	this->rotating = false;

	ro->SetModelMatrix(Matrix4::Scale(Vector3(distance*2, distance*2, distance*2)));
	ro->Update(0.0f);
}


Plane::~Plane(){
	delete ro;
}

/* Updating */
void Plane::update(const float& msec){
	Matrix4 mat;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
		rotating = true;
		mat = Matrix4::Rotation(0.2f, Vector3(1, 0, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
		rotating = true;
		mat = mat * Matrix4::Rotation(0.2f, Vector3(0, 0, 1));
	}
	if (rotating){
		rotatePlanes(mat, msec);
	}
}

void Plane::rotatePlanes(Matrix4 mat, const float& msec){
	normal = (mat * normal).unitVector(); //normal is normalised
	ro->SetModelMatrix(mat * ro->GetModelMatrix());
	ro->Update(msec);
}
/* END Updating */


/* Collisions */
bool Plane::isColliding(const Sphere& s) const {
	// N dot S + d < r
	// N is normal of plane
	// S is position of center of sphere
	// d is distance 
	return ((Vector3::Dot(normal, s.getPosition()) + distance) <= s.getRadius());
}

void Plane::resolveCollisions(Sphere& s, const float msec){
	// Get Data
	float penetrationDistance = s.getRadius() - (Vector3::Dot(normal, s.getPosition()) + distance);
	//Vector3 normal = -normal;
	//s.getRadius() - penetrationDistance;
	Vector3 point = s.getPosition() - normal * (s.getRadius() - penetrationDistance);

	// Get Velocity of Sphere
	Vector3 vS = s.getVelocity(msec);

	// Calculate Vector Normal
	float vN = Vector3::Dot(vS, normal);

	// Calculate elasticity of collision with plane
	float E = (this->elasticity + s.getElasticity()) * 0.5f;

	// Impulse = -(1+E)Vab dot N / N dot (normal(1/ma + 1/mb))
	float impulse = (-(1 + E) * vN) / Vector3::Dot(normal, normal * (s.getOneOverMass()));

	// Move sphere so it doesn't overlap plane
	// Only sphere moves so move by full pendistance
	s.moveBy(normal * penetrationDistance);

	// Set new velocity of sphere
	s.setVelocity(vS + (normal * impulse * s.getOneOverMass()), msec);
}
/* End Collisions */