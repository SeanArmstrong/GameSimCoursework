#pragma once

#include <vector>
#include "Sphere.h"
#include "Plane.h"

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
		
		for (it = spheres.begin(); it < spheres.end(); ++it) {
			std::vector<Sphere*>::iterator it2;
			for (it2 = spheres.begin(); it2 < spheres.end(); ++it2) {
				if ((it != it2) && ((**it).isColliding((**it2)))){
					//std::cout << "Collision occuring";
					//Resolve Collision
				}
			}
		}

		for (it = spheres.begin(); it < spheres.end(); ++it) {
			std::vector<Plane*>::iterator itp;
			for (itp = planes.begin(); itp < planes.end(); ++itp) {
				if ((**it).isColliding((**itp))){
					//std::cout << "Plane COL";
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
	Plane* addPlane(Vector3& plane, const float& distance);

private:
	std::vector<Sphere*> spheres;

	// Change to array as we know the size
	std::vector<Plane*> planes;
};

