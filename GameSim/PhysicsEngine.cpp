#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine(){
}


PhysicsEngine::~PhysicsEngine(){
}

Sphere* PhysicsEngine::addSphere(const Vector3& pos, const float& radius, float mass, Vector3 force){
	Sphere* s = new Sphere(pos, radius, mass, force);
	spheres.push_back(s);
	sortSpheres();
	return s;
}

Plane* PhysicsEngine::addPlane(const Vector3& plane, const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d, const float& distance){
	Plane* p = new Plane(plane, a, b, c, d, distance);
	planes.push_back(p);

	return p;
}

/*
* Sorts spheres in the x axis by their smallest point
* caculated by center.x - radius
* Uses insertion sort due to its efficency over almost
* sorted data
*/
void PhysicsEngine::sortSpheres(){
	int j;
	Sphere* val;

	for (unsigned int i = 1; i < spheres.size(); i++){
		val = spheres[i];
		j = i - 1;

		while (j >= 0 && spheres[j]->getSmallestXPoint() > val->getSmallestXPoint()){
			spheres[j + 1] = spheres[j];
			j = j - 1;
		}
		spheres[j + 1] = val;
	}
}

void PhysicsEngine::rotatePlanes(const Vector3& axis){
	std::vector<Plane*>::const_iterator ip;
	for (ip = planes.begin(); ip < planes.end(); ++ip) {
		Vector3 norm = (**ip).getNormal();
		Vector3 unitVector = norm.unitVector();
		Quaternion quat = Quaternion::AxisAngleToQuaterion(axis, 2.0f);

		Matrix4 mat = quat.ToMatrix();

		Vector3 resultnorm = mat * unitVector;

		float distance = (**ip).getDistance();
		(**ip).setNormal(resultnorm);

		(**ip).getRenderObject()->SetModelMatrix((**ip).getRenderObject()->GetModelMatrix() * mat);
		(**ip).getRenderObject()->Update(0.0f);
		
	}
}

void PhysicsEngine::applyGravity(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).applyNewForce(Vector3(0, -9.81f, 0));
	}
}

void  PhysicsEngine::applyUpwardsForce(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).applyNewForce(Vector3(0, 2500.0f, 0));
	}
}

void PhysicsEngine::removeAcclerationFromAllSpheres(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).applyNewForce(Vector3(0, 0, 0));
	}
}

void PhysicsEngine::setDragSphereFactor(const float& drag){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).setDragFactor(drag);
	}
}