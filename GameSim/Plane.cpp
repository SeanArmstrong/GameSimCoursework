#include "Plane.h"

Plane::Plane(){
	// No
}

Plane::Plane(Vector3& plane, Vector3 a, Vector3 b, Vector3 c, Vector3 d, const float& distance){
	/*
	Plane Ax + By + Cz + D = 0
	(A, B, C) is Normal and D is distance

	*/
	Mesh* m = Mesh::GenerateQuad(a,b,c,d);
	Shader* s = new Shader("assets/shaders/basicvert.glsl", "assets/shaders/basicFrag.glsl");
	ro = new RenderObject(m, s);

	//normal = plane.GetNormalised();
	this->distance = distance;
	this->elasticity = 0.5f;

	// TODO: Test this model matrix
	//ro->SetModelMatrix(Matrix4::Translation(normal * distance) * Matrix4::Rotation(90, normal.Reverse())
	//	* Matrix4::Rotation(90, Vector3(1, 0, 0)) * Matrix4::Scale(Vector3(distance, distance, distance)));
	ro->SetModelMatrix(Matrix4::Scale(Vector3(distance, distance, distance)));
	ro->Update(0.0f);
}


Plane::~Plane(){
	delete ro;
}

bool Plane::isColliding(const Sphere& s) const {
	// N dot S + d < r
	// N is normal of plane
	// S is position of center of sphere
	// d is distance 
	return ((Vector3::Dot(normal, s.getPosition()) + distance) < s.getRadius());
}

// TODO: Check distance
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
