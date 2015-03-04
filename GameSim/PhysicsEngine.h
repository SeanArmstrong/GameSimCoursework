/*
* Author: Sean Armstrong
* Class to handle all physical interation between physical objects
*/

#pragma once

#include <vector>
#include "Sphere.h"
#include "Plane.h"
#include "Quaternion.h"
#include <iostream>

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void update(const float& msec);

	void draw(SFMLRenderer& renderer, const float& msec) const;

	/* Adding physics objects */

	Sphere* addSphere(const Vector3& pos = Vector3(0, 0, 0), const float& radius = 1.0f, float mass = 1.0f, Vector3 force = Vector3(0, 0, 0));
	Plane* addPlane(const Vector3& plane, const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d, const float& distance);

	/* End Adding */

	void sortSpheres();


	void rotatePlanes(const Vector3& axis);

	void applyGravity();
	void applyUpwardsForce();

	void removeGravity();
	void removeUpwardsForce();
	void removeAcclerationFromAllSpheres();

	void setDragSphereFactor(const float& drag);
	void setPlaneRotation(const Vector3& axis);

private:

	std::vector<Sphere*> spheres;
	std::vector<Plane*> planes;
};

