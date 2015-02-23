#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine(){
}


PhysicsEngine::~PhysicsEngine()
{
}

Sphere* PhysicsEngine::addSphere(const Vector3& pos, const float& radius, float mass, Vector3 force){
	Sphere* s = new Sphere(pos, radius, mass, force);
	spheres.push_back(s);

	return s;
}

Plane* PhysicsEngine::addPlane(Vector3& plane, const float& distance){
	Plane* p = new Plane(plane, distance); 
	planes.push_back(p);

	return p;
}