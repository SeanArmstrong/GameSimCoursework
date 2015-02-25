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

	inline void update(const float& msec){
		std::vector<Sphere*>::iterator it;
		for (it = spheres.begin(); it < spheres.end(); ++it) {
			(**it).update(msec);
		}

		rotatePlanes();

		// Sort
		sortSpheres();
		
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
					//(**it).resolveCollisions((**it2), msec);
				}
			}
		}

		for (it = spheres.begin(); it < spheres.end(); ++it) {
			std::vector<Plane*>::iterator itp;
			if (!(**it).getRestState()){
				for (itp = planes.begin(); itp < planes.end(); ++itp) {
					if ((**it).isColliding((**itp))){
						std::cout << "COLLIDING";
						(**itp).resolveCollisions((**it), msec);
					}
				}
			}
		}
	}

	inline void draw(SFMLRenderer& renderer, const float& msec)const {
		std::vector<Sphere*>::const_iterator is;
		for (is = spheres.begin(); is < spheres.end(); ++is) {
			(**is).draw(renderer, msec);
		}

		std::vector<Plane*>::const_iterator ip;
		for (ip = planes.begin(); ip < planes.end(); ++ip) {
			(**ip).draw(renderer);
		}
	}

	Sphere* addSphere(const Vector3& pos = Vector3(0, 0, 0), const float& radius = 1.0f, float mass = 1.0f, Vector3 force = Vector3(0, 0, 0));
	Plane* addPlane(Vector3& plane, Vector3 a, Vector3 b, Vector3 c, Vector3 d,  const float& distance);
	void sortSpheres();


	void rotatePlanes();
	void applyGravity();
	void applyUpwardsForce();
	void removeUpwardsForce();
	void removeAcclerationFromAllSpheres();
	void setDragSphereFactor(const float& drag);

private:
	std::vector<Sphere*> spheres;

	// Change to array as we know the size
	std::vector<Plane*> planes;
};

