#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine(){

}

PhysicsEngine::~PhysicsEngine(){
	std::vector<Plane*>::const_iterator ip;
	for (ip = planes.begin(); ip < planes.end(); ++ip) {
		delete (*ip);
	}
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		delete (*it);
	}
}



/* Updating */

/*
* Updates position of spheres and sorts them.
* Then it checks for collisions with spheres and
* with planes. if there is a collison it will resolve it
*/
void PhysicsEngine::update(const float& msec){
	int restingSpheres = 0;

	// Update all spheres that are not at rest
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		if (!(**it).getRestState()){
			(**it).update(msec);
		}
		else{
			restingSpheres++;
		}
	}

	if (restingSpheres > 0){
		std::cout << "Resting Spheres: " << restingSpheres << std::endl;
	}

	// Sort the spheres by their smallest x point
	sortSpheres();

	// Update all planes
	std::vector<Plane*>::const_iterator ip;
	for (ip = planes.begin(); ip < planes.end(); ++ip) {
		(**ip).update(msec);
	}

	// Find collisions between spheres
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		std::vector<Sphere*>::iterator it2;
		for (it2 = it + 1; it2 < spheres.end(); ++it2) {
			if ((**it2).getSmallestXPoint() >= (**it).getLargestXPoint()){
				// Sweep
				// Smallest points are sorted smallest to largest in the x axis 
				// so if the next element you are checking point is larger
				// than the largest x point of first sphere. It has not collided
				// and nor will anyother spheres after this one
				// so you can break
				break;
			}
			else if ((it != it2) && ((**it).isColliding((**it2)))){
				// resolve collisions
				(**it).resolveCollisions((**it2), msec);
			}
		}
	}

	// Find collisions between spheres and planes
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		std::vector<Plane*>::iterator itp;
		for (itp = planes.begin(); itp < planes.end(); ++itp) {
			if ((**it).isColliding((**itp))){
				(**itp).resolveCollisions((**it), msec);
			}
		}
	}
}
/* End Updating */




/* Drawing */

/*
* Called every frame to draw spheres and planes
*/
void PhysicsEngine::draw(SFMLRenderer& renderer, const float& msec) const {
	std::vector<Sphere*>::const_iterator is;
	for (is = spheres.begin(); is < spheres.end(); ++is) {
		(**is).draw(renderer, msec);
	}

	std::vector<Plane*>::const_iterator ip;
	for (ip = planes.begin(); ip < planes.end(); ++ip) {
		(**ip).draw(renderer);
	}
}

/* End Drawing */

/*
* Creates a sphere and adds it to a vector spheres
* params are starting position, radius, mass and force
* sorts when added
*/
Sphere* PhysicsEngine::addSphere(const Vector3& pos, const float& radius, float mass, Vector3 force){
	Sphere* s = new Sphere(pos, radius, mass, force);
	spheres.push_back(s);
	sortSpheres();
	return s;
}

/*
* Creates a new plane and adds it to a vector of planes
* params are the normal, 4 points and a distance from the nomral
*/
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

/*
* Applies gravity at -9.81m/s
* Times by mass so the force is independent of mass
*/
void PhysicsEngine::applyGravity(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).setRestState(false);
		(**it).applyGravity(true);
	}
}

/*
* Applies a preset upwards force (Positive Y)
*/
void  PhysicsEngine::applyUpwardsForce(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).setRestState(false);
		(**it).applyNewForce(Vector3(0, 30000.0f, 0));
	}
}

/* 
* Removes gravity from all spheres
*/
void PhysicsEngine::removeGravity(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).applyGravity(false);
	}
}

/*
* Removes accleration from all spheres in the engine by setting
* a new force of 0,0,0
*/
void PhysicsEngine::removeAcclerationFromAllSpheres(){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).applyNewForce(Vector3(0, 0, 0));
	}
}

/*
* Sets drag of all spheres in engine
*/
void PhysicsEngine::setDragSphereFactor(const float& drag){
	std::vector<Sphere*>::iterator it;
	for (it = spheres.begin(); it < spheres.end(); ++it) {
		(**it).setDragFactor(drag);
	}
}