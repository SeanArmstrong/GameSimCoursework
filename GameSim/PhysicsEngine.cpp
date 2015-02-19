#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine()
{
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::addSphere(const Sphere& s){
	spheres.push_back(s);
}